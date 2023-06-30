set(TARGET_NAME SmallVoxelRenderer)

add_executable(
    ${TARGET_NAME}
    main.cpp
)

set_target_properties(${TARGET_NAME} PROPERTIES CXX_STANDARD 20 OUTPUT_NAME ${TARGET_NAME})

target_precompile_headers(${TARGET_NAME} PRIVATE ${VOXEL_RENDERER_ROOT_DIR}/precompile/pch.hpp)