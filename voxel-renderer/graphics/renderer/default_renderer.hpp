//
// Created by xmmmmmovo on 07/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_DEFAULT_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_DEFAULT_RENDERER_HPP

#include "core/path.hpp"
#include "graphics/common/camera.hpp"
#include "graphics/opengl/ogl_pipeline.hpp"
#include "graphics/opengl/ogl_renderpass.hpp"
#include "graphics/opengl/ogl_shader.hpp"
#include "input/input_system.hpp"
#include "reader/raw_reader.hpp"

#include "i_renderer.hpp"
#include "ubuffer_struct.hpp"

namespace voxel {

class DefaultRenderer final : public IRenderer {
private:
    std::unique_ptr<OGLPipeline>   _main_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _main_render_pass{nullptr};

    std::unique_ptr<OGLBuffer<std::array<glm::vec3, 8>>>     _main_vbo{nullptr};
    std::unique_ptr<OGLBuffer<std::array<unsigned int, 36>>> _main_ebo{nullptr};
    std::unique_ptr<OGLVertexArray>                          _main_vao{nullptr};

    OGLShader _main_vert_shader{};
    OGLShader _main_frag_shader{};

    std::unique_ptr<OGLTexture> _volume_tex{nullptr};

public:
    void init() noexcept override {
        _main_vert_shader.initShaderFromSource(OGLShaderType::VERTEX,
                                               RAYCASTER_VERT_GL);
        _main_frag_shader.initShaderFromSource(OGLShaderType::FRAGMENT,
                                               RAYCASTER_FRAG_GL);

        OGLShaderProgram main_shader_program;
        main_shader_program.attach(_main_vert_shader);
        main_shader_program.attach(_main_frag_shader);
        main_shader_program.link();

        OGLPipelineDescription main_pipeline_description{
                ._shader_program = std::move(main_shader_program),
        };
        _main_pipeline = std::make_unique<OGLPipeline>(
                std::move(main_pipeline_description));

        _main_render_pass =
                std::make_unique<OGLRenderPass>(OGLRenderPassDescription{});

        _main_vao = std::make_unique<OGLVertexArray>();
        _main_vbo = std::make_unique<OGLBuffer<std::array<glm::vec3, 8>>>(
                OGLBufferDescription{OGLBufferType::VERTEX}, VERTICES);
        _main_ebo = std::make_unique<OGLBuffer<std::array<unsigned int, 36>>>(
                OGLBufferDescription{OGLBufferType::ELEMENT}, INDICES);

        _main_vao->bind();
        _main_vao->bindBuffer(*_main_vbo);
        _main_vao->bindBuffer(*_main_ebo);
        _main_vao->unbind();

        _volume_tex = std::make_unique<OGLTexture>(
                OGLTextureDescription{.dim             = TextureDim::MAP_3D,
                                      .internal_format = GL_RED,
                                      .format          = GL_RED,
                                      .min_filter = GL_LINEAR_MIPMAP_LINEAR,
                                      .wrap_s     = GL_CLAMP,
                                      .wrap_t     = GL_CLAMP,
                                      .wrap_r     = GL_CLAMP,
                                      .level      = 4,
                                      .generate_mipmap = GL_TRUE});

        _volume_tex->bind();
        _volume_tex->uploadData(
                loadRaw(DEBUG_PATH "/resources/data/Engine256.raw"));
        _volume_tex->unbind();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void update(float /*delta_t*/) noexcept override {
        _main_render_pass->use();

        glEnable(GL_BLEND);
        _main_pipeline->use();

        _volume_tex->activeSlot(0);
        _volume_tex->bind();

        _main_vao->bind();
        _main_vao->draw();
        _main_vao->unbind();

        glDisable(GL_BLEND);
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_DEFAULT_RENDERER_HPP
