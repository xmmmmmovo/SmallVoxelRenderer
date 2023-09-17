//
// Created by xmmmmmovo on 11/08/2023.
//

#ifndef VOXEL_RENDERER_GUI_RENDER_LAYER_CTX_HPP
#define VOXEL_RENDERER_GUI_RENDER_LAYER_CTX_HPP

#include "graphics/common/common_vertex_buffer.hpp"

namespace voxel {

struct RenderLayerContext {
    CommonVertexBuffer _common_vbuffer{};
    OGLShader          ray_caster_vert_shader{};
    OGLShader          ray_caster_frag_shader{};
    OGLShader          splat_vert_shader{};
    OGLShader          splat_frag_shader{};
    OGLShader          quad_vert_shader{};
    OGLShader          quad_frag_shader{};
    OGLShader          marcher_vert_shader{};
    OGLShader          marcher_frag_shader{};

    std::optional<Image> _volume_image{std::nullopt};
    std::optional<Model> _mesh_obj{std::nullopt};

    RenderLayerContext() {
        ray_caster_vert_shader.initShaderFromSource(OGLShaderType::VERTEX,
                                                    RAYCASTER_VERT_GL);
        ray_caster_frag_shader.initShaderFromSource(OGLShaderType::FRAGMENT,
                                                    RAYCASTER_FRAG_GL);
        splat_vert_shader.initShaderFromSource(OGLShaderType::VERTEX,
                                               SPLAT_VERT_GL);
        splat_frag_shader.initShaderFromSource(OGLShaderType::FRAGMENT,
                                               SPLAT_FRAG_GL);
        quad_vert_shader.initShaderFromSource(OGLShaderType::VERTEX,
                                              QUAD_VERT_GL);
        quad_frag_shader.initShaderFromSource(OGLShaderType::FRAGMENT,
                                              QUAD_FRAG_GL);
        marcher_vert_shader.initShaderFromSource(OGLShaderType::VERTEX,
                                                 MARCHER_VERT_GL);
        marcher_frag_shader.initShaderFromSource(OGLShaderType::FRAGMENT,
                                                 MARCHER_FRAG_GL);
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_RENDER_LAYER_CTX_HPP
