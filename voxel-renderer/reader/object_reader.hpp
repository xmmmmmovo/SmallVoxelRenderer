//
// Created by xmmmmmovo on 13/08/2023.
//

#ifndef VOXEL_RENDERER_READER_OBJECT_READER_HPP
#define VOXEL_RENDERER_READER_OBJECT_READER_HPP

#include <filesystem>

#include <assimp/BaseImporter.h>
#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "core/defines.hpp"
#include "read_data_types.hpp"

namespace voxel {

void processMaterial(aiScene const               *scene,
                     std::filesystem::path const &root_path, Model &model) {
    model.materials.reserve(scene->mNumMaterials);

    for (std::size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial *material = scene->mMaterials[i];
        Material    mat;
        aiColor4D   color;

        // load material ids
        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &color)) {
            mat.ambient = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color)) {
            mat.diffuse = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &color)) {
            mat.specular = glm::vec3(color.r, color.g, color.b);
        }

        if (AI_SUCCESS ==
            aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &mat.shininess)) {
            mat.shininess /= 4.0f;
        }

        model.materials.emplace_back(mat);
    }
}

Mesh processMesh(aiMesh const *mesh) {
    Mesh ret_mesh;

    auto const vertex_cnt = mesh->mNumVertices;
    ret_mesh.vertices.reserve(vertex_cnt);
    for (std::size_t i = 0; i < vertex_cnt; ++i) {
        ret_mesh.vertices.emplace_back(mesh->mVertices[i].x,
                                       mesh->mVertices[i].y,
                                       mesh->mVertices[i].z);

        if (mesh->HasNormals()) {
            ret_mesh.normals.emplace_back(mesh->mNormals[i].x,
                                          mesh->mNormals[i].y,
                                          mesh->mNormals[i].z);
        }
    }


    unsigned int faces = 0;
    ret_mesh.indices.reserve(mesh->mNumFaces);
    for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
        auto face = mesh->mFaces[i];
        faces += face.mNumIndices;
        ret_mesh.indices.reserve(faces);
        for (unsigned int j = 0; j < face.mNumIndices; ++j) {
            ret_mesh.indices.emplace_back(face.mIndices[j]);
        }
    }

    ret_mesh.material_idx = mesh->mMaterialIndex;

    return ret_mesh;
}

void processNode(aiNode *node, aiScene const *scene, Model &model) {
    model.meshes.reserve(node->mNumMeshes);
    for (std::size_t i = 0; i < node->mNumMeshes; ++i) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        model.meshes.push_back(processMesh(mesh));
    }

    for (std::size_t i = 0; i < node->mNumChildren; ++i) {
        processNode(node->mChildren[i], scene, model);
    }
}

VOXEL_INLINE std::optional<Model>
             loadObjFile(std::filesystem::path const &path) {
    Model                       model{};
    std::filesystem::path const dir_path = getDirectoryPath(path);

    Assimp::Importer importer;
    aiScene const   *scene = importer.ReadFile(
            path.generic_string(),
            // optimize indexing
            aiProcess_JoinIdenticalVertices | aiProcess_Triangulate |
                    // normal
                    aiProcess_GenSmoothNormals |
                    // opengl uv different
                    aiProcess_FlipUVs |
                    // tangent
                    aiProcess_CalcTangentSpace);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE ||
        !scene->mRootNode) {
        spdlog::error("Assimp error: {}", importer.GetErrorString());
        return std::nullopt;
    }

    processMaterial(scene, dir_path, model);
    processNode(scene->mRootNode, scene, model);

    return model;
}

}// namespace voxel

#endif//VOXEL_RENDERER_READER_OBJECT_READER_HPP
