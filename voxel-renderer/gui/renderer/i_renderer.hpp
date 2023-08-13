//
// Created by xmmmmmovo on 10/08/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_IRENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_IRENDERER_HPP

#include "marcher_frag_gl.h"
#include "marcher_vert_gl.h"
#include "quad_frag_gl.h"
#include "quad_vert_gl.h"
#include "raycaster_frag_gl.h"
#include "raycaster_vert_gl.h"
#include "splat_frag_gl.h"
#include "splat_vert_gl.h"

#include "gui/render_layer_ctx.hpp"

namespace voxel {

class IRenderer {
public:
    virtual void init(RenderLayerContext *ctx) noexcept = 0;

    virtual void update(float delta_t) noexcept = 0;

    virtual ~IRenderer() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDERER_IRENDERER_HPP
