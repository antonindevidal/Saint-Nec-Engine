#version 410 core

uniform vec3 sunDir;
uniform vec3 waterColor;
uniform vec3 cameraDir;
uniform int specularExp;
uniform float ambient;

in vec3 normal;

out vec4 FragColor;


void main()
{

	float diffuse = max(dot(normal, sunDir), 0.0f);

	//Blinn phong (specular reflection)
	vec3 halfwayVector = normalize(sunDir - cameraDir);
	float specular = pow(max(dot(halfwayVector,normal),0.0f),specularExp) *3;

	//FragColor= vec4(specular,specular,specular,1.0f);
	FragColor = vec4(waterColor *(specular+ ambient + diffuse),1.0f);
}
