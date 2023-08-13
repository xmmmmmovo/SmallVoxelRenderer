#version 460

layout (location = 0) in vec3 vVertex;    //object space vertex position
layout (location = 1) in vec3 vNormal;    //object space vertex normal

layout (std140, binding = 0) uniform Matrices {
    mat4 view;
    mat4 projection;
    mat4 viewProjection;
};

layout (std140, binding = 1) uniform Model {
    mat4 model;
};

//output object space normal
layout (location = 0) out vec3 outNormal;

void main()
{
    //get the clipspace position
    gl_Position = viewProjection * model * vec4(vVertex.xyz, 1);
    //output object space normal
    outNormal = vNormal;
}