//
// Created by xmmmmmovo on 2023/7/16.
//

#ifndef VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
#define VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

namespace voxel {

enum class RendererType { DEFAULT = 0, CPU_SPLATTING = 1 };

struct ImGuiLayerContext final {
    ImGuiIO    *io{nullptr};
    ImGuiStyle *style{nullptr};

    RendererType current_renderer{RendererType::CPU_SPLATTING};

    bool show_control_window{true};
    bool show_debug_window{false};
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
