//
// Created by xmmmmmovo on 2023/7/16.
//

#ifndef VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
#define VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

namespace voxel {

struct ImGuiState final {
    ImGuiContext *context;
    ImGuiIO      *io;
    ImGuiStyle   *style;
};

}

#endif//VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
