//
// Created by xmmmmmovo on 2023/7/4.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP


#include "core/noncopyable.hpp"
#include "gui/layers/layer.hpp"

namespace voxel {

class RenderLayer final : private Noncopyable, public ILayer {
public:
    void init() noexcept override {}

    void update() noexcept override {}

    ~RenderLayer() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
