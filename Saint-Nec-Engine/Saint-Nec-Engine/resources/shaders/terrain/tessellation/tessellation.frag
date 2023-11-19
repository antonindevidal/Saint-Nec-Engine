#version 410 core

out vec4 FragColor;

in vec2 uvs;

uniform sampler2D heightmap;
uniform sampler2D heightmapNormal;
uniform sampler2D rockTex;
uniform sampler2D grassTex;


uniform float textureScaling;
uniform vec3 lightDir;

void main()
{
	vec4 heighmapColor = texture(heightmap, uvs);
	vec4 grassColor = texture(grassTex, uvs * textureScaling);
	vec4 rockColor = texture(rockTex, uvs * textureScaling);
	vec4 norm = texture(heightmapNormal, uvs);
	vec3 normal = vec3(norm.x,norm.y,norm.z);

	float diffuse = max(dot(normal, lightDir), 0.0f);
	vec4 objectColor = mix(rockColor,grassColor, heighmapColor.x);
	
	vec3 result = (diffuse +0.2)* vec3(objectColor.x,objectColor.y,objectColor.z);
	
	FragColor =  vec4(result, 1.0f);
	//FragColor = vec4(heighmapColor.x, heighmapColor.x, heighmapColor.x, 1.0f);
}
