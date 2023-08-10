//
// Created by xmmmmmovo on 30/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP

#include <glad/glad.h>

#include "core/noncopyable.hpp"

#include "ogl_buffer.hpp"

namespace voxel {

class OGLVertexArray final : private NonCopyable {
private:
    GLuint        _vao_id{0};
    bool          _is_indexed{false};
    GLsizei       _draw_count{0};
    std::uint32_t _attribute_count{0};

    static void enableAttribute(GLuint index) noexcept {
        glEnableVertexAttribArray(index);
    }

    static void disableAttribute(GLuint index) noexcept {
        glDisableVertexAttribArray(index);
    }

    static void vertexAttributePointer(GLuint index, GLint size, GLenum type,
                                       GLboolean normalized, GLsizei stride,
                                       const void *pointer) noexcept {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    }

public:
    OGLVertexArray() noexcept { glGenVertexArrays(1, &_vao_id); }

    ~OGLVertexArray() noexcept override {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &_vao_id);
    }

    void bind() const noexcept { glBindVertexArray(_vao_id); }

    void unbind() const noexcept { glBindVertexArray(0); }

    template<typename T>
    void bindBuffer(OGLBuffer<T> const &buffer) noexcept {
        buffer.bind();
        if (buffer.getType() == OGLBufferType::ELEMENT) {
            setIndexDrawCount(buffer.getSize());
        } else {
            setVertexDrawCount(buffer.getSize());
            vertexAttributePointer(_attribute_count, buffer.getDataLength(),
                                   GL_FLOAT, GL_FALSE, 0, nullptr);
            enableAttribute(_attribute_count++);
        }
    }

    void draw() const noexcept {
        if (_is_indexed) {
            glDrawElements(GL_TRIANGLES, _draw_count, GL_UNSIGNED_INT, nullptr);
        } else {
            glDrawArrays(GL_TRIANGLES, 0, _draw_count);
        }
    }

    void setIndexDrawCount(GLsizei count) noexcept {
        _draw_count = count;
        _is_indexed = true;
    }

    void setVertexDrawCount(GLsizei count) noexcept { _draw_count = count; }

    [[nodiscard]] GLsizei getDrawCount() const noexcept { return _draw_count; }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_VERTEX_ARRAY_HPP
