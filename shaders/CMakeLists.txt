set(TARGET_NAME ${SHADER_COMPILE_TARGET})

file(GLOB_RECURSE VULKAN_SHADER_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.frag"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.comp"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.geom"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.tesc"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.tese"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.mesh"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.task"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.rgen"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.rchit"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.rmiss"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/vulkan/*.rcall"
        )

file(GLOB_RECURSE OPENGL_SHADER_FILES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.vert"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.frag"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.comp"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.geom"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.tesc"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.tese"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.mesh"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.task"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.rgen"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.rchit"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.rmiss"
        "${CMAKE_CURRENT_SOURCE_DIR}/glsl/opengl/*.rcall"
        )

set(SHADER_INCLUDE_FOLDER ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GENERATED_SHADER_FOLDER "generated")

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER})
endif ()

if (NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/${GENERATED_SHADER_FOLDER}/spv)
endif ()

set(glslangValidator_executable ${Vulkan_GLSLANG_VALIDATOR_EXECUTABLE})

include(${PROJECT_SOURCE_DIR}/cmake/ShaderCompile.cmake)
compile_shader(
        "${VULKAN_SHADER_FILES}"
        "${TARGET_NAME}_VK"
        "${SHADER_INCLUDE_FOLDER}"
        "${GENERATED_SHADER_FOLDER}"
        "${glslangValidator_executable}"
        "vk"
        "-V100"
)

compile_shader(
        "${OPENGL_SHADER_FILES}"
        "${TARGET_NAME}_GL"
        "${SHADER_INCLUDE_FOLDER}"
        "${GENERATED_SHADER_FOLDER}"
        "${glslangValidator_executable}"
        "gl"
        "-G"
)

set_target_properties("${TARGET_NAME}_VK" PROPERTIES FOLDER "VKRendererShader")
set_target_properties("${TARGET_NAME}_GL" PROPERTIES FOLDER "GLRendererShader")
