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
{    5000, "bf835f754e392a456a2c2b3dbedc192d0d6423f42802a048173d914d01ed0898"},
{   10000, "5f6c69de3b0af9c67b45827c87327f2e724a5d090de20ac210efcc970523dcbe"},
{   15000, "88a0312b2e88d154d95e96746bf61ae220048af6bdfb54b1dbe5d3cb7dbe36fc"},
{   20000, "06b2cc0f6eef46c813ab32015363d7b6054b7042dfda3ed9a80f073da6006ea4"},
{   25000, "1a078ec18e501605c83b18dbea2b0509842af44c6608e57c238988a8067fba81"},
{   30000, "e3329d3918e5ab251afde1c4572bfe57e3ad44add3a832ae9c48074c140204ec"},
{   35000, "dde4f174e650c7b3191dc96a0277c13288d57573d482de5545d7bf3a014c07ad"},
{   40000, "645a640ec893e1598e0e3feb56c6bd7d39ada018ffb04060b853e22dead91489"},
{   45000, "4c2663a705dccbd45d4e01c91b36ed53328f741b3c59462ec77b1dc2c7287a38"},
{   50000, "9d7f8667f78ca430bceef7fdc864e7f6e7741f7f3f99281fccef4f6345b1fdbe"},
{   55000, "0e6e5c1a267f77f949199d83de7330ae717ab8ed02046fb7bbe7da2f158e3044"},
{   60000, "8f16d5715b71c99d6cb7dace56fff604b6c4bdcf64966f97fba0f9ba6a4b7ddc"},
{   65000, "dbac88c36d0f7f5ca89e5ba381ac6cc934aad87a62e0246765e537c53b30a3e3"},
{   70000, "4291220f7c78ce7a238f207adf4d98d49ee893e2d949d92397f23f801219ee1b"},
{   75000, "c2ff355382b9eefc2dcde0a952100b6c1997f3405ae5164063ecdfba9e120f08"},
{   80000, "f722f475ebea9dc525679d9afe6c3124c7f29a7d2e8b5ef34fb78753841eca33"},
{   85000, "f203db16bdcbd0e4d72fddbe41aef9ced02092e3f84ed06b7d8805d5529a3b4a"},
{   90000, "a24d64ce3c516a6560104f07d8ebe322b26648cb1f255a1257e56ef7a8be56a2"},
{   95000, "eb729705e214e8fc9ee764598e307e6a650703db3021817985f9d94a0f3310b0"},
{  100000, "1da1d8b3eced1770bfa45313b63fe71d7a3e93b5e97fb118177430d8ad68e069"},
{  105000, "4451da60d3866337f2fdb9836bb27c22b2aa6374c22d9ec12a86f50fee29f559"},
{  110000, "9382e62ec35944cbf1b748987c10f71c99e3011d4d2589e4da80fd70cb417d27"},
{  115000, "da08a8f61e2dd67ac02cfb352c35f853b8db479d533fbc328c75d36bc16a326c"},
{  120000, "e81b95a530f33627f055e1c85d2e6cbc8507eb68b8013173da56d9790d3042b2"},
{  125000, "7136387e652440a5441662ab50137315496cf710aae2aab8c303b43ded491587"},
{  130000, "795513852f20fb3dca23b08775498be68749cae0775307eccd9f26428efa1c32"},
{  135000, "cfd152ebfae21f0c6416786b42bdd0ec0614c944bbaf41870a84ab82b91575c3"},
{  140000, "cf4d237c489e67aa52347cb862e194080fe994fae2bce19151e983044d8b6eac"},
};
}
