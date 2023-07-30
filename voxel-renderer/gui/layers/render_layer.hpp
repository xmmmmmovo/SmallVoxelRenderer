//
// Created by xmmmmmovo on 2023/7/4.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP


#include "core/noncopyable.hpp"
#include "graphics/opengl/ogl_pipeline.hpp"
#include "graphics/opengl/ogl_renderpass.hpp"
#include "graphics/opengl/ogl_shader.hpp"
#include "gui/layers/layer.hpp"

#include <main_frag_gl.h>
#include <main_vert_gl.h>

namespace voxel {

class RenderLayer final : private NonCopyable, public ILayer {
private:
    std::vector<float> vertices = {
            0.5f,  0.5f,  0.0f,// top right
            0.5f,  -0.5f, 0.0f,// bottom right
            -0.5f, -0.5f, 0.0f,// bottom left
            -0.5f, 0.5f,  0.0f // top left
    };
    std::vector<unsigned int> indices{
            // note that we start from 0!
            0, 1, 3,// first Triangle
            1, 2, 3 // second Triangle
    };
    unsigned int VBO, VAO, EBO;

    std::unique_ptr<OGLPipeline> _main_pipeline{nullptr};

public:
    void init() noexcept override {
        OGLPipelineDescription _main_pipeline_description{};
        _main_pipeline = std::make_unique<OGLPipeline>(
                std::move(_main_pipeline_description));
    }

    void update() noexcept override {}

    ~RenderLayer() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
