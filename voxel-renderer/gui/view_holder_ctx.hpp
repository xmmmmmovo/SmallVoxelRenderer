//
// Created by xmmmmmovo on 10/08/2023.
//

#ifndef VOXEL_RENDERER_GUI_VIEW_HOLDER_CTX_HPP
#define VOXEL_RENDERER_GUI_VIEW_HOLDER_CTX_HPP

namespace voxel {

struct ViewHolderContext final {
    std::unique_ptr<IGraphicsAdapter> gl_adapter{nullptr};
    std::unique_ptr<IImGuiAdapter>    imgui_adapter{nullptr};
    bool                              is_vsync{false};

    std::string_view window_title;
    std::int32_t     window_width, window_height;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GUI_VIEW_HOLDER_CTX_HPP
