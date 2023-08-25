//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_READER_DATA_HPP
#define VOXEL_RENDERER_READER_DATA_HPP

namespace voxel {

class Image final {
public:
    std::uint8_t *data{nullptr};
    int           width{0};
    int           height{0};
    int           depth{0};
    int           channels{0};
    int           idx{0};

public:
    Image() noexcept = default;

    // copy
    Image(Image const &other) noexcept
        : width(other.width), height(other.height), depth(other.depth),
          channels(other.channels), idx(other.idx) {
        if (data != nullptr) {
            data = static_cast<std::uint8_t *>(
                    malloc(width * height * depth * channels));
            memcpy(data, other.data, width * height * depth * channels);
        }
    }
    // operator=
    Image &operator=(Image const &other) noexcept {
        if (this == &other) { return *this; }

        width    = other.width;
        height   = other.height;
        depth    = other.depth;
        channels = other.channels;
        idx      = other.idx;

        if (data != nullptr) {
            data = static_cast<std::uint8_t *>(
                    malloc(width * height * depth * channels));
            memcpy(data, other.data, width * height * depth * channels);
        }

        return *this;
    }

    // move
    Image(Image &&other) noexcept
        : data(other.data), width(other.width), height(other.height),
          depth(other.depth), channels(other.channels), idx(other.idx) {
        other.data = nullptr;
    }

    // operator=
    Image &operator=(Image &&other) noexcept {
        if (this == &other) { return *this; }

        data     = other.data;
        width    = other.width;
        height   = other.height;
        depth    = other.depth;
        channels = other.channels;
        idx      = other.idx;

        other.data = nullptr;

        return *this;
    }

    ~Image() noexcept {
        if (data != nullptr) { free(data); }
    }
};

struct Material final {
    glm::vec3 ambient{};
    glm::vec3 diffuse{};
    glm::vec3 specular{};
    float     shininess{};
};

struct MeshObj final {
    std::vector<glm::vec3> vertices{};
    std::vector<glm::vec3> normals{};

    std::size_t material_idx{0};
};

struct MeshGPU final {
    OGLVertexArray                                     vao{};
    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> pos_buffer{nullptr};
    std::unique_ptr<OGLBuffer<std::vector<glm::vec3>>> normal_buffer{nullptr};
    std::size_t                                        vertex_count{0};
    std::size_t                                        material_idx{0};
};

struct Model final {
    std::vector<MeshObj>  meshes{};
    std::vector<Material> materials{};
};

struct ModelGPU final {
    std::vector<MeshGPU>  meshes{};
    std::vector<Material> materials{};
    glm::vec3             aabbMin, aabbMax;
};

}// namespace voxel

#endif//VOXEL_RENDERER_READER_DATA_HPP
