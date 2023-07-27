//
// Created by xmmmmmovo on 2023/7/26.
//

#ifndef VOXEL_RENDERER_GUI_ADAPTERS_IMGUI_OPENGL_ADAPTER_HPP
#define VOXEL_RENDERER_GUI_ADAPTERS_IMGUI_OPENGL_ADAPTER_HPP

#include "core/defines.hpp"
#include "imgui_adapter.hpp"

#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include <imgui.h>

namespace voxel {
class OGLImguiAdapter : public IImGuiAdapter {
public:
    void init(GLFWwindow *window) noexcept override {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |=
                ImGuiConfigFlags_NavEnableKeyboard;// Enable Keyboard Controls
        io.ConfigFlags |=
                ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(OPENGL_VERSION.data());
    }

    void newFrame() noexcept override {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void render() noexcept override {
        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    ~OGLImguiAdapter() noexcept override {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    };
};
}// namespace voxel


#endif//VOXEL_RENDERER_GUI_ADAPTERS_IMGUI_OPENGL_ADAPTER_HPP
