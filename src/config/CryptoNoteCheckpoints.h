// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers
//
// This file is part of Bytecoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <initializer_list>

namespace CryptoNote {
struct CheckpointData {
  uint32_t index;
  const char* blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = {  
 {       0, "041fcedf9ea195f37a53fdb5ac64cc8420cd9d1bc3e448606c51f2640e181025"},
{       2, "91555c0d9577c8bb0aa54958f53d0b73e5307b2cbb507e4b7810b85b5b207fc1"},
{    5000, "bf835f754e392a456a2c2b3dbedc192d0d6423f42802a048173d914d01ed0898"},
/*{   10000, ""},
{   15000, ""},
{   20000, ""},
{   25000, ""},
{   30000, ""},
{   35000, ""},
{   40000, ""},
/*
};
}
