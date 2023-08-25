//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_HPP

#include "core/clock.hpp"
#include "core/config.hpp"
#include "graphics/adapters/ogl_adapter.hpp"
#include "gui/imgui/adapters/imgui_opengl_adapter.hpp"
#include "gui/imgui/imgui_layer.hpp"
#include "gui/render_layer.hpp"
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

    Clock _clock;

public:
    void init() noexcept {
        spdlog::info("Init VoxelRenderer");
        std::unique_ptr<OGLAdapter> ogl_adapter =
                std::make_unique<OGLAdapter>();
        std::unique_ptr<OGLImguiAdapter> imgui_adapter =
                std::make_unique<OGLImguiAdapter>();
        _view_holder.init({
                .gl_adapter    = std::move(ogl_adapter),
                .imgui_adapter = std::move(imgui_adapter),
                .is_vsync      = true,
                .window_title  = WINDOW_TITLE,
                .window_width  = WINDOW_WIDTH,
                .window_height = WINDOW_HEIGHT,
        });

        _imgui_layer.init();
        _render_layer.init(_imgui_layer.getImGuiCtx());
    }

    void update() noexcept {
        _clock.update();
        _render_layer.update(_clock.getDeltaTime());
        _imgui_layer.update(_clock.getDeltaTime());
    }

    void start() noexcept {
        _view_holder.setUpdateFunc([this]() { this->update(); });
        _view_holder.mainLoop();
    }

    void destroy() noexcept { _view_holder.destroy(); }
};

}// namespace voxel

#endif// VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
