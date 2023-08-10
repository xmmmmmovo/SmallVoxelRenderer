//
// Created by xmmmmmovo on 08/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP

#include <glm/mat4x4.hpp>

namespace voxel {

struct MatricesStruct final {
    glm::mat4 view{};
    glm::mat4 projection{};
    glm::mat4 view_projection{};
};

struct ModelStruct final {
    glm::mat4 model{glm::scale(glm::mat4(1.0f), glm::vec3(3.0f))};
    //    glm::mat4 model{glm::mat4(1.0f)};
};

struct CameraStruct final {
    glm::vec4 position{};
    glm::vec4 ray_steps{};
};

static constexpr std::array<glm::vec3, 8> VERTICES{
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(-0.5f, 0.5f, 0.5f)};
static constexpr std::array<unsigned int, 36> INDICES{
        0, 5, 4, 5, 0, 1, 3, 7, 6, 3, 6, 2, 7, 4, 6, 6, 4, 5,
        2, 1, 3, 3, 1, 0, 3, 0, 7, 7, 0, 4, 6, 5, 2, 2, 5, 1};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_UBUFFER_STRUCT_HPP
