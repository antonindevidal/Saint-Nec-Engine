#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform sampler2D heightmap;

out vec2 TexCoord;

void main()
{
	vec4 text = texture(heightmap,aTexCoord);
	vec4 pos = vec4(aPos.x,text.x * 4.0f, aPos.z,1.0f);
	TexCoord = aTexCoord;
	gl_Position = projection * view * model* pos;
}
