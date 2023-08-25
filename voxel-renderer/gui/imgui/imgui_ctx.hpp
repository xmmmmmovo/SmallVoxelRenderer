//
// Created by xmmmmmovo on 2023/7/16.
//

#ifndef VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
#define VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

namespace voxel {

enum class RendererType {
    DEFAULT         = 0,
    POINT_SPLATTING = 1,
    MARCHER         = 2,
    SVO             = 3,
    VDB             = 4
};

struct ImGuiLayerContext final {
    ImGuiIO    *io{nullptr};
    ImGuiStyle *style{nullptr};

    RendererType current_renderer{RendererType::MARCHER};

    std::filesystem::path volume_path{};

    bool show_control_window{true};
    bool show_debug_window{false};
    bool is_wireframe{false};
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
