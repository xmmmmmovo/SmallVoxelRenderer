//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP

#include "backends/imgui_impl_glfw.h"
#include "gui/layers/layer.hpp"
#include "imgui.h"

#include "core/noncopyable.hpp"
#include "imgui_state.hpp"

namespace voxel {

/**
 * @brief imgui渲染层
 */
class ImGuiLayer final : private NonCopyable, public ILayer {
private:
    ImGuiState _imgui_state;

public:
    void init() noexcept override {
        _imgui_state.io    = &ImGui::GetIO();
        _imgui_state.style = &ImGui::GetStyle();
    }

    void update() noexcept override {
        ImGui::ShowDemoWindow(&_imgui_state.show_demo_window);
        ImGui::ShowMetricsWindow(&_imgui_state.show_demo_window);
    }

    ~ImGuiLayer() noexcept override = default;

    [[nodiscard]] ImGuiState const &getImGuiState() noexcept {
        return _imgui_state;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
