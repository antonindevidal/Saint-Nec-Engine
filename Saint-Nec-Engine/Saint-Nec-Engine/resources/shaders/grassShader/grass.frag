#version 410 core

uniform vec3 grassColorTop;
uniform vec3 grassColorBottom;

in vec2 uv;

out vec4 FragColor;

void main()
{
	vec3 color = mix(grassColorBottom, grassColorTop, uv.y);
	FragColor = vec4(color, 1.0);
}
