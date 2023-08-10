//
// Created by xmmmmmovo on 03/08/2023.
//

#ifndef VOXEL_RENDERER_CORE_RAII_POINTER_HPP
#define VOXEL_RENDERER_CORE_RAII_POINTER_HPP

namespace voxel {

struct FreeDeleter {
    template<typename T>
    void operator()(T *ptr) const noexcept {
        if (ptr) { free(ptr); }
    }
};

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_RAII_POINTER_HPP
