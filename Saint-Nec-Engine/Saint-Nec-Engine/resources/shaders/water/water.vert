#version 410 core

struct Wave
{
	float amplitude;
	float wavelenght;
	float speed;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform Wave[10] waves; //Maximum of 10 waves
uniform int nWaves;
uniform float time;

out vec2 uvs;

void main()
{

	float yPos = aPos.y;


	float frequency;
	float phase;
	
	for(int i = 0; i < nWaves; i ++)
	{
		frequency = 2.0/waves[i].wavelenght;
		phase = waves[i].speed * frequency;
		yPos += waves[i].amplitude * sin(frequency * aPos.x + time * phase);
	}
	


	gl_Position = projection * view * model * vec4(aPos.x, yPos, aPos.z,1.0f);
}
