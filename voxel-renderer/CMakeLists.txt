set(TARGET_NAME SmallVoxelRenderer)

# accelerate the msvc project
if (MSVC)
    add_compile_options("/MP")
    add_compile_options("/utf-8")
endif ()

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.hpp *.h)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.inc)

add_executable(
        ${TARGET_NAME}
        ${HEADER_FILES}
        ${SOURCE_FILES}
)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME ${TARGET_NAME})

target_include_directories(${TARGET_NAME} PRIVATE ${VOXEL_RENDERER_ROOT_DIR}/voxel-renderer)

target_precompile_headers(${TARGET_NAME} PRIVATE ${VOXEL_RENDERER_ROOT_DIR}/precompile/pch.hpp)

add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET})

find_package(Vulkan REQUIRED)
find_package(Threads REQUIRED)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindGLFW3.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindGLM.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindStb.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindImgui.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindSpdlog.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindVMA.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindVolk.cmake)

target_link_libraries(${TARGET_NAME} PRIVATE GPUOpen::VulkanMemoryAllocator volk_headers)
target_link_libraries(${TARGET_NAME} PUBLIC Threads::Threads)
target_link_libraries(${TARGET_NAME} PUBLIC glfw stb glm Vulkan::Vulkan)
target_link_libraries(${TARGET_NAME} PUBLIC imgui spdlog)
