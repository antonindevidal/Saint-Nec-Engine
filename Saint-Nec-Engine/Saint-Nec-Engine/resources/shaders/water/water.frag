#version 410 core

uniform vec3 sunDir;
uniform vec3 waterColor;
uniform vec3 cameraDir;
uniform int specularExp;
uniform float ambient;
uniform bool useSpecular;

in vec3 normal;


out vec4 FragColor;


void main()
{

	float diffuse = max(dot(normalize(normal), -sunDir), 0.0f);

	//Blinn phong (specular reflection)
	
	float specular = 0.0f;
	//FragColor= vec4(0.0f,abs(normal.y),0.0f,1.0f);
	if(useSpecular)
	{
		vec3 halfwayVector = normalize(-normalize(sunDir)- normalize(cameraDir ));
		specular = pow(max(dot(normal,halfwayVector),0.0f),specularExp);
	}
	FragColor = vec4(waterColor *( ambient+ specular  + diffuse),1.0f);
}
