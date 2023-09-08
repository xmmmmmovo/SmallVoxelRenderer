//
// Created by xmmmmmovo on 09/09/2023.
//

#ifndef VOXEL_RENDERER_VOXELIZER_CONFIG_HPP
#define VOXEL_RENDERER_VOXELIZER_CONFIG_HPP

#include <cstdint>

namespace voxel {

static constexpr std::uint32_t MIN_TREE_LEVEL = 1;
static constexpr std::uint32_t MAX_TREE_LEVEL = 12;

static constexpr std::uint32_t MIN_NODE_NUM = 1000000;
static constexpr std::uint32_t MAX_NODE_NUM = 100000000;

}// namespace voxel

#endif//VOXEL_RENDERER_VOXELIZER_CONFIG_HPP
