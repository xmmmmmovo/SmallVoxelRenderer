//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_READER_DATA_HPP
#define VOXEL_RENDERER_READER_DATA_HPP

namespace voxel {

struct Image {
    std::uint8_t *data{nullptr};
    int           width{0};
    int           height{0};
    int           depth{0};
    int           channels{0};
    int           idx{0};
    ~Image() noexcept { free(data); }
};


}// namespace voxel

#endif//VOXEL_RENDERER_READER_DATA_HPP
