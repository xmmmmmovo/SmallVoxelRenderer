//
// Created by xmmmmmovo on 29/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP

#include <optional>
#include <utility>
#include <vector>

#include "ogl_render_buffer.hpp"
#include "ogl_texture.hpp"

namespace voxel {

struct OGLFramebufferDescription final {
    int width{0};
    int height{0};

    std::vector<OGLTexture>        color_attachments{};
    std::optional<OGLRenderBuffer> depth_stencil_attachment{};
};

class OGLFramebuffer final {
private:
    OGLFramebufferDescription _description;

    GLuint _framebuffer{0};

    void create_framebuffer() {
        if (_framebuffer != 0) {
            glDeleteFramebuffers(1, &_framebuffer);
            _framebuffer = 0;
        }
        glGenFramebuffers(1, &_framebuffer);
        bind();
        std::size_t i = 0;
        for (auto &color_attachment : _description.color_attachments) {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i++,
                                   GL_TEXTURE_2D,
                                   color_attachment.getTextureID(), 0);
        }
        if (_description.depth_stencil_attachment.has_value()) {
            glFramebufferRenderbuffer(
                    GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
                    GL_RENDERBUFFER,
                    _description.depth_stencil_attachment.value()
                            .getRenderBufferID());
        }
        unbind();
    }

public:
    explicit OGLFramebuffer(OGLFramebufferDescription description)
        : _description(std::move(description)) {
        create_framebuffer();
    };

    void bind() const noexcept {
        glBindFramebuffer(GL_FRAMEBUFFER, _framebuffer);
    }

    void unbind() const noexcept { glBindFramebuffer(GL_FRAMEBUFFER, 0); }

    void resize(int width, int height) {
        _description.width  = width;
        _description.height = height;
        create_framebuffer();
    }

    [[nodiscard]] GLuint getFramebufferID() const noexcept {
        return _framebuffer;
    }

    [[nodiscard]] OGLTexture const &
    getColorAttachment(int index) const noexcept {
        return _description.color_attachments[index];
    }

    [[nodiscard]] std::optional<OGLRenderBuffer> const &
    getDepthStencilAttachment() const noexcept {
        return _description.depth_stencil_attachment;
    }

    ~OGLFramebuffer() noexcept {
        if (_framebuffer != 0) { glDeleteFramebuffers(1, &_framebuffer); }
    };
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP
