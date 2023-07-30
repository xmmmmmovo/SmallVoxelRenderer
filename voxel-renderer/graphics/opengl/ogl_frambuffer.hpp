//
// Created by xmmmmmovo on 29/07/2023.
//

#ifndef VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP
#define VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP

#include <optional>
#include <utility>
#include <vector>

#include "ogl_texture.hpp"

namespace voxel {

struct OGLFramebufferDescription final {
    int  width{0};
    int  height{0};
    int  samples{1};
    int  mip_levels{1};
    int  attachment_count{0};
    int  color_attachment_count{0};
    int  depth_stencil_attachment_count{0};
    bool swapchain_target{false};

    std::vector<OGLTexture>   color_attachments{};
    std::optional<OGLTexture> depth_stencil_attachment{std::nullopt};
};

class OGLFramebuffer final {
private:
    OGLFramebufferDescription _description;

public:
    explicit OGLFramebuffer(OGLFramebufferDescription description)
        : _description(std::move(description)){
                  

          };
    ~OGLFramebuffer() noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_OPENGL_OGL_FRAMBUFFER_HPP
