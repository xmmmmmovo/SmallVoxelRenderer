//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

#include "core/noncopyable.hpp"
#include "imgui_ctx.hpp"

namespace voxel {

/**
 * @brief imgui渲染层
 */
class ImGuiLayer final : private NonCopyable {
private:
    std::unique_ptr<ImGuiLayerContext> _imgui_ctx{
            std::make_unique<ImGuiLayerContext>()};

public:
    void init() noexcept {
        _imgui_ctx->io    = &ImGui::GetIO();
        _imgui_ctx->style = &ImGui::GetStyle();
    }

    void update(float /*delta_t*/) noexcept {
        if (_imgui_ctx->show_control_window) {
            if (ImGui::Begin("control panel", nullptr)) {
                ImGui::Text("Device: %s", glGetString(GL_RENDERER));
                ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION));

                ImGui::Separator();

                ImGui::Text("Choose the data:");

                static constexpr int LEN       = 1024;
                static char          path[LEN] = "resources/data/Engine256.raw";
                ImGui::InputText("path", path, LEN);
                ImGui::SameLine();
                if (ImGui::Button("Load")) { _imgui_ctx->volume_path = path; }

                ImGui::Separator();

                ImGui::Text("Choose the volume renderer:");

                // combo box
                static std::array<std::string_view, 5> items = {
                        "Default", "Point Splatting", "Marcher", "SVO", "VDB"};
                if (ImGui::BeginCombo(
                            "Renderer",
                            items[static_cast<std::size_t>(
                                          _imgui_ctx->current_renderer)]
                                    .data())) {
                    for (int n = 0; n < items.size(); n++) {
                        bool const is_selected =
                                (_imgui_ctx->current_renderer ==
                                 static_cast<RendererType>(n));
                        if (ImGui::Selectable(items[n].data(), is_selected)) {
                            _imgui_ctx->current_renderer =
                                    static_cast<RendererType>(n);
                        }
                        if (is_selected) { ImGui::SetItemDefaultFocus(); }
                    }
                    ImGui::EndCombo();
                }

                if (ImGui::Button("Show Debug Window")) {
                    _imgui_ctx->show_debug_window = true;
                }

                if (_imgui_ctx->current_renderer == RendererType::MARCHER) {
                    ImGui::Checkbox("Wireframe", &_imgui_ctx->is_wireframe);
                }

                if (_imgui_ctx->current_renderer == RendererType::SVO ||
                    _imgui_ctx->current_renderer == RendererType::VDB) {
                    ImGui::Text("Octree Level: %d", 10);
                }

                ImGui::End();
            }
        }

        if (_imgui_ctx->show_debug_window) {
            ImGui::ShowMetricsWindow(&_imgui_ctx->show_debug_window);
        }
    }

    ~ImGuiLayer() noexcept override = default;

    [[nodiscard]] ImGuiLayerContext const *getImGuiCtx() noexcept {
        return _imgui_ctx.get();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
