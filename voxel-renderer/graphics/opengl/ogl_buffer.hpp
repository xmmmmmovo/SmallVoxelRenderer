//
// Created by xmmmmmovo on 28/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP

#include <glad/glad.h>

#include <algorithm>
#include <glm/glm.hpp>
#include <vector>

#include "core/meta/is_specialization.hpp"

namespace voxel {

enum class OGLBufferType : GLenum {
    VERTEX  = GL_ARRAY_BUFFER,
    ELEMENT = GL_ELEMENT_ARRAY_BUFFER,
    UNIFORM = GL_UNIFORM_BUFFER,
};

struct OGLBufferDescription final {
    OGLBufferType type{};
    GLenum        usage{GL_STATIC_DRAW};

    std::uint32_t index{0};
};

template<typename T>
class OGLBuffer final : private NonCopyable {
private:
    GLuint               _buf_id{};
    OGLBufferDescription _description{};

    std::uint32_t _dataLength{0};
    std::size_t   _size{0};

public:
    explicit OGLBuffer(OGLBufferDescription const &description, T const &data)
        : _description(description) {
        GLsizeiptr  size = 0;
        void const *ptr  = nullptr;

        if constexpr (IsSpecialization<T, std::vector>::value ||
                      IsArray<T>::value) {
            size = data.size() * sizeof(typename T::value_type);
            ptr  = data.data();

            if constexpr (std::is_same_v<typename T::value_type, glm::vec2>) {
                _dataLength = 2;
            } else if constexpr (std::is_same_v<typename T::value_type,
                                                glm::vec3>) {
                _dataLength = 3;
            } else if constexpr (std::is_same_v<typename T::value_type,
                                                glm::vec4>) {
                _dataLength = 4;
            } else {
                _dataLength = 1;
            }
            this->_size = data.size();
        } else {
            size        = sizeof(data);
            ptr         = &data;
            _dataLength = 1;
            this->_size = 1;
        }

        glGenBuffers(1, &_buf_id);
        glBindBuffer(static_cast<GLenum>(_description.type), _buf_id);
        glBufferData(static_cast<GLenum>(_description.type), size, ptr,
                     _description.usage);

        if (_description.type == OGLBufferType::UNIFORM) {
            glBindBufferBase(static_cast<GLenum>(_description.type),
                             _description.index, _buf_id);
        }

        glBindBuffer(static_cast<GLenum>(_description.type), 0);
    };

    void bind() const noexcept {
        glBindBuffer(static_cast<GLenum>(_description.type), _buf_id);
    }

    void unbind() const noexcept {
        glBindBuffer(static_cast<GLenum>(_description.type), 0);
    }

    void updateBuffer(T const &data, std::size_t offset = 0) {
        glBufferSubData(static_cast<GLenum>(_description.type), offset,
                        sizeof(data), &data);
    }

    ~OGLBuffer() noexcept override { glDeleteBuffers(1, &_buf_id); };

    [[nodiscard]] GLuint getId() const noexcept { return _buf_id; }

    [[nodiscard]] OGLBufferType getType() const noexcept {
        return _description.type;
    }

    [[nodiscard]] std::uint32_t getDataLength() const noexcept {
        return _dataLength;
    }

    [[nodiscard]] std::size_t getSize() const noexcept { return _size; }
};
}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_BUFFER_HPP
