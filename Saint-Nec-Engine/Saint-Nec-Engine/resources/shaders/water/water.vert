#version 410 core

struct Wave
{
	float amplitude;
	float wavelenght;
	float speed;
	float steepness; 
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


vec3 sumOfSineWave(Wave w,vec3 originalPos)
{

	float frequency = 2.0/w.wavelenght;
	float phase = w.speed * frequency;
	float waveCoord = getWaveCoord(w,aPos);

	return vec3(0.0f, w.amplitude * sin(frequency * waveCoord + time * phase ),0.0f);
}

vec3 normalSumOfSineWave(Wave w,vec3 originalPos)
{
	float frequency = 2.0/w.wavelenght;
	float phase = w.speed * frequency;
	float waveCoord = getWaveCoord(w,aPos);
	vec2 normal = frequency * w.amplitude * w.direction * cos(waveCoord * frequency + time * phase );
	return vec3(normal.x,normal.y,0);
}

vec3 gerstnerWave(Wave w,vec3 originalPos)
{

	float frequency = 2.0/w.wavelenght;
	float phase = w.speed * frequency;
	float waveCoord = getWaveCoord(w,aPos);
	float Q = w.steepness/(frequency * w.amplitude * nWaves); //Keep it between 0 and 1/(f*a) to avoid loops

	vec3 res = vec3(0.0f,0.0f,0.0f);

	res.x = w.steepness *w.amplitude* w.direction.x * cos(frequency * waveCoord + time* phase);
	res.z = w.steepness *w.amplitude* w.direction.y * cos(frequency * waveCoord + time* phase);
	res.y = w.amplitude * sin(frequency * waveCoord + time * phase );
	return res;
}


void main()
{
	vec3 n = vec3(0.0f,0.0f,0.0f);
	vec3 p = aPos;

	float frequency;
	float phase;
	float waveCoord;
	
	for(int i = 0; i < nWaves; i ++)
	{
		p += gerstnerWave(waves[i],aPos);
		n += normalSumOfSineWave(waves[i],aPos);
	}
	

	normal = n;
	gl_Position = projection * view * model * vec4(p, 1.0f);
}
