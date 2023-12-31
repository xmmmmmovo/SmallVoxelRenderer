//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP

#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

#include "core/noncopyable.hpp"
#include "imgui_ctx.hpp"
#include "os/file.hpp"
#include "voxelizer/config.hpp"

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

    static void buildDeviceInfo() noexcept {
        ImGui::Text("Device: %s", glGetString(GL_RENDERER));
        ImGui::Text("OpenGL version: %s", glGetString(GL_VERSION));
    }

    void dataChooser() {
        ImGui::Text("Choose the data:");

        static constexpr int LEN = 1024;
        static char path[LEN]    = "../../resources/model/bunny.obj";// NOLINT
        ImGui::InputText("path", path, LEN);
        ImGui::SameLine();
        if (ImGui::Button("Load")) {
            _imgui_ctx->file_path        = path;
            _imgui_ctx->is_file_selected = true;
            _imgui_ctx->is_loaded        = false;

            std::string const ext = getLastExtension(_imgui_ctx->file_path);
            if (ext == ".raw") {
                _imgui_ctx->asset_type       = ASSET_TYPE::RAW;
                _imgui_ctx->current_renderer = RendererType::DEFAULT;
            } else if (ext == ".obj") {
                _imgui_ctx->asset_type       = ASSET_TYPE::OBJ;
                _imgui_ctx->current_renderer = RendererType::VOXELIZED;
            } else if (ext == ".ply") {
                _imgui_ctx->asset_type       = ASSET_TYPE::PLY;
                _imgui_ctx->current_renderer = RendererType::VOXELIZED;
            } else if (ext == ".vdb") {
                _imgui_ctx->asset_type       = ASSET_TYPE::VDB;
                _imgui_ctx->current_renderer = RendererType::VDB;
            }
        }
    }

    void buildRendererChooser() {
        ImGui::Text("Choose the volume renderer:");

        // combo box
        if (ImGui::BeginCombo(
                    "Renderer",
                    RENDERER_ITEMS[static_cast<std::size_t>(
                                           _imgui_ctx->current_renderer)]
                            .data())) {

            static auto const kAddSelectableFn = [this](RendererType type) {
                bool const is_selected = (_imgui_ctx->current_renderer == type);
                if (ImGui::Selectable(
                            RENDERER_ITEMS[static_cast<std::size_t>(type)]
                                    .data(),
                            is_selected)) {
                    _imgui_ctx->current_renderer = type;
                }
                if (is_selected) { ImGui::SetItemDefaultFocus(); }
            };

            if (_imgui_ctx->is_loaded) {
                if (_imgui_ctx->asset_type == ASSET_TYPE::RAW) {
                    kAddSelectableFn(RendererType::DEFAULT);
                    kAddSelectableFn(RendererType::POINT_SPLATTING);
                    kAddSelectableFn(RendererType::MARCHER);
                } else if (_imgui_ctx->asset_type == ASSET_TYPE::OBJ) {
                    _imgui_ctx->current_renderer = RendererType::VOXELIZED;
                    kAddSelectableFn(RendererType::VOXELIZED);
                    kAddSelectableFn(RendererType::SVO);
                    kAddSelectableFn(RendererType::VDB);
                }
            }

            ImGui::EndCombo();
        }

        if (_imgui_ctx->current_renderer == RendererType::MARCHER) {
            ImGui::Checkbox("Wireframe", &_imgui_ctx->is_wireframe);
        }

        if (_imgui_ctx->current_renderer == RendererType::VOXELIZED ||
            _imgui_ctx->current_renderer == RendererType::SVO ||
            _imgui_ctx->current_renderer == RendererType::VDB) {
            static ImGuiSliderFlags const kSliderFlags = ImGuiSliderFlags_None;

            if (ImGui::InputInt("tree level", &_imgui_ctx->tree_level)) {
                if (MAX_TREE_LEVEL < _imgui_ctx->tree_level) {
                    _imgui_ctx->tree_level = MAX_TREE_LEVEL;
                } else if (MIN_TREE_LEVEL > _imgui_ctx->tree_level) {
                    _imgui_ctx->tree_level = MIN_TREE_LEVEL;
                }
                _imgui_ctx->voxel_size = 1 << _imgui_ctx->tree_level;
            }
            ImGui::Text("voxel level: %d", _imgui_ctx->voxel_size);
        }
    }

    void buildDebugWindow() {
        if (ImGui::Button("Show Debug Window")) {
            _imgui_ctx->show_debug_window = true;
        }
    }

    void update(float /*delta_t*/) noexcept {
        if (_imgui_ctx->show_control_window) {
            if (ImGui::Begin("control panel", nullptr)) {

                buildDeviceInfo();
                ImGui::Separator();

                dataChooser();
                ImGui::Separator();
                buildRendererChooser();
                buildDebugWindow();

                ImGui::End();
            }
        }

        if (_imgui_ctx->show_debug_window) {
            ImGui::ShowMetricsWindow(&_imgui_ctx->show_debug_window);
        }
    }

    ~ImGuiLayer() noexcept override = default;

    [[nodiscard]] ImGuiLayerContext *getImGuiCtx() noexcept {
        return _imgui_ctx.get();
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_IMGUI_LAYER_HPP
