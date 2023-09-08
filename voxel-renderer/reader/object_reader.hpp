//
// Created by xmmmmmovo on 13/08/2023.
//

#ifndef VOXEL_RENDERER_READER_OBJECT_READER_HPP
#define VOXEL_RENDERER_READER_OBJECT_READER_HPP

#include <tiny_obj_loader.h>

#include <filesystem>

#include "core/defines.hpp"
#include "read_data_types.hpp"

namespace voxel {

VOXEL_INLINE MeshObj loadObjFile(std::filesystem::path const &path) {
    tinyobj::attrib_t                attrib;
    std::vector<tinyobj::shape_t>    shapes;
    std::vector<tinyobj::material_t> materials;

    bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, nullptr, nullptr,
                                path.string().c_str());

    if (!ret) { throw std::runtime_error("load obj file failed"); }

    MeshObj mesh_obj{};
}

}// namespace voxel

#endif//VOXEL_RENDERER_READER_OBJECT_READER_HPP
