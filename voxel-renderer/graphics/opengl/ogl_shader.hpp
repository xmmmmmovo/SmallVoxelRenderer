//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP

#include <glad/glad.h>

namespace voxel {

enum class OGLShaderType {};

class OGLShader {
private:
    GLuint _program_id  = 0;
    GLuint _vertex_id   = 0;
    GLuint _fragment_id = 0;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_SHADER_HPP
