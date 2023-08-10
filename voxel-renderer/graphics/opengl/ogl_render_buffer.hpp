//
// Created by xmmmmmovo on 10/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDER_BUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDER_BUFFER_HPP

#include <utility>

#include <glad/glad.h>

namespace voxel {

struct OGLRenderBufferDescription final {
    GLsizei _width{};
    GLsizei _height{};

    GLenum internal_format{};
};

class OGLRenderBuffer final : private NonCopyable {
private:
    OGLRenderBufferDescription _description{};
    unsigned int               _rbo{};

private:
    void create_rbo() {
        if (_rbo != 0) {
            glDeleteRenderbuffers(1, &_rbo);
            _rbo = 0;
        }
        glGenRenderbuffers(1, &_rbo);
        bind();
        glRenderbufferStorage(GL_RENDERBUFFER, _description.internal_format,
                              _description._width, _description._height);
        unbind();
    }

public:
    explicit OGLRenderBuffer(OGLRenderBufferDescription description) noexcept
        : _description(description) {
        create_rbo();
    };

    // implement move
    OGLRenderBuffer(OGLRenderBuffer &&other) noexcept
        : _description(other._description), _rbo(other._rbo) {
        other._rbo = 0;
    }

    OGLRenderBuffer &operator=(OGLRenderBuffer &&other) noexcept {
        if (this == &other) { return *this; }

        _description = other._description;
        _rbo         = other._rbo;
        other._rbo   = 0;

        return *this;
    }


    void bind() const noexcept { glBindRenderbuffer(GL_RENDERBUFFER, _rbo); }

    void unbind() const noexcept { glBindRenderbuffer(GL_RENDERBUFFER, 0); }

    [[nodiscard]] unsigned int getRenderBufferID() const noexcept {
        return _rbo;
    }

    void resize(int width, int height) {
        _description._width  = width;
        _description._height = height;
        create_rbo();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_RENDER_BUFFER_HPP
