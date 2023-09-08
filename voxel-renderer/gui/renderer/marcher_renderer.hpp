//
// Created by xmmmmmovo on 13/08/2023.
//

#ifndef VOXEL_RENDERER_GUI_RENDERER_MARCHER_RENDERER_HPP
#define VOXEL_RENDERER_GUI_RENDERER_MARCHER_RENDERER_HPP

#include "graphics/common/tables.hpp"
#include "i_renderer.hpp"

namespace voxel {

class MarcherRenderer final : public IRenderer {
private:
    RenderLayerContext *_ctx{};

    std::unique_ptr<OGLPipeline>   _marcher_pipeline{nullptr};
    std::unique_ptr<OGLRenderPass> _marcher_render_pass{nullptr};

    std::vector<glm::vec3> _marcher_pos{};
    std::vector<glm::vec3> _marcher_normal{};

    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> _marcher_pos_buffer{
            nullptr};
    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> _marcher_normal_buffer{
            nullptr};
    std::unique_ptr<OGLVertexArray> _marcher_vao{nullptr};

    glm::vec3 _inv_dim{1.0f / DFT_X_DIM, 1.0f / DFT_Y_DIM, 1.0f / DFT_Z_DIM};
    GLubyte   _iso_value{48};
    std::uint32_t _x_sample_dist{128}, _y_sample_dist{128}, _z_sample_dist{128};

private:
    std::uint8_t SampleVolume(const int x, const int y, const int z) {
        int index = (x + (y * DFT_X_DIM)) + z * (DFT_X_DIM * DFT_Y_DIM);
        if (index < 0) index = 0;
        if (index >= DFT_X_DIM * DFT_Y_DIM * DFT_Z_DIM)
            index = (DFT_X_DIM * DFT_Y_DIM * DFT_Z_DIM) - 1;
        return _ctx->_volume_image.value().data[index];
    }

    glm::vec3 GetNormal(const int x, const int y, const int z) {
        glm::vec3 N;
        N.x = (SampleVolume(x - 1, y, z) - SampleVolume(x + 1, y, z)) * 0.5f;
        N.y = (SampleVolume(x, y - 1, z) - SampleVolume(x, y + 1, z)) * 0.5f;
        N.z = (SampleVolume(x, y, z - 1) - SampleVolume(x, y, z + 1)) * 0.5f;
        return glm::normalize(N);
    }

    float GetOffset(const GLubyte v1, const GLubyte v2) {
        float delta = (float) (v2 - v1);
        if (delta == 0) return 0.5f;
        else
            return (_iso_value - v1) / delta;
    }

    void sampleVoxel(std::int32_t const x, std::int32_t const y,
                     std::int32_t const z, glm::vec3 const &scale) {
        GLubyte   cubeCornerValues[8];
        int       flagIndex, edgeFlags, i;
        glm::vec3 edgeVertices[12];
        glm::vec3 edgeNormals[12];

        //Make a local copy of the values at the cube's corners
        for (i = 0; i < 8; i++) {
            cubeCornerValues[i] =
                    SampleVolume(x + (int) (a2fVertexOffset[i][0] * scale.x),
                                 y + (int) (a2fVertexOffset[i][1] * scale.y),
                                 z + (int) (a2fVertexOffset[i][2] * scale.z));
        }

        //Find which vertices are inside of the surface and which are outside
        //Obtain a flagIndex based on if the value at the cube vertex is less
        //than the given isovalue
        flagIndex = 0;
        for (i = 0; i < 8; i++) {
            if (cubeCornerValues[i] <= _iso_value) flagIndex |= 1 << i;
        }

        //Find which edges are intersected by the surface
        edgeFlags = aiCubeEdgeFlags[flagIndex];

        //If the cube is entirely inside or outside of the surface, then there will be no intersections
        if (edgeFlags == 0) { return; }

        //for all edges
        for (i = 0; i < 12; i++) {
            //if there is an intersection on this edge
            if (edgeFlags & (1 << i)) {
                //get the offset
                float offset =
                        GetOffset(cubeCornerValues[a2iEdgeConnection[i][0]],
                                  cubeCornerValues[a2iEdgeConnection[i][1]]);

                //use offset to get the vertex position
                edgeVertices[i].x =
                        x + (a2fVertexOffset[a2iEdgeConnection[i][0]][0] +
                             offset * a2fEdgeDirection[i][0]) *
                                    scale.x;
                edgeVertices[i].y =
                        y + (a2fVertexOffset[a2iEdgeConnection[i][0]][1] +
                             offset * a2fEdgeDirection[i][1]) *
                                    scale.y;
                edgeVertices[i].z =
                        z + (a2fVertexOffset[a2iEdgeConnection[i][0]][2] +
                             offset * a2fEdgeDirection[i][2]) *
                                    scale.z;

                //use the vertex position to get the normal
                edgeNormals[i] = GetNormal((int) edgeVertices[i].x,
                                           (int) edgeVertices[i].y,
                                           (int) edgeVertices[i].z);
            }
        }

        //Draw the triangles that were found.  There can be up to five per cube
        for (i = 0; i < 5; i++) {
            if (a2iTriangleConnectionTable[flagIndex][3 * i] < 0) break;

            for (int j = 0; j < 3; j++) {
                int vertex = a2iTriangleConnectionTable[flagIndex][3 * i + j];
                _marcher_pos.emplace_back(edgeVertices[vertex] * _inv_dim);
                _marcher_normal.emplace_back(edgeNormals[vertex]);
            }
        }
    }

    void marchVolume() {
        std::uint32_t const dx    = DFT_X_DIM / _x_sample_dist;
        std::uint32_t const dy    = DFT_Y_DIM / _y_sample_dist;
        std::uint32_t const dz    = DFT_Z_DIM / _z_sample_dist;
        glm::vec3           scale = glm::vec3(dx, dy, dz);

        for (std::uint32_t z = 0; z < DFT_X_DIM; z += dz) {
            for (std::uint32_t y = 0; y < DFT_Y_DIM; y += dy) {
                for (std::uint32_t x = 0; x < DFT_Z_DIM; x += dx) {
                    sampleVoxel(x, y, z, scale);
                }
            }
        }
    }

public:
    void init(RenderLayerContext *ctx) noexcept override {
        _ctx = ctx;
        OGLShaderProgram splat_shader_program;
        splat_shader_program.attach(_ctx->marcher_vert_shader);
        splat_shader_program.attach(_ctx->marcher_frag_shader);
        splat_shader_program.link();
        OGLPipelineDescription marcher_pipeline_description{
                ._shader_program = std::move(splat_shader_program),
        };

        _marcher_pipeline = std::make_unique<OGLPipeline>(
                std::move(marcher_pipeline_description));
        _marcher_render_pass =
                std::make_unique<OGLRenderPass>(OGLRenderPassDescription{});

        marchVolume();

        _marcher_vao = std::make_unique<OGLVertexArray>();
        _marcher_pos_buffer =
                std::make_unique<OGLBuffer<std::vector<glm::vec3>>>(
                        OGLBufferDescription{OGLBufferType::VERTEX},
                        _marcher_pos);
        _marcher_normal_buffer =
                std::make_unique<OGLBuffer<std::vector<glm::vec3>>>(
                        OGLBufferDescription{OGLBufferType::VERTEX},
                        _marcher_normal);
        _marcher_vao->bind();
        _marcher_vao->bindBuffer(*_marcher_pos_buffer);
        _marcher_vao->bindBuffer(*_marcher_normal_buffer);
        _marcher_vao->unbind();
    }

    void update(float delta_t) noexcept override {
        _marcher_render_pass->use();
        _marcher_pipeline->use();
        // splat pass
        _marcher_vao->bind();
        _marcher_vao->draw();
    }
};


}// namespace voxel

#endif//VOXEL_RENDERER_GUI_RENDERER_MARCHER_RENDERER_HPP
