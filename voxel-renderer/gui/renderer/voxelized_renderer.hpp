//
// Created by xmmmmmovo on 07/09/2023.
//

#ifndef VOXEL_RENDERER_GUI_RENDERER_VOXELIZED_RENDERER_HPP
#define VOXEL_RENDERER_GUI_RENDERER_VOXELIZED_RENDERER_HPP

#include "i_renderer.hpp"

namespace voxel {

class VoxelizedRenderer final : public IRenderer {

public:
    void init(RenderLayerContext *ctx) noexcept override {}
    void update(float delta_t) noexcept override {}
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_RENDERER_VOXELIZED_RENDERER_HPP
