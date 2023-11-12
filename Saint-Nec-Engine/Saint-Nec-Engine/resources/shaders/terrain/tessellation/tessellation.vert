#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D heightmap;

out vec2 uvs;

void main()
{
	uvs = aTexCoord;
	gl_Position = vec4(aPos,1.0f);
}
