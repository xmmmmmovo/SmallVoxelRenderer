//
// Created by xmmmmmovo on 2023/7/4.
//

#ifndef VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
#define VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP

#include "core/noncopyable.hpp"
#include "graphics/common/common_vertex_buffer.hpp"
#include "gui/imgui/imgui_ctx.hpp"
#include "gui/renderer/default_renderer.hpp"
#include "gui/renderer/marcher_renderer.hpp"
#include "gui/renderer/point_splatting_renderer.hpp"
#include "render_layer_ctx.hpp"

#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace voxel {

class RenderLayer final : private NonCopyable {
private:
    MatricesStruct                             _matrices{};
    std::unique_ptr<OGLBuffer<MatricesStruct>> _matrices_buffer{nullptr};

    ModelStruct                             _model{};
    std::unique_ptr<OGLBuffer<ModelStruct>> _model_buffer{nullptr};

    CameraStruct                             _camera_struct{};
    std::unique_ptr<OGLBuffer<CameraStruct>> _camera_buffer{nullptr};

    SplatStruct                             _splat_struct{};
    std::unique_ptr<OGLBuffer<SplatStruct>> _splat_buffer{nullptr};

    EulerCamera _camera{};

    bool  _first_mouse{true};
    float _mouse_last_x{0.0f}, _mouse_last_y{0.0f};

    DefaultRenderer        _dft_renderer{};
    PointSplattingRenderer _point_splatting_renderer{};
    MarcherRenderer        _marcher_renderer{};

    ImGuiLayerContext const            *_imgui_ctx{nullptr};
    std::unique_ptr<RenderLayerContext> _render_ctx{nullptr};

private:
    void processInput(float delta_t) {
        static InputSystem const &input{InputSystem::getInstance()};

        if (input.getKeyInputState(GLFW_MOUSE_BUTTON_2)) {
            if (input.getKeyInputState(GLFW_KEY_W)) {
                _camera.processKeyboard(CameraMovement::FORWARD, delta_t);
            }
            if (input.getKeyInputState(GLFW_KEY_S)) {
                _camera.processKeyboard(CameraMovement::BACKWARD, delta_t);
            }
            if (input.getKeyInputState(GLFW_KEY_A)) {
                _camera.processKeyboard(CameraMovement::LEFT, delta_t);
            }
            if (input.getKeyInputState(GLFW_KEY_D)) {
                _camera.processKeyboard(CameraMovement::RIGHT, delta_t);
            }
            if (input.getKeyInputState(GLFW_KEY_E)) {
                _camera.processKeyboard(CameraMovement::UP, delta_t);
            }
            if (input.getKeyInputState(GLFW_KEY_Q)) {
                _camera.processKeyboard(CameraMovement::DOWN, delta_t);
            }

            if (_first_mouse) {
                _mouse_last_x = input.mouse_pos_x;
                _mouse_last_y = input.mouse_pos_y;
                _first_mouse  = false;
            }
            _camera.processMouseMovement(input.mouse_pos_x - _mouse_last_x,
                                         _mouse_last_y - input.mouse_pos_y);
            _mouse_last_x = input.mouse_pos_x;
            _mouse_last_y = input.mouse_pos_y;

            if (input.was_mouse_scrolling) {
                _camera.processMouseScroll(input.mouse_scroll_offset_y);
            }
        }
    }

    void updateUBO() {
        _matrices.view            = _camera.getViewMatrix();
        _matrices.projection      = _camera.getProjectionMatrix();
        _matrices.view_projection = _matrices.projection * _matrices.view;

        _matrices_buffer->bind();
        _matrices_buffer->updateBuffer(_matrices);
        _matrices_buffer->unbind();

        _camera_struct.position = glm::inverse(_matrices.view * _model.model) *
                                  glm::vec4(0, 0, 0, 1);
        _camera_buffer->bind();
        _camera_buffer->updateBuffer(_camera_struct);
        _camera_buffer->unbind();

        _splat_struct.splat_normal =
                glm::inverseTranspose(glm::mat3(_matrices.view * _model.model));
        _splat_buffer->bind();
        _splat_buffer->updateBuffer(_splat_struct);
        _splat_buffer->unbind();
    }

public:
    void init(ImGuiLayerContext const *ctx) noexcept {
        _imgui_ctx  = ctx;
        _render_ctx = std::make_unique<RenderLayerContext>();

        _dft_renderer.init(_render_ctx.get());
        _point_splatting_renderer.init(_render_ctx.get());
        _marcher_renderer.init(_render_ctx.get());

        _matrices_buffer = std::make_unique<OGLBuffer<MatricesStruct>>(
                OGLBufferDescription{.type  = OGLBufferType::UNIFORM,
                                     .index = 0},
                _matrices);

        _model_buffer = std::make_unique<OGLBuffer<ModelStruct>>(
                OGLBufferDescription{.type  = OGLBufferType::UNIFORM,
                                     .index = 1},
                _model);
        _model.model =
                glm::translate(_model.model, glm::vec3(-0.5, -0.5, -0.5));
        _model_buffer->bind();
        _model_buffer->updateBuffer(_model);
        _model_buffer->unbind();

        _camera_buffer = std::make_unique<OGLBuffer<CameraStruct>>(
                OGLBufferDescription{.type  = OGLBufferType::UNIFORM,
                                     .index = 2},
                _camera_struct);
        _camera_struct.ray_steps.x = 1.0f / DFT_X_DIM;
        _camera_struct.ray_steps.y = 1.0f / DFT_Y_DIM;
        _camera_struct.ray_steps.z = 1.0f / DFT_Z_DIM;

        _splat_buffer = std::make_unique<OGLBuffer<SplatStruct>>(
                OGLBufferDescription{.type  = OGLBufferType::UNIFORM,
                                     .index = 3},
                _splat_struct);
        _splat_struct.splat_size = 256.0f / 64.0f;
    }

    void update(float delta_t) noexcept {
        processInput(delta_t);
        updateUBO();

        if (_imgui_ctx->is_wireframe) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        if (_imgui_ctx->current_renderer == RendererType::DEFAULT) {
            _dft_renderer.update(delta_t);
        } else if (_imgui_ctx->current_renderer ==
                   RendererType::POINT_SPLATTING) {
            _point_splatting_renderer.update(delta_t);
        } else {
            _marcher_renderer.update(delta_t);
        }
    }

    ~RenderLayer() noexcept override = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_GRAPHICS_RENDER_LAYER_HPP
