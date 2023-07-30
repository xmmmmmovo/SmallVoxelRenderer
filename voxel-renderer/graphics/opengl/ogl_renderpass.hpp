#include <utility>

//
// Created by xmmmmmovo on 28/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDERPASS_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDERPASS_HPP

#include "ogl_frambuffer.hpp"
#include "ogl_shader.hpp"

namespace voxel {

struct OGLRenderPassDescription final {
    std::shared_ptr<OGLShader> _vert_shader{nullptr};
    std::shared_ptr<OGLShader> _frag_shader{nullptr};
    OGLShaderProgram           _shader_program{};

    std::unique_ptr<OGLFramebuffer> _framebuffer{nullptr};
};

class OGLRenderPass final {
    OGLRenderPassDescription _description{};

public:
    explicit OGLRenderPass(OGLRenderPassDescription description)
        : _description(std::move(description)){};
    ~OGLRenderPass() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDERPASS_HPP
