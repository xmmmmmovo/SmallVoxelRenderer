//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

#include "core/noncopyable.hpp"
#include "core/object.hpp"
#include "imgui_state.hpp"

namespace voxel {

/**
 * @brief imgui渲染层
 */
class ImGuiLayer final : private Noncopyable, public RenderLoopObject {
private:
    ImGuiState _imgui_state;

public:
    void init(GLFWwindow const *window) noexcept override {}

    void update() noexcept override {}

    ~ImGuiLayer() noexcept override{};

    [[nodiscard]] ImGuiState const &getImGuiState() noexcept {
        return _imgui_state;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
