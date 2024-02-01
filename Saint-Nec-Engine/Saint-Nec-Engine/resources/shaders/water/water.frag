#version 410 core

uniform vec3 sunDir;
uniform vec3 waterColor;
in vec3 normal;

out vec4 FragColor;


void main()
{
	float diffuse = max(dot(normal, sunDir), 0.0f) + 0.8;

	FragColor = vec4(normal, 1.0f);
}
