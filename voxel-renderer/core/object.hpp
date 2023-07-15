//
// Created by xmmmmmovo on 2023/7/4.
//

#ifndef VOXEL_RENDERER_CORE_OBJECT_HPP
#define VOXEL_RENDERER_CORE_OBJECT_HPP

#include <GLFW/glfw3.h>

namespace voxel {

class RenderLoopObject {
public:
    virtual void init(GLFWwindow *window) noexcept = 0;
    virtual void update() noexcept                 = 0;
    virtual ~RenderLoopObject() noexcept           = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_OBJECT_HPP
