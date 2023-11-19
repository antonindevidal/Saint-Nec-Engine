#version 410 core

out vec4 FragColor;

in vec2 uvs;

uniform sampler2D heightmap;

void main()
{
	vec4 textColor = texture(heightmap, uvs);
	FragColor = vec4(textColor.x, textColor.x, textColor.x, 1.0f);
}
