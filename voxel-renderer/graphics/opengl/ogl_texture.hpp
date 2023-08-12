//
// Created by xmmmmmovo on 28/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_TEXTURE_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_TEXTURE_HPP

#include <filesystem>

#include "reader/image_reader.hpp"

namespace voxel {

enum class TextureDim : GLenum {
    MAP_2D   = GL_TEXTURE_2D,
    MAP_3D   = GL_TEXTURE_3D,
    MAP_CUBE = GL_TEXTURE_CUBE_MAP,
};

struct OGLTextureDescription final {
    TextureDim dim{TextureDim::MAP_2D};
    GLint      internal_format{GL_RGB};
    GLenum     format{GL_RGB};
    GLenum     type{GL_UNSIGNED_BYTE};
    GLint      min_filter{GL_LINEAR};
    GLint      mag_filter{GL_LINEAR};
    GLint      wrap_s{GL_REPEAT};
    GLint      wrap_t{GL_REPEAT};
    GLint      wrap_r{GL_REPEAT};
    GLint      level{0};
    GLint      border{0};
    GLboolean  generate_mipmap{GL_FALSE};
    GLboolean  flip_vertically{GL_FALSE};
};

class OGLTexture final : private NonCopyable {

private:
    OGLTextureDescription _description{};

    GLuint _texture_id{0};

private:
    void create_texture() {
        if (_texture_id != 0) {
            glDeleteTextures(1, &_texture_id);
            _texture_id = 0;
        }
        glGenTextures(1, &_texture_id);
        bind();

        glTexParameteri(static_cast<GLenum>(_description.dim),
                        GL_TEXTURE_MIN_FILTER, _description.min_filter);
        glTexParameteri(static_cast<GLenum>(_description.dim),
                        GL_TEXTURE_MAG_FILTER, _description.mag_filter);

        glTexParameteri(static_cast<GLenum>(_description.dim),
                        GL_TEXTURE_WRAP_S, _description.wrap_s);
        glTexParameteri(static_cast<GLenum>(_description.dim),
                        GL_TEXTURE_WRAP_T, _description.wrap_t);
        glTexParameteri(static_cast<GLenum>(_description.dim),
                        GL_TEXTURE_WRAP_R, _description.wrap_r);
    }

public:
    explicit OGLTexture(OGLTextureDescription description)
        : _description(description) {
        create_texture();
    };
    ~OGLTexture() noexcept override { glDeleteTextures(1, &_texture_id); };

    // implement move
    OGLTexture(OGLTexture &&other) noexcept
        : _description(other._description), _texture_id(other._texture_id) {
        other._texture_id = 0;
    }

    OGLTexture &operator=(OGLTexture &&other) noexcept {
        if (this == &other) { return *this; }

        _description = other._description;
        _texture_id  = other._texture_id;

        other._texture_id = 0;

        return *this;
    }

    static void activeSlot(GLuint index) noexcept {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    void bind() const noexcept {
        glBindTexture(static_cast<GLenum>(_description.dim), _texture_id);
    }

    void unbind() const noexcept {
        glBindTexture(static_cast<GLenum>(_description.dim), 0);
    }

    [[nodiscard]] GLuint getTextureID() const noexcept { return _texture_id; }

    void uploadData(Image const &image) const {
        if (_description.generate_mipmap) {
            glTexParameteri(static_cast<GLenum>(_description.dim),
                            GL_TEXTURE_BASE_LEVEL, 0);
            glTexParameteri(static_cast<GLenum>(_description.dim),
                            GL_TEXTURE_MAX_LEVEL, _description.level);
        }

        switch (_description.dim) {
            case TextureDim::MAP_2D:
                glTexImage2D(static_cast<GLenum>(_description.dim), 0,
                             _description.internal_format, image.width,
                             image.height, _description.border,
                             _description.format, _description.type,
                             image.data);
                break;
            case TextureDim::MAP_3D:
                glTexImage3D(static_cast<GLenum>(_description.dim), 0,
                             _description.internal_format, image.width,
                             image.height, image.depth, _description.border,
                             _description.format, _description.type,
                             image.data);
                break;
            case TextureDim::MAP_CUBE:
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + image.idx, 0,
                             _description.internal_format, image.width,
                             image.height, _description.border,
                             _description.format, _description.type,
                             image.data);
                break;
        }

        if (_description.generate_mipmap) {
            glGenerateMipmap(static_cast<GLenum>(_description.dim));
        }
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_TEXTURE_HPP
