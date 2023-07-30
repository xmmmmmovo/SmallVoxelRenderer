//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_CORE_NONCOPYABLE_HPP
#define VOXEL_RENDERER_CORE_NONCOPYABLE_HPP

namespace voxel {

/**
 * @brief inherit this class in private method
 * @details 这个类适用于接口定义，仅能用私有继承(private inheritance)
 * 继承自此类便会自动取消构造函数和复制构造函数，用于定义接口
 */
class NonCopyable {
protected:
    NonCopyable()         = default;
    virtual ~NonCopyable() = default;

public:
    NonCopyable(const NonCopyable &)            = delete;
    NonCopyable &operator=(const NonCopyable &) = delete;

    NonCopyable(NonCopyable &&other) noexcept            = default;
    NonCopyable &operator=(NonCopyable &&other) noexcept = default;
};

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_NONCOPYABLE_HPP
