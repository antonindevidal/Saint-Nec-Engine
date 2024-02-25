#version 410 core

uniform vec3 sunDir;
uniform vec3 color;

in vec2 uvs;

out vec4 FragColor;


void main()
{
	vec2 centeredUV = uvs -0.5;
	float distanceFromCenter = sqrt(centeredUV.x * centeredUV.x  + centeredUV.y * centeredUV.y);

	float insideCircle = 1.0 - step(0.5, distanceFromCenter);
	FragColor = insideCircle * vec4(color, 1.0) + (1-insideCircle) *vec4(0.0,0.0,0.0, 0.0) ;
}
