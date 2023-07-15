//
// Created by xmmmmmovo on 2023/7/5.
//

#ifndef VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
#define VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP

#include <string>

#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

constexpr std::string_view WINDOW_TITLE  = "Voxel Renderer";
constexpr std::uint32_t    WINDOW_WIDTH  = 800;
constexpr std::uint32_t    WINDOW_HEIGHT = 600;

struct ViewHolderContext {
    std::uint32_t width{WINDOW_WIDTH};
    std::uint32_t height{WINDOW_HEIGHT};
};

struct ViewHolder final {
    GLFWwindow       *window{nullptr};
    ViewHolderContext context{};
};

GLFWwindow *createGLFWwindow(ViewHolderContext &context) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow *window = glfwCreateWindow(
            WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.data(), nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    glfwSetWindowUserPointer(window, &context);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(
            window, [](GLFWwindow *window, int width, int height) {
                auto *context = reinterpret_cast<ViewHolderContext *>(
                        glfwGetWindowUserPointer(window));
                context->width  = width;
                context->height = height;
            });

    return window;
}

void destroyGLFWwindow(GLFWwindow *window) {
    glfwDestroyWindow(window);
    glfwTerminate();
}

void initGraphicsAPI() {}

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_VIEW_HOLDER_HPP
