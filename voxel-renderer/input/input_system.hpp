//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP
#define VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP

#include "gui/view_holder.hpp"
#include "input_state.hpp"

namespace voxel {

class InputSystem final {
private:
    InputState _input_state;

public:
    void init(GLFWwindow *window) noexcept {}

    [[nodiscard]] bool getInputState(int key) const noexcept {
        return _input_state.keys[key] == 1;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_INPUT_INPUT_SYSTEM_HPP
