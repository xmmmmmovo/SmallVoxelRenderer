//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
#define VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP

#include "input/input_system.hpp"
#include "view_holder_ctx.hpp"

#include <functional>
#include <memory>
#include <string>

#include <volk.h>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

class ViewHolder final {
private:
    ViewHolderContext     _context{};
    GLFWwindow           *_window{nullptr};
    std::function<void()> _update_func;
    bool                  _is_capture_mouse = false;

private:
    static void framebufferSizeCallback(GLFWwindow *window, int width,
                                        int height) noexcept {
        auto *context = static_cast<ViewHolderContext *>(
                glfwGetWindowUserPointer(window));
        context->gl_adapter->resize(width, height);
        spdlog::info("Resize window to {}x{}", width, height);
    }

    static void mouseMoveCallback(GLFWwindow *window, double xposIn,
                                  double yposIn) {
        static InputSystem &input{InputSystem::getInstance()};
        input.mouse_pos_x = static_cast<float>(xposIn);
        input.mouse_pos_y = static_cast<float>(yposIn);
    }

    static void mouseScrollCallback(GLFWwindow *window, double xoffset,
                                    double yoffset) {
        static InputSystem &input{InputSystem::getInstance()};

        if (static_cast<float>(xoffset) == input.mouse_scroll_offset_x &&
            static_cast<float>(yoffset) == input.mouse_scroll_offset_y) {
            input.was_mouse_scrolling = false;
            return;
        }

        if (!input.was_mouse_scrolling) { input.was_mouse_scrolling = true; }
        input.mouse_scroll_offset_x = static_cast<float>(xoffset);
        input.mouse_scroll_offset_y = static_cast<float>(yoffset);
    }

    static void keyCallback(GLFWwindow *window, int key, int scancode,
                            int action, int mods) {
        static InputSystem &input{InputSystem::getInstance()};

        if (action == GLFW_PRESS) {
            input.down(key);
        } else if (action == GLFW_RELEASE) {
            input.up(key);
        }
    }

    static void mouseButtonCallback(GLFWwindow *window, int button, int action,
                                    int mods) {
        static InputSystem &input{InputSystem::getInstance()};

        if (action == GLFW_PRESS) {
            input.down(button);
        } else if (action == GLFW_RELEASE) {
            input.up(button);
        }
    }

private:
    void processInput() {
        static InputSystem const &input{InputSystem::getInstance()};
        if (input.getKeyInputState(GLFW_KEY_ESCAPE)) {
            glfwSetWindowShouldClose(_window, true);
        } else if (input.getKeyInputState(GLFW_KEY_F1)) {
            _context.is_vsync = !_context.is_vsync;
            glfwSwapInterval(_context.is_vsync);
        }
        if (input.getKeyInputState(GLFW_MOUSE_BUTTON_2)) {
            if (!_is_capture_mouse) {
                glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                _is_capture_mouse = true;
            }
        } else {
            if (_is_capture_mouse) {
                glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                _is_capture_mouse = false;
            }
        }
    }

public:
    void init(ViewHolderContext context) {
        _context = std::move(context);
        spdlog::info("Init window");
        glfwInit();
        _context.gl_adapter->initForWindow();
        _window = glfwCreateWindow(
                _context.window_width, _context.window_height,
                _context.window_title.data(), nullptr, nullptr);
        if (!_window) {
            spdlog::error("Failed to create window");
            glfwTerminate();
        }
        glfwSetWindowUserPointer(_window, &_context);

        glfwSetFramebufferSizeCallback(_window, framebufferSizeCallback);
        glfwSetCursorPosCallback(_window, mouseMoveCallback);
        glfwSetScrollCallback(_window, mouseScrollCallback);
        glfwSetKeyCallback(_window, keyCallback);
        glfwSetMouseButtonCallback(_window, mouseButtonCallback);

        _context.gl_adapter->initForApi(_window);
        _context.imgui_adapter->init(_window);
        setVsync(_context.is_vsync);
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
        _context.is_vsync = enable;
    }

    void setUpdateFunc(std::function<void()> func) noexcept {
        _update_func = std::move(func);
    }

    void mainLoop() noexcept {
        while (!glfwWindowShouldClose(_window)) {
            glfwPollEvents();
            processInput();
            _context.imgui_adapter->newFrame();
            _update_func();
            _context.imgui_adapter->render();
            _context.gl_adapter->swapBuffers();
        }
    }

    [[nodiscard]] GLFWwindow const *getWindow() const noexcept {
        return _window;
    }

    ViewHolderContext *getContextPtr() noexcept { return &_context; }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
