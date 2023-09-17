#version 460 core

layout (location = 0) in vec3 vVertex; //object space vertex position

layout (std140, binding = 0) uniform Matrices {
    mat4 view;
    mat4 projection;
    mat4 viewProjection;
};

layout (std140, binding = 1) uniform Model {
    mat4 model;
};

layout (location = 0) smooth out vec3 vUV; //3D texture coordinates for texture lookup in the fragment shader

void main()
{
    //get the clipspace position
    gl_Position = viewProjection * model * vec4(vVertex.xyz, 1);

    //get the 3D texture coordinates by adding (0.5,0.5,0.5) to the object space
    //vertex position. Since the unit cube is at origin (min: (-0.5,-0.5,-0.5) and max: (0.5,0.5,0.5))
    //adding (0.5,0.5,0.5) to the unit cube object space position gives us values from (0,0,0) to
    //(1,1,1)
    vUV = vVertex + vec3(0.5f);
}