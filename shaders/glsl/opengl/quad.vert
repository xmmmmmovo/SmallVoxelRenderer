#version 460

layout (location = 0) in vec2 vertex;

layout (location = 0) out vec2 texCoord;

void main()
{
    //get clipspace position by using the object space vertex position
    gl_Position = vec4(vertex.xy * 2.0 - 1.0, 0.0f, 1.0f);
    //store the object space vertex position as texture coordinates
    texCoord = vertex;
}