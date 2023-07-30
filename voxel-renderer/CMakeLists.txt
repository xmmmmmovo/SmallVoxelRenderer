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

target_include_directories(${TARGET_NAME} PUBLIC ${VOXEL_RENDERER_ROOT_DIR}/voxel-renderer)
target_include_directories(
        ${TARGET_NAME}
        PUBLIC $<BUILD_INTERFACE:${VOXEL_RENDERER_ROOT_DIR}/shaders/generated/cpp>)

target_precompile_headers(${TARGET_NAME} PRIVATE ${VOXEL_RENDERER_ROOT_DIR}/precompile/pch.hpp)

add_dependencies(${TARGET_NAME} "${SHADER_COMPILE_TARGET}_VK")
add_dependencies(${TARGET_NAME} "${SHADER_COMPILE_TARGET}_GL")

find_package(Vulkan REQUIRED)
find_package(Threads REQUIRED)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindGLFW3.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindGLM.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindStb.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindSpdlog.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindVMA.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindVolk.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindOpenGL.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindMagicEnum.cmake)
include(${VOXEL_RENDERER_ROOT_DIR}/3rdparty/FindImgui.cmake)

target_link_libraries(${TARGET_NAME} PRIVATE GPUOpen::VulkanMemoryAllocator volk_headers Vulkan::Vulkan)
target_link_libraries(${TARGET_NAME} PRIVATE Threads::Threads magic_enum::magic_enum spdlog)
target_link_libraries(${TARGET_NAME} PRIVATE glfw stb imgui glm)
target_link_libraries(${TARGET_NAME} PRIVATE ${OGLLIB} glad)
