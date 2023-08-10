//
// Created by xmmmmmovo on 29/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP


#include "ogl_frambuffer.hpp"
#include "ogl_renderpass.hpp"
#include "ogl_vertex_array.hpp"

#include <algorithm>

namespace voxel {

struct OGLPipelineDescription final {
    OGLShaderProgram _shader_program{};
};

class OGLPipeline final {
private:
    OGLPipelineDescription _description{};

private:
public:
    explicit OGLPipeline(OGLPipelineDescription description)
        : _description(std::move(description)){};
    ~OGLPipeline() noexcept = default;

    void use() const noexcept { _description._shader_program.use(); }

    template<typename T>
    void setUniform(const std::string_view &name, const T &value) {
        _description._shader_program.setUniform(name, value);
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP
