//
// Created by xmmmmmovo on 11/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_COMMON_BUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_COMMON_BUFFER_HPP

#include "graphics/opengl/ogl_vertex_array.hpp"

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <memory>

namespace voxel {

static constexpr std::array<glm::vec3, 8> CUBE_VERTICES{
        glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f),
        glm::vec3(0.5f, 0.5f, -0.5f),   glm::vec3(-0.5f, 0.5f, -0.5f),
        glm::vec3(-0.5f, -0.5f, 0.5f),  glm::vec3(0.5f, -0.5f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.5f),    glm::vec3(-0.5f, 0.5f, 0.5f)};
static constexpr std::array<unsigned int, 36> CUBE_INDICES{
        0, 5, 4, 5, 0, 1, 3, 7, 6, 3, 6, 2, 7, 4, 6, 6, 4, 5,
        2, 1, 3, 3, 1, 0, 3, 0, 7, 7, 0, 4, 6, 5, 2, 2, 5, 1};

static constexpr std::array<glm::vec2, 4> QUAD_VERTICES{
        glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f),
        glm::vec2(0.0f, 1.0f)};
static constexpr std::array<unsigned int, 6> QUAD_INDICES{0, 1, 2, 0, 2, 3};


struct CommonVertexBuffer {
    OGLBuffer<std::array<glm::vec3, 8>> cube_vbo{
            OGLBufferDescription{OGLBufferType::VERTEX}, CUBE_VERTICES};
    OGLBuffer<std::array<unsigned int, 36>> cube_ebo{
            OGLBufferDescription{OGLBufferType::ELEMENT}, CUBE_INDICES};
    OGLVertexArray cube_vao{};

    OGLBuffer<std::array<glm::vec2, 4>> quad_vbo{
            OGLBufferDescription{OGLBufferType::VERTEX}, QUAD_VERTICES};
    OGLBuffer<std::array<unsigned int, 6>> quad_ebo{
            OGLBufferDescription{OGLBufferType::ELEMENT}, QUAD_INDICES};
    OGLVertexArray quad_vao{};

    CommonVertexBuffer() {
        cube_vao.bind();
        cube_vao.bindBuffer(cube_vbo);
        cube_vao.bindBuffer(cube_ebo);
        cube_vao.unbind();

        quad_vao.bind();
        quad_vao.bindBuffer(quad_vbo);
        quad_vao.bindBuffer(quad_ebo);
        quad_vao.unbind();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_COMMON_BUFFER_HPP
