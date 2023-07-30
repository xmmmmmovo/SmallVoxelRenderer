#version 460

layout(location = 0) in vec3 aPos;

layout(location = 0) uniform mat4 model;

layout(std140, binding = 0) uniform Matrices {
	mat4 view;
	mat4 projection;
	mat4 viewProjection;
};

void main() {
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}