cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

project(
    SmallVoxelRenderer
    VERSION 0.1
    DESCRIPTION "Voxel Renderer"
    LANGUAGES CXX C
)

include(cmake/CPM.cmake)

set(VOXEL_RENDERER_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

configure_file(cmake/path.hpp.in ${VOXEL_RENDERER_ROOT_DIR}/voxel-renderer/core/path.hpp @ONLY)

add_subdirectory(voxel-renderer)

set(SHADER_COMPILE_TARGET VoxelShaderCompile)
add_subdirectory(shaders)