//
// Created by xmmmmmovo on 2023/7/2.
//

#ifndef VOXEL_RENDERER_CORE_HASH_HPP
#define VOXEL_RENDERER_CORE_HASH_HPP

#include <cstddef>
#include <cstdint>
#include <functional>

namespace voxel {
/**
 * @brief hash_combine 通用Hash函数
 * @tparam T
 * @param seed
 * @param v
 */
template<typename T>
inline void hash_combine(std::size_t &seed, const T &v) {
    seed ^= std::hash<T>{}(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

/**
 * @brief hash_combine 通用Hash函数
 * @tparam T
 * @param seed
 * @param v
 */
template<typename T, typename... Ts>
inline void hash_combine(std::size_t &seed, const T &v, Ts... rest) {
    hash_combine(seed, v);
    if constexpr (sizeof...(Ts) > 1) { hash_combine(seed, rest...); }
}

using hash32_t = std::uint32_t;
using hash64_t = std::uint64_t;

// From: https://gist.github.com/Lee-R/3839813
inline constexpr hash32_t fnv1a_32(char const *s, std::size_t count) {
    return ((count ? fnv1a_32(s, count - 1)
                   : 2166136261u)// NOLINT (hicpp-signed-bitwise)
            ^ s[count]) *
           16777619u;            // NOLINT (hicpp-signed-bitwise)
}

inline constexpr hash64_t fnv1a_64(char const *s, std::size_t count) {
    return ((count ? fnv1a_64(s, count - 1)
                   : 14695981039346656037ULL)// NOLINT (hicpp-signed-bitwise)
            ^ s[count]) *
           // 64 bit FNV_prime = 240 + 28 + 0xb3 = 1099511628211
           1099511628211ULL;// NOLINT (hicpp-signed-bitwise)
}

constexpr hash32_t operator"" _hash32(char const *s, std::size_t count) {
    return fnv1a_32(s, count);
}

constexpr hash64_t operator"" _hash64(char const *s, std::size_t count) {
    return fnv1a_64(s, count);
}

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_HASH_HPP
