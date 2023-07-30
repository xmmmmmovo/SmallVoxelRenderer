//
// Created by xmmmmmovo on 30/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP

#include <glad/glad.h>

#include "core/noncopyable.hpp"

namespace voxel {

class OGLVertexArray final : private NonCopyable {
private:
    GLuint _vao_id{0};
    bool   binded{false};

public:
    OGLVertexArray() noexcept {
        glGenVertexArrays(1, &_vao_id);
        glBindVertexArray(_vao_id);
    }

    ~OGLVertexArray() noexcept override {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &_vao_id);
    }

    void bind() noexcept {
        glBindVertexArray(_vao_id);
        binded = true;
    }

    void unbind() noexcept {
        glBindVertexArray(0);
        binded = false;
    }

    void enableAttribute(GLuint index) noexcept {
        if (!binded) { bind(); }
        glEnableVertexAttribArray(index);
    }

    void disableAttribute(GLuint index) noexcept {
        if (!binded) { bind(); }
        glDisableVertexAttribArray(index);
    }

    void vertexAttributePointer(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizei stride,
                                const void *pointer) noexcept {
        if (!binded) { bind(); }
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

    void vertexAttributePointer(GLuint index, GLint size, GLenum type,
                                GLboolean normalized, GLsizei stride,
                                GLuint offset) noexcept {
        if (!binded) { bind(); }
        glVertexAttribPointer(index, size, type, normalized, stride,
                              reinterpret_cast<const void *>(offset));
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP
