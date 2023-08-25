//
// Created by xmmmmmovo on 08/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP

#include "glm/mat4x4.hpp"

namespace voxel {

struct MatricesStruct final {
    glm::mat4 view{};
    glm::mat4 projection{};
    glm::mat4 view_projection{};
};

struct ModelStruct final {
    glm::mat4 model{glm::scale(glm::mat4(1.0f), glm::vec3(2.0f))};
};

struct CameraStruct final {
    glm::vec4 position{};
    glm::vec4 ray_steps{};
};

struct SplatStruct final {
    glm::mat4 splat_normal{};
    float     splat_size{};
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP
