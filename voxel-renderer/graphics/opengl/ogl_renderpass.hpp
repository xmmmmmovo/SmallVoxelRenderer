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
    std::unique_ptr<OGLFramebuffer> _framebuffer{nullptr};
    glm::vec4                       _clear_color{0.8f, 0.8f, 0.8f, 1.0f};
};

class OGLRenderPass final {
    OGLRenderPassDescription _description{};

private:
    void clear() const {
        glClearColor(_description._clear_color.r, _description._clear_color.g,
                     _description._clear_color.b, _description._clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

public:
    explicit OGLRenderPass(OGLRenderPassDescription description)
        : _description(std::move(description)){};

    void use() noexcept {
        if (_description._framebuffer != nullptr) {
            _description._framebuffer->bind();
        }
        clear();
    }

    void unuse() const noexcept {
        if (_description._framebuffer != nullptr) {
            _description._framebuffer->unbind();
        }
    }

    [[nodiscard]] OGLTexture const &
    getColorAttachment(int index) const noexcept {
        return _description._framebuffer->getColorAttachment(index);
    }

    [[nodiscard]] std::optional<OGLRenderBuffer> const &
    getDepthStencilAttachment() const noexcept {
        return _description._framebuffer->getDepthStencilAttachment();
    }

    ~OGLRenderPass() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDERPASS_HPP
