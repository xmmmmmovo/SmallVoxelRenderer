#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

layout (location = 0) out vec3 outNormal;

layout (std140, binding = 0) uniform Matrices {
    mat4 view;
    mat4 projection;
    mat4 viewProjection;
};

layout (std140, binding = 1) uniform Model {
    mat4 model;
};

layout (std140, binding = 3) uniform Splat {
    mat4 splat_normal;
    float splat_size;
};

void main() {
    //get eye space vertex position
    vec4 eyeSpaceVertex = view * model * vec4(aPos, 1);

    //get the splat size by using the eye space vertex z component
    gl_PointSize = 2 * splat_size / -eyeSpaceVertex.z;

    //get the clipspace position
    gl_Position = projection * eyeSpaceVertex;

    //get the eye space normal
    outNormal = mat3(splat_normal) * aNormal;
}