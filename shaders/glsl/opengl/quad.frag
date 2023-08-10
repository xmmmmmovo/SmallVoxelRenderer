#version 460

layout(location = 0) in vec2 TexCoords;

layout(location = 0) out vec4 FragColor;

layout(location = 0) uniform sampler2D screenTexture;

void main()
{
    vec3 col = texture(screenTexture, TexCoords).rgb;
    FragColor = vec4(col, 1.0);
}