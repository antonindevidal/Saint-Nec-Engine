#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uvs;

void main()
{
	mat4 vm = view  * model;
	vm[0][0] = 1;
	vm[0][1] = 0;
	vm[0][2] = 0;
	vm[1][0] = 0;
	vm[1][1] = 1;
	vm[1][2] = 0;
	vm[2][0] = 0;
	vm[2][1] = 0;
	vm[2][2] = 1;

	uvs = aUV;
	gl_Position = projection * vm *  vec4(aPos, 1.0);
}
