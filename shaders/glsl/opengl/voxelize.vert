#version 460

layout (location = 0) in vec3 position;

layout (std140, binding = 0) uniform Matrices {
    mat4 view;
    mat4 projection;
    mat4 viewProjection;
};

layout (std140, binding = 1) uniform Model {
    mat4 model;
};


void main() {
    //get the clipspace position
    gl_Position = viewProjection * model * vec4(position.xyz, 1);
}