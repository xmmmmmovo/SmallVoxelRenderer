//
// Created by xmmmmmovo on 10/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_CPU_SPLATTING_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_CPU_SPLATTING_RENDERER_HPP

#include "core/path.hpp"
#include "graphics/common/camera.hpp"
#include "graphics/opengl/ogl_pipeline.hpp"
#include "graphics/opengl/ogl_renderpass.hpp"
#include "graphics/opengl/ogl_shader.hpp"
#include "input/input_system.hpp"
#include "reader/raw_reader.hpp"

#include "graphics/common/common_uniform_buffer.hpp"
#include "i_renderer.hpp"

#include <vector>

namespace voxel {

class CPUSplattingRenderer final : public IRenderer {
private:
    std::unique_ptr<OGLPipeline>   _main_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _main_render_pass{nullptr};

    std::unique_ptr<OGLPipeline>   _swap_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _swap_render_pass{nullptr};

    std::unique_ptr<OGLTexture> _volume_tex{nullptr};

    RenderLayerContext *_ctx;

public:
    void init(RenderLayerContext *ctx) noexcept override {
        _ctx = ctx;

        OGLShaderProgram main_shader_program;
        main_shader_program.attach(_ctx->ray_caster_vert_shader);
        main_shader_program.attach(_ctx->ray_caster_frag_shader);
        main_shader_program.link();

        OGLPipelineDescription main_pipeline_description{
                ._shader_program = std::move(main_shader_program),
        };

        std::int32_t const width = 1366, height = 768;

        _main_pipeline = std::make_unique<OGLPipeline>(
                std::move(main_pipeline_description));

        std::vector<OGLTexture> color_attachments;
        color_attachments.emplace_back(OGLTextureDescription{
                .dim             = TextureDim::MAP_2D,
                .internal_format = GL_RGBA32F,
                .format          = GL_RGBA,
                .min_filter      = GL_LINEAR,
                .mag_filter      = GL_LINEAR,
                .wrap_s          = GL_CLAMP,
                .wrap_t          = GL_CLAMP,
                .wrap_r          = GL_CLAMP,
                .generate_mipmap = false,
        });
        color_attachments[0].bind();
        Image attachment_image{};
        attachment_image.width  = width;
        attachment_image.height = height;
        color_attachments[0].uploadData(attachment_image);
        color_attachments[0].unbind();

        _main_render_pass = std::make_unique<
                OGLRenderPass>(OGLRenderPassDescription{
                ._framebuffer = std::make_unique<
                        OGLFramebuffer>(OGLFramebufferDescription{
                        .width             = width,
                        .height            = height,
                        .color_attachments = std::move(color_attachments),
                        .depth_stencil_attachment = {std::make_optional<
                                OGLRenderBuffer>(OGLRenderBufferDescription{
                                ._width          = width,
                                ._height         = height,
                                .internal_format = GL_DEPTH_COMPONENT32,
                        })}})});

        _swap_render_pass =
                std::make_unique<OGLRenderPass>(OGLRenderPassDescription{});

        OGLShaderProgram quad_shader_program;
        quad_shader_program.attach(_ctx->quad_vert_shader);
        quad_shader_program.attach(_ctx->quad_frag_shader);
        quad_shader_program.link();

        OGLPipelineDescription quad_pipeline_description{
                ._shader_program = std::move(quad_shader_program),
        };
        _swap_pipeline = std::make_unique<OGLPipeline>(
                std::move(quad_pipeline_description));

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
        _volume_tex->uploadData(_ctx->_volume_image);
        _volume_tex->unbind();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    void update(float /*delta_t*/) noexcept override {
        _main_render_pass->use();
        glEnable(GL_BLEND);
        _main_pipeline->use();

        _volume_tex->activeSlot(0);
        _volume_tex->bind();

        _ctx->_common_vbuffer.cube_vao.bind();
        _ctx->_common_vbuffer.cube_vao.draw();
        _ctx->_common_vbuffer.cube_vao.unbind();

        _volume_tex->unbind();
        glDisable(GL_BLEND);
        _main_render_pass->unuse();

        _swap_render_pass->use();
        _swap_pipeline->use();

        OGLTexture::activeSlot(0);
        _main_render_pass->getColorAttachment(0).bind();

        _ctx->_common_vbuffer.quad_vao.bind();
        _ctx->_common_vbuffer.quad_vao.draw();
        _ctx->_common_vbuffer.quad_vao.unbind();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_CPU_SPLATTING_RENDERER_HPP
