//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_CORE_PUBLIC_SINGLETON_HPP
#define VOXEL_RENDERER_CORE_PUBLIC_SINGLETON_HPP

#include <type_traits>

namespace voxel {

/**
 * @brief public extend singleton class
 * @tparam T Type for singleton instance
 */
template<typename T>
class PublicSingleton {
protected:
    PublicSingleton()           = default;
    ~PublicSingleton() noexcept = default;

public:
    /**
     * @brief get instance, thread safe.
     * @return static instance ref.
     */
    static inline T &
    getInstance() noexcept(std::is_nothrow_constructible<T>::value) {
        static T instance;
        return instance;
    }

    PublicSingleton(const PublicSingleton &)            = delete;
    PublicSingleton &operator=(const PublicSingleton &) = delete;
};


}// namespace voxel

#endif//VOXEL_RENDERER_CORE_PUBLIC_SINGLETON_HPP
