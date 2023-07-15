//
// Created by xmmmmmovo on 2023/7/4.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP


#include "core/noncopyable.hpp"
#include "core/object.hpp"

namespace voxel {

class RenderLayer final : private Noncopyable, public RenderLoopObject {
public:
    void init(GLFWwindow *window) noexcept override {}
    void update() noexcept override {}
    ~RenderLayer() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
