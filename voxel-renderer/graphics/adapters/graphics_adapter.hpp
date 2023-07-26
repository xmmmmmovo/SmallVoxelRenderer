//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP
#define VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP

namespace voxel {

class IGraphicsAdapter {
public:
    virtual void initForWindow() const noexcept = 0;
    virtual void initForApi() const noexcept    = 0;

    virtual void update() noexcept = 0;

    virtual ~IGraphicsAdapter() noexcept = 0;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_ADAPTERS_GRAPHICS_ADAPTER_HPP
