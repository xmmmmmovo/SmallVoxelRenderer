//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDERER_HPP

#include "gui/layers/imgui_layer.hpp"
#include "gui/layers/render_layer.hpp"
#include "gui/view_holder.hpp"
#include "input/input_system.hpp"

namespace voxel {

class Renderer {
private:
    RenderLayer _render_layer;
    ImGuiLayer  _imgui_layer;
    ViewHolder  _view_holder;
    InputSystem _input_system;

private:
    static inline void clear() noexcept {
    }

public:
    void init() noexcept {
        _view_holder.window = createGLFWwindow(_view_holder.context);
        _input_system.init(_view_holder.window);
        initGraphicsAPI();
        _render_layer.init(_view_holder.window);
        _imgui_layer.init(_view_holder.window);
    }

    void update() noexcept {
        _render_layer.update();
        _imgui_layer.update();
    }

    void start() noexcept {
        while (!glfwWindowShouldClose(_view_holder.window)) {
            clear();
            update();
            glfwSwapBuffers(_view_holder.window);
            glfwPollEvents();
        }
    }

    ~Renderer() noexcept { destroyGLFWwindow(_view_holder.window); };
};

}// namespace voxel

#endif// VOXEL_RENDERER_GRAPHICS_RENDERER_HPP
