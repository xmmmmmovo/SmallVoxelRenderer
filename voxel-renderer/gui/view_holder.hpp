//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
#define VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP

#include "graphics/adapters/graphics_adapter.hpp"
#include "gui/imgui/adapters/imgui_adapter.hpp"
#include <functional>
#include <memory>
#include <string>

#include <volk.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

constexpr std::string_view WINDOW_TITLE  = "Voxel VoxelRenderer";
constexpr std::uint32_t    WINDOW_WIDTH  = 1366;
constexpr std::uint32_t    WINDOW_HEIGHT = 768;

class ViewHolder final {
private:
    GLFWwindow           *_window = nullptr;
    std::function<void()> _update_func;

    std::unique_ptr<IGraphicsAdapter> _gl_adapter;
    std::unique_ptr<IImGuiAdapter>    _imgui_adapter;

    bool is_vsync = false;

private:
    static void framebufferSizeCallback(GLFWwindow *window, int width,
                                        int height) noexcept {
        auto *holder =
                static_cast<ViewHolder *>(glfwGetWindowUserPointer(window));
        holder->_gl_adapter->resize(width, height);
    }

public:
    void init(std::unique_ptr<IGraphicsAdapter> adapter,
              std::unique_ptr<IImGuiAdapter>    imgui_adapter) {
        spdlog::info("Init window");
        glfwInit();
        adapter->initForWindow();
        _window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT,
                                   WINDOW_TITLE.data(), nullptr, nullptr);
        if (!_window) {
            spdlog::error("Failed to create window");
            glfwTerminate();
        }
        glfwSetWindowUserPointer(_window, this);
        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
        adapter->initForApi(_window);
        imgui_adapter->init(_window);

        _gl_adapter    = std::move(adapter);
        _imgui_adapter = std::move(imgui_adapter);
    }

    void destroy() {
        spdlog::info("Destroy window");
        if (_window) {
            glfwDestroyWindow(_window);
            glfwTerminate();
        }
    }

    void setVsync(bool enable) noexcept {
        glfwSwapInterval(enable ? 1 : 0);
        is_vsync = enable;
    }

    void setUpdateFunc(std::function<void()> func) noexcept {
        _update_func = std::move(func);
    }

    void mainLoop() noexcept {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
            _gl_adapter->update();
            _imgui_adapter->newFrame();
            _update_func();
            _imgui_adapter->render();
            _gl_adapter->swapBuffers();
        }
    }

    [[nodiscard]] GLFWwindow const *getWindow() const noexcept {
        return _window;
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
