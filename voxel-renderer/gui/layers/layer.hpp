//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GUI_LAYERS_LAYER_HPP
#define VOXEL_RENDERER_GUI_LAYERS_LAYER_HPP

#include <GLFW/glfw3.h>

namespace voxel {

class ILayer {
public:
    virtual void init() noexcept = 0;

    virtual void update() noexcept = 0;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_LAYERS_LAYER_HPP
