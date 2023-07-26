//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
#define VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP

#include "graphics/adapters/graphics_adapter.hpp"
#include <string>

#include <volk.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

constexpr std::string_view WINDOW_TITLE  = "Voxel Renderer";
constexpr std::uint32_t    WINDOW_WIDTH  = 800;
constexpr std::uint32_t    WINDOW_HEIGHT = 600;

class ViewHolder final {
private:
    GLFWwindow *_window = nullptr;

public:
    void init(IGraphicsAdapter const *adapter) {
        spdlog::info("Init window");
        glfwInit();
        adapter->init();
        _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                   WINDOW_TITLE.data(), nullptr, nullptr);
    }

    void destroy() {
        spdlog::info("Destroy window");
        if (_window) {
            glfwDestroyWindow(_window);
            glfwTerminate();
        }
    }

    [[nodiscard]] GLFWwindow const *getWindow() const noexcept {
        return _window;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
