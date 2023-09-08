//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_READER_RAW_READER_HPP
#define VOXEL_RENDERER_READER_RAW_READER_HPP

#include "core/defines.hpp"
#include "os/file_service.hpp"
#include "read_data_types.hpp"

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <filesystem>

namespace voxel {

//dimensions of volume data
static constexpr std::uint32_t DFT_X_DIM = 256;
static constexpr std::uint32_t DFT_Y_DIM = 256;
static constexpr std::uint32_t DFT_Z_DIM = 256;

VOXEL_INLINE Image loadRaw(std::filesystem::path const &path) {
    std::ifstream file = openFile(path, std::ios::in | std::ios::binary);
    Image         image;

    std::int64_t const vol_size =
            static_cast<std::size_t>(DFT_X_DIM * DFT_Y_DIM * DFT_Z_DIM) * sizeof(std::uint8_t);

    image.data   = static_cast<std::uint8_t *>(malloc(vol_size));
    image.width  = DFT_X_DIM;
    image.height = DFT_Y_DIM;
    image.depth  = DFT_Z_DIM;

    file.read(reinterpret_cast<char *>(image.data), vol_size);
    return image;
}

}// namespace voxel

#endif//VOXEL_RENDERER_READER_RAW_READER_HPP
