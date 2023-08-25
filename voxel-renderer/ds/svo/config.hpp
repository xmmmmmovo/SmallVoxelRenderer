//
// Created by xmmmmmovo on 14/08/2023.
//

#ifndef VOXEL_RENDERER_DS_SVO_CONFIG_HPP
#define VOXEL_RENDERER_DS_SVO_CONFIG_HPP

#include "core/config.hpp"

#include <cstdint>

namespace voxel {

constexpr std::int32_t OCTREE_LEVEL_MIN    = 1;
constexpr int          OCTREE_LEVEL_MAX    = 12;
constexpr int          OCTREE_NODE_NUM_MIN = 1000000;
constexpr int          OCTREE_NODE_NUM_MAX = 500000000;
constexpr int          BEAM_SIZE           = 8;//for beam optimization
constexpr int BEAM_WIDTH  = (WINDOW_WIDTH + (BEAM_SIZE - 1)) / BEAM_SIZE + 1;
constexpr int BEAM_HEIGHT = (WINDOW_HEIGHT + (BEAM_SIZE - 1)) / BEAM_SIZE + 1;

}// namespace voxel

#endif//VOXEL_RENDERER_DS_SVO_CONFIG_HPP
