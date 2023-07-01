set(TARGET_NAME SmallVoxelRenderer)

file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.hpp *.h)
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp *.inc)

add_executable(
    ${TARGET_NAME}
    ${HEADER_FILES}
    ${SOURCE_FILES}
)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME ${TARGET_NAME})

target_precompile_headers(${TARGET_NAME} PRIVATE ${VOXEL_RENDERER_ROOT_DIR}/precompile/pch.hpp)

# add_dependencies(${TARGET_NAME} ${SHADER_COMPILE_TARGET})