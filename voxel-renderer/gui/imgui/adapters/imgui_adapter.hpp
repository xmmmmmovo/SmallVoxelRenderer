//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GUI_IMGUI_ADAPTERS_IMGUI_ADAPTER_HPP
#define VOXEL_RENDERER_GUI_IMGUI_ADAPTERS_IMGUI_ADAPTER_HPP

#include <GLFW/glfw3.h>

namespace voxel {

class IImGuiAdapter {
public:
    virtual void init(GLFWwindow const *window) noexcept = 0;

    virtual void update() noexcept = 0;

    virtual ~IImGuiAdapter() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_IMGUI_ADAPTERS_IMGUI_ADAPTER_HPP
