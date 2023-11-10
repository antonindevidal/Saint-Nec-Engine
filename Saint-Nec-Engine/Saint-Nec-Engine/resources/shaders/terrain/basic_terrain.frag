#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D heightmap;

void main()
{
	vec4 textColor = texture(heightmap, TexCoord);
	FragColor = vec4(textColor.x, textColor.x, textColor.x, 1.0f);
}
