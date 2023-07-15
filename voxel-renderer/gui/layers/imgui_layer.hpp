//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

#include "core/noncopyable.hpp"
#include "core/object.hpp"

namespace voxel {

struct ImGuiState {
    ImGuiContext *context;
    ImGuiIO      *io;
    ImGuiStyle   *style;
};

/**
 * @brief imgui渲染层
 */
class ImGuiLayer final : private Noncopyable, public RenderLoopObject {
private:
    ImGuiState _imgui_state;

public:
    void init(GLFWwindow *window) noexcept override {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        _imgui_state.context = ImGui::GetCurrentContext();
        _imgui_state.io      = &ImGui::GetIO();
        (void) _imgui_state.io;
        _imgui_state.style = &ImGui::GetStyle();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
    }

    void update() noexcept override {}

    ~ImGuiLayer() noexcept override {
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };

    [[nodiscard]] ImGuiState const &getImGuiState() noexcept {
        return _imgui_state;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
