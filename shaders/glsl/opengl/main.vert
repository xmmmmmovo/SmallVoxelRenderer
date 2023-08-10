#version 460

layout(location = 0) in vec3 aPos;

layout(std140, binding = 0) uniform Matrices {
	mat4 view;
	mat4 projection;
	mat4 viewProjection;
};

layout(std140, binding = 1) uniform Model {
	mat4 model;
};

void main() {
    gl_Position = viewProjection * model * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
}