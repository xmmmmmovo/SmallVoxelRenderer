//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP
#define VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP

#include <GLFW/glfw3.h>
#include <cstdint>

namespace voxel {

class IGraphicsAdapter {
public:
    virtual void initForWindow() const noexcept                = 0;
    virtual void initForApi(GLFWwindow *window) const noexcept = 0;

    virtual void update() noexcept = 0;

    virtual void resize(int width, int height) const noexcept = 0;
    virtual void swapBuffers() const noexcept                 = 0;

    virtual ~IGraphicsAdapter() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP
