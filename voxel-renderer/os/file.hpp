//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_OS_FILE_HPP
#define VOXEL_RENDERER_OS_FILE_HPP

#include <filesystem>

#include "core/defines.hpp"

namespace voxel {

VOXEL_INLINE std::filesystem::path
             getRelativePath(const std::filesystem::path &directory,
                             const std::filesystem::path &file_path) {
    return file_path.lexically_relative(directory);
}

VOXEL_INLINE std::vector<std::string>
             getFileExtensions(const std::filesystem::path &file_path) {
    std::vector<std::string> res(1);
    for (auto p = file_path; !p.extension().empty(); p = p.stem()) {
        res.push_back(p.extension().generic_string());
    }
    return res;
}

VOXEL_INLINE std::string
             getLastExtension(const std::filesystem::path &file_path) {
    return file_path.extension().generic_string();
}

VOXEL_INLINE std::string getFilePureName(const std::string &file_full_name) {
    std::string file_pure_name = file_full_name;
    auto        pos            = file_full_name.find_first_of('.');
    if (pos != std::string::npos) {
        file_pure_name = file_full_name.substr(0, pos);
    }

    return file_pure_name;
}

VOXEL_INLINE std::filesystem::path
             fromRelativePath(const std::filesystem::path &directory,
                              const std::filesystem::path &file_path) {
    return directory / file_path;
}

VOXEL_INLINE std::filesystem::path
             fromRelativePath(const std::filesystem::path &relative_path) {
    return std::filesystem::current_path() / relative_path;
}

VOXEL_INLINE std::filesystem::path getRootPath() {
    // 根据不同os获取磁盘根目录
    return std::filesystem::current_path().root_path();
}

VOXEL_INLINE std::filesystem::path
             getDirectoryPath(const std::filesystem::path &file_path) {
    return file_path.parent_path();
}


}// namespace voxel

#endif//VOXEL_RENDERER_OS_FILE_HPP
