#version 450 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoords;
layout (location = 3) in uint aTexture;
layout (location = 4) in vec3 aColor;

layout(location = 0) out vec2 vTexcoords;
layout(location = 1) out vec3 vNormal;
layout(location = 2) flat out uint vTexture;
layout(location = 3) flat out vec3 vColor;

void main() {
	vTexcoords = aTexcoords;
	vNormal = aNormal;
	vTexture = aTexture;
	vColor = aColor;
	gl_Position = vec4(aPosition, 1.0f);
}
