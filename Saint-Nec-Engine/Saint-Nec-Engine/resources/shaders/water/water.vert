#version 410 core

struct Wave
{
	float amplitude;
	float wavelenght;
	float speed;
	vec2 direction;
};

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform Wave[10] waves; //Maximum of 10 waves
uniform int nWaves;
uniform float time;

out vec3 normal;


float getWaveCoord(Wave w, vec3 pos)
{
	return w.direction.x * pos.x +  w.direction.y * pos.z;
}

void main()
{

	float yPos = aPos.y;
	vec3 n = vec3(0.0f,0.0f,0.0f);


	float frequency;
	float phase;
	float waveCoord;
	
	for(int i = 0; i < nWaves; i ++)
	{
		frequency = 2.0/waves[i].wavelenght;
		phase = waves[i].speed * frequency;
		waveCoord = getWaveCoord(waves[i],aPos);

		yPos += waves[i].amplitude * sin(frequency * waveCoord );

		//vec3 T = vec3(1,0, waves[i].direction.x * cos(dot(waves[i].direction,aPos.xz)));
		//vec3 B = vec3(0,1, waves[i].direction.y * cos(dot(waves[i].direction,aPos.xz)));
		//vec3 normal = cross(B,T);
		vec2 normal = frequency * waves[i].amplitude * waves[i].direction * cos(waveCoord * frequency );
		n += vec3(normal.x,normal.y,0);
	}
	

	normal = n;
	gl_Position = projection * view * model * vec4(aPos.x, yPos, aPos.z,1.0f);
}
