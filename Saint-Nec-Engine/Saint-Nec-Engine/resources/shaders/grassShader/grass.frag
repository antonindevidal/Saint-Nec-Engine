#version 410 core

uniform vec3 grassColorTop;
uniform vec3 grassColorBottom;

in vec2 uv;
in vec3 norm;
in vec3 lightDir;
in vec3 cameraFront;

out vec4 FragColor;

void main()
{
	vec3 color = mix(grassColorBottom, grassColorTop, uv.y);
	float faceRendered = dot(cameraFront,norm);
	float diffuse = max(dot(norm*sign(faceRendered)*-1.0, lightDir), 0.0f);

	FragColor = vec4(color * (0.8 + diffuse) , 1.0);
}
