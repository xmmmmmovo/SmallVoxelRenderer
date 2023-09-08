//
// Created by xmmmmmovo on 10/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_POINT_SPLATTING_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_POINT_SPLATTING_RENDERER_HPP

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

class PointSplattingRenderer final : public IRenderer {
private:
    std::unique_ptr<OGLPipeline>   _splat_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _splat_render_pass{nullptr};

    std::unique_ptr<OGLPipeline>   _swap_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _swap_render_pass{nullptr};

    RenderLayerContext *_ctx;

    std::vector<glm::vec3> _splat_pos{};
    std::vector<glm::vec3> _splat_normal{};

    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> _splat_pos_buffer{
            nullptr};
    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> _splat_normal_buffer{
            nullptr};
    std::unique_ptr<OGLVertexArray> _splat_vao{nullptr};

    glm::vec3 _inv_dim{1.0f / DFT_X_DIM, 1.0f / DFT_Y_DIM, 1.0f / DFT_Z_DIM};
    GLubyte   _iso_value{40};
    glm::vec3 _scale{};
    std::uint32_t _x_sample_dist{64}, _y_sample_dist{64}, _z_sample_dist{64};

private:
    glm::vec3 calcuNormal(std::int32_t const x, std::int32_t const y,
                          std::int32_t const z) {
        return glm::normalize(glm::vec3{
                (sampleVolume(x - _scale.x, y, z)) / (2 * _scale.x),
                (sampleVolume(x, y - _scale.y, z)) / (2 * _scale.y),
                (sampleVolume(x, y, z - _scale.z)) / (2 * _scale.z),
        });
    }

    std::uint8_t sampleVolume(std::int32_t const x, std::int32_t const y,
                              std::int32_t const z) {
        std::int32_t index =
                (x + (y * DFT_X_DIM)) + z * (DFT_X_DIM * DFT_Y_DIM);
        if (index < 0) { index = 0; }
        if (index >= DFT_X_DIM * DFT_Y_DIM * DFT_Z_DIM) {
            index = (DFT_X_DIM * DFT_Y_DIM * DFT_Z_DIM) - 1;
        }
        return _ctx->_volume_image.value().data[index];
    }

    void sampleVoxel(std::int32_t const x, std::int32_t const y,
                     std::int32_t const z) {
        std::uint8_t const data = sampleVolume(x, y, z);
        if (data > _iso_value) {
            glm::vec3 pos = glm::vec3(x, y, z);
            pos *= _inv_dim;
            _splat_pos.emplace_back(pos);
            _splat_normal.emplace_back(calcuNormal(x, y, z));
        }
    }

    void splatVolume() {
        std::uint32_t const dx = DFT_X_DIM / _x_sample_dist;
        std::uint32_t const dy = DFT_Y_DIM / _y_sample_dist;
        std::uint32_t const dz = DFT_Z_DIM / _z_sample_dist;
        _scale                 = glm::vec3(dx, dy, dz);

        for (std::uint32_t z = 0; z < DFT_X_DIM; z += dz) {
            for (std::uint32_t y = 0; y < DFT_Y_DIM; y += dy) {
                for (std::uint32_t x = 0; x < DFT_Z_DIM; x += dx) {
                    sampleVoxel(x, y, z);
                }
            }
        }
    }

public:
    void init(RenderLayerContext *ctx) noexcept override {
        _ctx = ctx;

        OGLShaderProgram splat_shader_program;
        splat_shader_program.attach(_ctx->splat_vert_shader);
        splat_shader_program.attach(_ctx->splat_frag_shader);
        splat_shader_program.link();
        OGLPipelineDescription splat_pipeline_description{
                ._shader_program = std::move(splat_shader_program),
        };
        std::int32_t const width = 1366, height = 768;

        _splat_pipeline = std::make_unique<OGLPipeline>(
                std::move(splat_pipeline_description));

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
        attachment_image.data   = nullptr;
        attachment_image.width  = width;
        attachment_image.height = height;
        color_attachments[0].uploadData(attachment_image);
        color_attachments[0].unbind();

        _splat_render_pass = std::make_unique<
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
                                .internal_format = GL_DEPTH24_STENCIL8,
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

        splatVolume();

        _splat_vao        = std::make_unique<OGLVertexArray>();
        _splat_pos_buffer = std::make_unique<OGLBuffer<std::vector<glm::vec3>>>(
                OGLBufferDescription{OGLBufferType::VERTEX}, _splat_pos);
        _splat_normal_buffer =
                std::make_unique<OGLBuffer<std::vector<glm::vec3>>>(
                        OGLBufferDescription{OGLBufferType::VERTEX},
                        _splat_normal);
        _splat_vao->bind();
        _splat_vao->bindBuffer(*_splat_pos_buffer);
        _splat_vao->bindBuffer(*_splat_normal_buffer);
        _splat_vao->unbind();
    }

    void update(float /*delta_t*/) noexcept override {
        _splat_render_pass->use();
        glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
        _splat_pipeline->use();

        // splat pass
        _splat_vao->bind();
        _splat_vao->draw(GL_POINTS, _splat_pos.size());

        glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
        _splat_render_pass->unuse();

        // swapchain pass
        _swap_render_pass->use();
        _swap_pipeline->use();

        OGLTexture::activeSlot(0);
        _splat_render_pass->getColorAttachment(0).bind();

        _ctx->_common_vbuffer.quad_vao.bind();
        _ctx->_common_vbuffer.quad_vao.draw();
        _ctx->_common_vbuffer.quad_vao.unbind();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_POINT_SPLATTING_RENDERER_HPP
