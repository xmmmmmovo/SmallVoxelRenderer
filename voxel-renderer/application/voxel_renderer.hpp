//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_HPP

#include "core/clock.hpp"
#include "graphics/adapters/ogl_adapter.hpp"
#include "gui/imgui/adapters/imgui_opengl_adapter.hpp"
#include "gui/layers/imgui_layer.hpp"
#include "gui/layers/render_layer.hpp"
#include "gui/view_holder.hpp"
#include "input/input_system.hpp"

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

class VoxelRenderer final {
private:
    ViewHolder _view_holder;

    RenderLayer _render_layer;
    ImGuiLayer  _imgui_layer;
    InputSystem _input_system;

    Clock _clock;

public:
    void init() noexcept {
        spdlog::info("Init VoxelRenderer");
        std::unique_ptr<OGLAdapter> ogl_adapter =
                std::make_unique<OGLAdapter>();
        std::unique_ptr<OGLImguiAdapter> imgui_adapter =
                std::make_unique<OGLImguiAdapter>();
        _view_holder.init(std::move(ogl_adapter), std::move(imgui_adapter));
        _view_holder.setVsync(true);

        _imgui_layer.init();
        _render_layer.init();
    }

    void update() noexcept {
        _clock.update();
        _render_layer.update();
        _imgui_layer.update();
    }

    void start() noexcept {
        _view_holder.setUpdateFunc([this]() { this->update(); });
        _view_holder.mainLoop();
    }

    void destroy() noexcept { _view_holder.destroy(); }
};

}// namespace voxel

#endif// VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
