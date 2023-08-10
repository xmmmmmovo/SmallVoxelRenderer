//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_READER_IMAGE_READER_HPP
#define VOXEL_RENDERER_READER_IMAGE_READER_HPP

#include <filesystem>
#include <stb_image.h>

#include "core/defines.hpp"
#include "do.hpp"

namespace voxel {

VOXEL_INLINE Image loadImage(std::filesystem::path const &path,
                             int                          desired_channels = 4,
                             bool flip_vertically = true) {
    stbi_set_flip_vertically_on_load(flip_vertically);
    Image image;
    image.data = stbi_load(path.generic_string().c_str(), &image.width,
                           &image.height, &image.channels, desired_channels);
    return image;
}

}// namespace voxel

#endif//VOXEL_RENDERER_READER_IMAGE_READER_HPP
