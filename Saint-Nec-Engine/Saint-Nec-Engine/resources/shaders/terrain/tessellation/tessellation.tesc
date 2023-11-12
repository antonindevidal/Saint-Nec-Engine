#version 410 core

layout (vertices = 4) out;

in vec2 uvs[];
out vec2 uvsCoord[];

void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position ;
	uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];

	//https://www.khronos.org/opengl/wiki/tessellation#Quads
	gl_TessLevelOuter[0] = 2; // Left side
	gl_TessLevelOuter[1] = 2; // Bottom side
	gl_TessLevelOuter[2] = 2; // Right side
	gl_TessLevelOuter[3] = 2; // Top side


	gl_TessLevelInner[0] = 4; // Top and Bottom sides
	gl_TessLevelInner[1] = 4; // Right and Left sides
}