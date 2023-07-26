//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_HPP

#include "gui/layers/imgui_layer.hpp"
#include "gui/layers/render_layer.hpp"
#include "gui/view_holder.hpp"
#include "input/input_system.hpp"
#include "spdlog/spdlog.h"

namespace voxel {

class Renderer {
private:
    RenderLayer _render_layer;
    ImGuiLayer  _imgui_layer;
    InputSystem _input_system;

private:
    static inline void clear() noexcept {}

public:
    void init() noexcept {}

    void update() noexcept {
        _render_layer.update();
        _imgui_layer.update();
    }

    void start() noexcept {}

    ~Renderer() noexcept {};
};

}// namespace voxel

#endif// VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
