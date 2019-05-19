// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
// Copyright (c) 2014-2018, The Monero Project
// Copyright (c) 2018-2019, The TurtleCoin Developers
//
// Please see the included LICENSE file for more information.

#include "Miner.h"

#include <iostream>

#include <functional>
#include <mutex>
#include "Common/StringTools.h"
#include "crypto/hash.h"
#include "crypto/crypto.h"
#include <crypto/random.h>
#include "CryptoNoteCore/CachedBlock.h"
#include <Common/Varint.h>
#include <config/CryptoNoteConfig.h>
#include "CryptoNoteCore/CheckDifficulty.h"
#include "CryptoNoteCore/CryptoNoteFormatUtils.h"

#include <System/InterruptedException.h>

#include <Utilities/ColouredMsg.h>

#define yeet throw

namespace CryptoNote {

Miner::(System::Dispatcher& dispatcher, Logging::ILogger& logger) :
  m_dispatcher(dispatcher),
  m_miningStopped(dispatcher),
  m_state(MiningState::MINING_STOPPED),
  m_logger(logger, "Miner") {
}

Miner::Miner() {
  assert(m_state != MiningState::MINING_IN_PROGRESS);
}

BlockTemplate Miner::mine(const BlockMiningParameters& blockMiningParameters, size_t threadCount) {
  if (threadCount == 0) {
    throw std::runtime_error("Miner requires at least one thread");
  }

  if (m_state == MiningState::MINING_IN_PROGRESS) {
    throw std::runtime_error("Mining is already in progress");
  }

  m_state = MiningState::MINING_IN_PROGRESS;
  m_miningStopped.clear();

  runWorkers(blockMiningParameters, threadCount);

  assert(m_state != MiningState::MINING_IN_PROGRESS);
  if (m_state == MiningState::MINING_STOPPED) {
    std::cout << InformationMsg("Mining has been stopped");
    throw System::InterruptedException();
  }

  assert(m_state == MiningState::BLOCK_FOUND);
  return m_block;
}

void Miner::stop() {
  MiningState state = MiningState::MINING_IN_PROGRESS;

  if (m_state.compare_exchange_weak(state, MiningState::MINING_STOPPED)) {
    m_miningStopped.wait();
    m_miningStopped.clear();
  }
}

void Miner::runWorkers(BlockMiningParameters blockMiningParameters, size_t threadCount) {
  assert(threadCount > 0);

  std::cout << InformationMsg("Started mining for difficulty of ")
              << InformationMsg(blockMiningParameters.difficulty)
              << InformationMsg(". Good luck! ;)\n");

  try {
    blockMiningParameters.blockTemplate.nonce = Random::randomValue<uint32_t>();


    for (size_t i = 0; i < threadCount; ++i) {
      m_workers.emplace_back(std::unique_ptr<System::RemoteContext<void>> (
        new System::RemoteContext<void>(m_dispatcher, std::bind(&Miner::workerFunc, this, blockMiningParameters.blockTemplate, blockMiningParameters.difficulty, static_cast<uint32_t>(threadCount))))
      );
	 std::cout << InformationMsg("Thread ")
		 	<< (i)
		        << (" started at nonce: ")
		        << (blockMiningParameters.blockTemplate.nonce);
             

      blockMiningParameters.blockTemplate.nonce++;
    }

    m_workers.clear();

  } catch (std::exception& e) {
    std::cout << WarningMsg("Error occured whilst mining: ")
                  << WarningMsg(e.what()) << std::endl;
    m_state = MiningState::MINING_STOPPED;
  }

  m_miningStopped.set();
}

void Miner::workerFunc(const BlockTemplate& blockTemplate, uint64_t difficulty, uint32_t nonceStep) {
	uint64_t* dataset_64;
	try {
		BlockTemplate block = blockTemplate;
		CachedBlock cachedBlock(block);
		if(block.majorVersion < BLOCK_MAJOR_VERSION_6){
			while (m_state == MiningState::MINING_IN_PROGRESS) {
				CachedBlock cachedBlock(block);
				Crypto::Hash hash = cachedBlock.getBlockLongHash();
				if (check_hash(hash, difficulty)) {
					std::cout << InformationMsg("Found block for difficulty ")
						  	<< (difficulty);

					if (!setStateBlockFound()) {
						  std::cout << WarningMsg("block is already found or mining stopped");
						  return;
					}

					m_block = block;
					return;
				}

				incrementHashCount();
				block.nonce += nonceStep;
			}
		} else{
			uint32_t height = cachedBlock.getBlockIndex();
			dataset_64      = (uint64_t*)calloc(536870912,8);
			if(!dataset_64) exit(1);
			std::cout << InformationMsg("Initialising dataset");
			Crypto::dataset_height(height, dataset_64);
			std::cout << InformationMsg("Finished one-time initialisation");
			std::cout << InformationMsg("Started mining on dataset");
			Crypto::Hash hash;
			while (m_state == MiningState::MINING_IN_PROGRESS) {
				CachedBlock cachedBlock(block);
				const auto& rawHashingBlock = cachedBlock.getParentBlockHashingBinaryArray(true);
				keghash_full(rawHashingBlock.data(), rawHashingBlock.size(), hash, dataset_64);
				if (check_hash(hash, difficulty)) {
					free(dataset_64);
					std::cout << InformationMsg("Found block for difficulty ")
						  	<< (difficulty);

					if (!setStateBlockFound()) {
						std::cout << WarningMsg("block is already found or mining stopped");
						return;
					}

					m_block = block;
					return;
				}

				incrementHashCount();
				block.nonce += nonceStep;
			}
		}
	} catch (std::exception& e) {
		std::cout << WarningMsg("Miner got error");
		m_state = MiningState::MINING_STOPPED;
		try{			
			free(dataset_64);
		} catch(std::exception& e) {
			;
		}	
	}
}

bool Miner::setStateBlockFound() {
  auto state = m_state.load();

  for (;;) {
    switch (state) {
      case MiningState::BLOCK_FOUND:
        return false;

      case MiningState::MINING_IN_PROGRESS:
        if (m_state.compare_exchange_weak(state, MiningState::BLOCK_FOUND)) {
          return true;
        }
        break;

      case MiningState::MINING_STOPPED:
        return false;

      default:
        assert(false);
        return false;
    }
  }
}

void Miner::incrementHashCount() {
  std::lock_guard<std::mutex> guard(m_hashes_mutex);
  m_hash_count++;
}

uint64_t Miner::getHashCount() {
  std::lock_guard<std::mutex> guard(m_hashes_mutex);
  return m_hash_count;
}

} //namespace CryptoNote
