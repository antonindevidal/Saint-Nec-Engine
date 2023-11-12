#version 410 core
 
layout (quads, equal_spacing, ccw) in;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

in vec2 uvsCoord[];
out vec2 uvs;

void main()
{

	float u = gl_TessCoord.x;
	float v = gl_TessCoord.y;

	vec2 uv0 = uvsCoord[0];
	vec2 uv1 = uvsCoord[1];
	vec2 uv2 = uvsCoord[2];
	vec2 uv3 = uvsCoord[3];

	//Bilinear interpolation

	vec2 leftUV = uv0 + v * (uv3 -uv0);
	vec2 rightUV = uv1 + v * (uv2 -uv1);
	vec2 texCoord = leftUV + u*(rightUV - leftUV);

	vec4 pos0 = gl_in[0].gl_Position;
	vec4 pos1 = gl_in[1].gl_Position;
	vec4 pos2 = gl_in[2].gl_Position;
	vec4 pos3 = gl_in[3].gl_Position;

	vec4 leftPos = pos0 + v*(pos3 - pos0);
	vec4 rightPos = pos1 + v* (pos2 - pos1);
	vec4 pos = leftPos + u* (rightPos - leftPos);

	gl_Position = projection * view * model * pos;
	uvs = texCoord;
}