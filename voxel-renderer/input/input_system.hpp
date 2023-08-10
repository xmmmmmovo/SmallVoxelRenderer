//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP
#define VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP

#include "core/public_singleton.hpp"
#include "key_code.hpp"

namespace voxel {

class InputSystem final : public PublicSingleton<InputSystem> {
    friend class PublicSingleton<InputSystem>;

private:
    std::array<std::int16_t, std::numeric_limits<std::int16_t>::max()> _keys{};

public:
    float mouse_pos_x{0.0f}, mouse_pos_y{0.0f};

    float mouse_scroll_offset_x{0.0f}, mouse_scroll_offset_y{0.0f};

    bool was_mouse_scrolling{false};

public:
    InputSystem() { _keys.fill(0); }

    [[nodiscard]] bool getKeyInputState(int key) const noexcept {
        return _keys[key] == 1;
    }

    void down(int key) noexcept { _keys[key] = 1; }

    void up(int key) noexcept { _keys[key] = 0; }
};

}// namespace voxel

#endif//VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP
