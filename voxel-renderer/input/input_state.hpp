//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_INPUT_INPUT_STATE_HPP
#define VOXEL_RENDERER_INPUT_INPUT_STATE_HPP

#include <array>

namespace voxel {

struct InputState {
    std::array<std::int16_t, std::numeric_limits<std::int16_t>::max()> keys{};

    float mouse_x{0.0f}, mouse_y{0.0f};

    float mouse_scroll_offset_x{0.0f}, mouse_scroll_offset_y{0.0f};

    bool was_mouse_scrolling{false};

    InputState() { keys.fill(0); }
};

}

#endif//VOXEL_RENDERER_INPUT_INPUT_STATE_HPP
