#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

layout(location = 0) in vec3 vNormal[];
layout(location = 1) in vec2 vTexcoords[];
layout(location = 2) flat in uint vTexture[];
layout(location = 3) flat in vec3 vColor[];

layout(location = 0) out vec2 gTexcoords;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec3 gVoxelPos;
layout(location = 3) flat out uint gTexture;
layout(location = 4) flat out vec3 gColor;

uniform int uVoxelResolution;

vec2 Project(in vec3 v, in int axis) { return axis == 0 ? v.yz : (axis == 1 ? v.xz : v.xy); }

void main() {
	//get projection axis
	vec3 axis_weight = abs(cross(gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz, gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz));
	int axis = 2;
	if(axis_weight.x >= axis_weight.y && axis_weight.x > axis_weight.z) axis = 0;
	else if(axis_weight.y >= axis_weight.z && axis_weight.y > axis_weight.x) axis = 1;

	//project the positions
	vec3 pos0 = gl_in[0].gl_Position.xyz;
	vec3 pos1 = gl_in[1].gl_Position.xyz;
	vec3 pos2 = gl_in[2].gl_Position.xyz;

	gTexture = vTexture[0];
	gColor = vColor[0];

	gTexcoords = vTexcoords[0];
	gNormal = normalize(vNormal[0]);
	gVoxelPos = (pos0 + 1.0f) * 0.5f * uVoxelResolution;
	gl_Position = vec4(Project(pos0, axis), 1.0f, 1.0f);
	EmitVertex();
	gTexcoords = vTexcoords[1];
	gNormal = normalize(vNormal[1]);
	gVoxelPos = (pos1 + 1.0f) * 0.5f * uVoxelResolution;
	gl_Position = vec4(Project(pos1, axis), 1.0f, 1.0f);
	EmitVertex();
	gTexcoords = vTexcoords[2];
	gNormal = normalize(vNormal[2]);
	gVoxelPos = (pos2 + 1.0f) * 0.5f * uVoxelResolution;
	gl_Position = vec4(Project(pos2, axis), 1.0f, 1.0f);
	EmitVertex();
	EndPrimitive();
}
