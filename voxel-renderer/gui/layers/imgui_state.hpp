//
// Created by xmmmmmovo on 2023/7/16.
//

#ifndef VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
#define VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

namespace voxel {

struct ImGuiState final {
    ImGuiIO    *io;
    ImGuiStyle *style;

    bool show_demo_window = true;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
