//
// Created by xmmmmmovo on 29/07/2023.
//

#ifndef VOXEL_RENDERER_CORE_META_IS_VECTOR_HPP
#define VOXEL_RENDERER_CORE_META_IS_VECTOR_HPP

#include <type_traits>

namespace voxel {

template<typename Test, template<typename...> class Ref>
struct IsSpecialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct IsSpecialization<Ref<Args...>, Ref> : std::true_type {};

template<class T>
struct IsArray : std::is_array<T> {};
template<class T, std::size_t N>
struct IsArray<std::array<T, N>> : std::true_type {};

}// namespace voxel

#endif//VOXEL_RENDERER_CORE_META_IS_VECTOR_HPP
