//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP
#define VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP

#include "core/defines.hpp"
#include "graphics_adapter.hpp"

#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <spdlog/spdlog.h>

namespace voxel {

class OGLAdapter : public IGraphicsAdapter {
public:
    void initForWindow() const noexcept override {
        spdlog::info("OGLAdapter init");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    void initForApi() const noexcept override {
        spdlog::info("OGLAdapter api init");
        if (!gladLoadGLLoader(
                    reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
            spdlog::error("Failed to initialize GLAD");
            abort();
        }
    }

    ~OGLAdapter() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_ADAPTERS_OGL_ADAPTER_HPP
