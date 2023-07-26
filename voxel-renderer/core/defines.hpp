//
// Created by xmmmmmovo on 2023/7/7.
//

#ifndef VOXEL_RENDERER_CORE_DEFINES_HPP
#define VOXEL_RENDERER_CORE_DEFINES_HPP

#include <cstdint>
#include <string>

// TODO: add platform detect
#define VOXEL_INLINE inline

namespace voxel {

constexpr std::string_view OPENGL_VERSION       = "#version 460";
constexpr std::uint32_t    OPENGL_MAJOR_VERSION = 4;
constexpr std::uint32_t    OPENGL_MINOR_VERSION = 6;

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_DEFINES_HPP
