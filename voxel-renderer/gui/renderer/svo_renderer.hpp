//
// Created by xmmmmmovo on 13/08/2023.
//

#ifndef VOXEL_RENDERER_GUI_RENDERER_SVO_RENDERER_HPP
#define VOXEL_RENDERER_GUI_RENDERER_SVO_RENDERER_HPP

#include "i_renderer.hpp"
#include "reader/object_reader.hpp"
#include "reader/read_data_types.hpp"

namespace voxel {

class SVORenderer final : public IRenderer {
    MeshObj mesh_obj{};

public:
    void init(RenderLayerContext *ctx) noexcept override {}

    void update(float delta_t) noexcept override {}
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_RENDERER_SVO_RENDERER_HPP
