//
// Created by xmmmmmovo on 28/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP

#include <glad/glad.h>

#include <algorithm>
#include <vector>

#include "core/meta/is_specialization.hpp"

namespace voxel {

enum class OGLBufferType : GLenum {
    VERTEX  = GL_ARRAY_BUFFER,
    ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
    UNIFORM = GL_UNIFORM_BUFFER,
};

template<typename T>
struct OGLBufferDescription final {
    T             data{};
    std::uint32_t size{0};
    OGLBufferType type{};
};

template<typename T>
class OGLBuffer final {
private:
    GLuint                  _buf_id{};
    OGLBufferDescription<T> _description{};

public:
    explicit OGLBuffer(OGLBufferDescription<T> description)
        : _description(std::move(description)) {
        GLsizeiptr size = 0;
        void      *ptr  = nullptr;

        if constexpr (IsSpecialization<T, std::vector>::value ||
                      std::is_array<T>::value) {
            size = _description.data.size() * sizeof(typename T::value_type);
            ptr  = _description.data.data();
        } else {
            size = sizeof(_description.data);
            ptr  = &_description.data;
        }

        glGenBuffers(1, &_buf_id);
        glBindBuffer(static_cast<GLenum>(_description.type), _buf_id);
        glBufferData(static_cast<GLenum>(_description.type), size, ptr,
                     GL_STATIC_DRAW);
        glBindBuffer(static_cast<GLenum>(_description.type), 0);
    };

    void bind() const noexcept {
        glBindBuffer(static_cast<GLenum>(_description.type), _buf_id);
    }

    [[nodiscard]] GLuint getId() const noexcept { return _buf_id; }

    ~OGLBuffer() noexcept { glDeleteBuffers(1, &_buf_id); };
};
}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP
