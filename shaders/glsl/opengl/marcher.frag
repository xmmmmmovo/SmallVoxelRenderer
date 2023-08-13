#version 460

layout (location = 0) in vec3 outNormal;

layout (location = 0) out vec4 vFragColor; // fragment shader output

void main() {
    // output the object space normal as colour
    vFragColor = vec4(outNormal, 1);
}