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
    VOXELIZED       = 3,
    SVO             = 4,
    VDB             = 5
};

enum class ASSET_TYPE { RAW = 0, OBJ = 1, PLY = 2, VDB = 3 };

static constexpr std::array<std::string_view, 6> RENDERER_ITEMS = {
        "Default", "Point Splatting", "Marcher", "Voxelized", "SVO", "VDB"};

struct ImGuiLayerContext final {
    ImGuiIO    *io{nullptr};
    ImGuiStyle *style{nullptr};

    RendererType current_renderer{RendererType::DEFAULT};

    bool                  is_file_selected{false}, is_loaded{false};
    std::filesystem::path file_path{};
    ASSET_TYPE            asset_type{ASSET_TYPE::RAW};

    static constexpr std::uint8_t DEFAULT_TREE_LEVEL{8};

    std::int32_t tree_level{DEFAULT_TREE_LEVEL};
    std::int32_t voxel_size{1 << DEFAULT_TREE_LEVEL};

    bool show_control_window{true};
    bool show_debug_window{false};
    bool is_wireframe{false};
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_LAYERS_IMGUI_STATE_HPP
