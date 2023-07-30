//
// Created by xmmmmmovo on 29/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP


#include "ogl_frambuffer.hpp"
#include "ogl_renderpass.hpp"

#include <algorithm>

namespace voxel {

struct OGLPipelineDescription final {
    std::unique_ptr<OGLRenderPass> _render_passes{nullptr};

    std::shared_ptr<OGLShader> _vert_shader{nullptr};
    std::shared_ptr<OGLShader> _frag_shader{nullptr};
    OGLShaderProgram           _shader_program{};



    glm::vec4 _clear_color{0.0f, 0.0f, 0.0f, 1.0f};
};

class OGLPipeline final {
private:
    OGLPipelineDescription _description{};

private:
    void clear() const {
        glClearColor(_description._clear_color.r, _description._clear_color.g,
                     _description._clear_color.b, _description._clear_color.a);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

public:
    explicit OGLPipeline(OGLPipelineDescription description)
        : _description(std::move(description)) {
        assert((_description._render_passes != nullptr) && "render_passes is "
                                                           "nullptr");
    };
    ~OGLPipeline() noexcept = default;

    void update() noexcept {
        // render loop
        clear();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_PIPELINE_HPP
