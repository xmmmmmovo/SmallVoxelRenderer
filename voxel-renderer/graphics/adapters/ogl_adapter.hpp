//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP
#define VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP

#include "core/defines.hpp"
#include "graphics_adapter.hpp"
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

class OGLAdapter : public IGraphicsAdapter {
public:
    void initForWindow() const noexcept override {
        spdlog::info("OGLAdapter window init");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    }

    void initForApi(GLFWwindow *window) const noexcept override {
        spdlog::info("OGLAdapter api init");

        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(
                    reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            spdlog::error("Failed to initialize GLAD");
            abort();
        }

        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void resize(int width, int height) const noexcept override {
        glViewport(0, 0, width, height);
    }

    void swapBuffers() const noexcept override {
        glfwSwapBuffers(glfwGetCurrentContext());
    }

    ~OGLAdapter() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP
