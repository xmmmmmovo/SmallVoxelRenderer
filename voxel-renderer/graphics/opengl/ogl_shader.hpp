//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP

#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <spdlog/spdlog.h>

#include <vector>

namespace voxel {

enum class OGLShaderType : GLenum {
    VERTEX          = GL_VERTEX_SHADER,
    FRAGMENT        = GL_FRAGMENT_SHADER,
    GEOMETRY        = GL_GEOMETRY_SHADER,
    COMPUTE         = GL_COMPUTE_SHADER,
    TESS_CONTROL    = GL_TESS_CONTROL_SHADER,
    TESS_EVALUATION = GL_TESS_EVALUATION_SHADER
};

void glShaderStatusCheck(GLuint const &shader_id, GLenum status_type) {
    int status = 0;
    glGetShaderiv(shader_id, status_type, &status);
    if (!status) {
        int info_len = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_len);
        if (info_len > 1) {
            std::vector<char> info_log(info_len);
            glGetShaderInfoLog(shader_id, info_len, nullptr, info_log.data());
            spdlog::error("Error on shader:\n%s\n", info_log.data());
        }
    }
}

void glShaderCompileStatusCheck(GLuint const &shader_id) {
    glShaderStatusCheck(shader_id, GL_COMPILE_STATUS);
}

void glShaderLinkStatusCheck(GLuint const &shader_id) {
    glShaderStatusCheck(shader_id, GL_LINK_STATUS);
}

class OGLShader : private NonCopyable {
private:
    GLuint shader_id = 0;

public:
    OGLShader() noexcept = default;
    OGLShader(OGLShaderType                    type,
              std::vector<std::uint8_t> const &source) noexcept {
        initShaderFromSource(type, source);
    }
    ~OGLShader() noexcept override { glDeleteShader(shader_id); }

    OGLShader(OGLShader &&other) noexcept {
        shader_id       = other.shader_id;
        other.shader_id = 0;
    }

    OGLShader &operator=(OGLShader &&other) noexcept {
        if (this == &other) { return *this; }
        glDeleteShader(shader_id);
        shader_id       = other.shader_id;
        other.shader_id = 0;
        return *this;
    }

    void initShaderFromSource(OGLShaderType                    type,
                              std::vector<std::uint8_t> const &source) {
        glDeleteShader(shader_id);
        shader_id = glCreateShader(static_cast<GLenum>(type));
        glShaderBinary(1, &shader_id, GL_SHADER_BINARY_FORMAT_SPIR_V,
                       source.data(), source.size());
        glSpecializeShader(shader_id, "main", 0, nullptr, nullptr);
        glShaderCompileStatusCheck(shader_id);
    }

    void attach(GLuint program_id) const noexcept {
        glAttachShader(program_id, shader_id);
    }

    void detach(GLuint program_id) const noexcept {
        glDetachShader(program_id, shader_id);
    }

    [[nodiscard]] GLuint getShaderId() const noexcept { return shader_id; }
};

class OGLShaderProgram : private NonCopyable {
private:
    GLuint _program_id = 0;

public:
    OGLShaderProgram() noexcept = default;
    ~OGLShaderProgram() noexcept override { glDeleteProgram(_program_id); }

    OGLShaderProgram(OGLShaderProgram &&other) noexcept {
        _program_id       = other._program_id;
        other._program_id = 0;
    }

    OGLShaderProgram &operator=(OGLShaderProgram &&other) noexcept {
        if (this == &other) { return *this; }
        glDeleteProgram(_program_id);
        _program_id       = other._program_id;
        other._program_id = 0;
        return *this;
    }

    void attach(OGLShader const &shader) noexcept {
        if (_program_id == 0) { _program_id = glCreateProgram(); }
        shader.attach(_program_id);
    }

    void detach(OGLShader const &shader) noexcept {
        if (_program_id == 0) { _program_id = glCreateProgram(); }
        shader.detach(_program_id);
    }

    void link() const noexcept {
        glLinkProgram(_program_id);
        glShaderLinkStatusCheck(_program_id);
    }

    void use() const noexcept { glUseProgram(_program_id); }

    [[nodiscard]] GLuint getProgramId() const noexcept { return _program_id; }

    template<typename T>
    void setUniform(std::string_view const &name, T value) const noexcept {
        if constexpr (std::is_same_v<T, float>) {
            glUniform1f(glGetUniformLocation(_program_id, name.data()), value);
        } else if constexpr (std::is_same_v<T, int>) {
            glUniform1i(glGetUniformLocation(_program_id, name.data()), value);
        } else if constexpr (std::is_same_v<T, glm::vec4>) {
            glUniform4fv(glGetUniformLocation(_program_id, name.data()), 1,
                         &value[0]);
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            glUniformMatrix4fv(glGetUniformLocation(_program_id, name.data()),
                               1, GL_FALSE, &value[0][0]);
        }
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP
