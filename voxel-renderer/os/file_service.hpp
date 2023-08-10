//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_OS_FILE_SERVICE_HPP
#define VOXEL_RENDERER_OS_FILE_SERVICE_HPP

#include <filesystem>
#include <fstream>

#include "core/defines.hpp"

namespace voxel {

VOXEL_INLINE std::vector<std::filesystem::path>
             getFiles(const std::filesystem::path &directory) {
    std::vector<std::filesystem::path> files;
    auto                               recursive_iter =
            std::filesystem::recursive_directory_iterator{directory};
    // TODO: this may cause mem explosion, Need to be optimized!
    std::copy_if(begin(recursive_iter), end(recursive_iter),
                              std::back_inserter(files),
                              [](std::filesystem::directory_entry const &directory_entry) {
                     return directory_entry.is_regular_file();
                 });
    return files;
}

VOXEL_INLINE bool removeFile(std::filesystem::path const &file_path) {
    return std::filesystem::remove(file_path);
}

VOXEL_INLINE bool removeDirectory(std::filesystem::path const &directory_path) {
    return std::filesystem::remove_all(directory_path);
}

VOXEL_INLINE bool createDirectory(std::filesystem::path const &directory_path) {
    return std::filesystem::create_directories(directory_path);
}

VOXEL_INLINE bool copyFile(std::filesystem::path const &source,
                           std::filesystem::path const &destination) {
    return std::filesystem::copy_file(source, destination);
}

VOXEL_INLINE bool copyDirectory(std::filesystem::path const &source,
                                std::filesystem::path const &destination) {
    std::error_code ec;
    std::filesystem::copy(source, destination, ec);
    return !static_cast<bool>(ec);
}

VOXEL_INLINE bool
moveFileOrDirectory(std::filesystem::path const &source,
                    std::filesystem::path const &destination) {
    std::error_code ec;
    std::filesystem::rename(source, destination, ec);
    return !static_cast<bool>(ec);
}

VOXEL_INLINE std::ifstream
             openFile(std::filesystem::path const &file_path,
                      std::ios_base::openmode      mode = std::ios_base::in) {
    std::ifstream ifstream{file_path, mode};
    if (!ifstream.is_open()) {
        throw std::runtime_error("Failed to open file: {}" +
                                              file_path.string());
    }
    return ifstream;
}

VOXEL_INLINE std::ofstream
             createFile(std::filesystem::path const &file_path,
                        std::ios_base::openmode      mode = std::ios_base::out) {
    std::ofstream ofstream{file_path, mode};
    if (!ofstream.is_open()) {
        throw std::runtime_error("Failed to create file: {}" +
                                              file_path.string());
    }
    return ofstream;
}

}// namespace voxel

#endif//VOXEL_RENDERER_OS_FILE_SERVICE_HPP
