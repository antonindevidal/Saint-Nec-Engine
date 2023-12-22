#version 410 core

#define PI 3.1415

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aInstancePos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 grassColorTop;
uniform vec3 grassColorBottom;

uniform vec3 camViewDir;
uniform vec3 windDir;
uniform vec3 offset;
uniform float time;

out vec2 uv;
out vec3 norm;

// Basic hash function  https://stackoverflow.com/questions/23319289/is-there-a-good-glsl-hash-function
uint lowbias32(uint x)
{
	x ^= x >> 16;
	x *= 0x7feb352dU;
	x ^= x >> 15;
	x *= 0x846ca68bU;
	x ^= x >> 16;
	return x;
}


float remap(float value, float low1, float high1, float low2, float high2)
{
	return low2 + (value - low1) * (high2 - low2) / (high1 - low1);
}


//Perlin noise from https://gist.github.com/patriciogonzalezvivo/670c22f3966e662d2f83
float rand(vec2 c){
	return fract(sin(dot(c.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

float noise(vec2 p, float freq ){
	float unit = 1920/freq;
	vec2 ij = floor(p/unit);
	vec2 xy = mod(p,unit)/unit;
	//xy = 3.*xy*xy-2.*xy*xy*xy;
	xy = .5*(1.-cos(PI*xy));
	float a = rand((ij+vec2(0.,0.)));
	float b = rand((ij+vec2(1.,0.)));
	float c = rand((ij+vec2(0.,1.)));
	float d = rand((ij+vec2(1.,1.)));
	float x1 = mix(a, b, xy.x);
	float x2 = mix(c, d, xy.x);
	return mix(x1, x2, xy.y);
}

float pNoise(vec2 p, int res){
	float persistance = .5;
	float n = 0.;
	float normK = 0.;
	float f = 4.;
	float amp = 1.;
	int iCount = 0;
	for (int i = 0; i<50; i++){
		n+=amp*noise(p, f);
		f*=2.;
		normK+=amp;
		amp*=persistance;
		if (iCount == res) break;
		iCount++;
	}
	float nf = n/normK;
	return nf*nf*nf*nf;
}

void main()
{

	uint h = lowbias32(gl_InstanceID);
	float angle = (h/10.0) *2.0 *3.14;


	//Wind effect
	//Wind strength
	float windStrengthNoise = pNoise( (aInstancePos.xz+offset.xz) *100.0f * windDir.xz + time *200.0f, 3);
	float windDirStrength = windStrengthNoise *8.0f;

	// Curve the blade
	float curvature = ((h%20)/20.0)*aPos.y + windStrengthNoise * 2.0f;
	vec3 curvedPos = vec3( aPos.x,
							(aPos.y * cos(curvature) - aPos.z * sin(curvature))*1.5f,
							aPos.y * sin(curvature) + aPos.z * cos(curvature) );

	curvedPos += windDir * 0.4 * aPos.y;

	// Rotate the blade
	vec3 rotPos = vec3(cos(angle) * curvedPos.x + sin(angle)* curvedPos.z,
						curvedPos.y, 
						(-sin(angle)* curvedPos.x) + (cos(angle) * curvedPos.z));
	


	//Rotate a little if camera dir orthogonal to blade normaL
	vec3 normal = vec3(cos(angle) *0.0f + sin(angle)* 1.0f,
					0.0f, 
					(-sin(angle)* 0.0f) + (cos(angle) * 1.0f));


	float viewDotNormal = clamp(dot(camViewDir,normal),0.0f,1.0f);		
	float factor =  pow(1-viewDotNormal,3);
	vec3 smallRot = vec3(cos(factor) * rotPos.x + sin(factor)* rotPos.z,
						rotPos.y, 
						(-sin(factor)* rotPos.x) + (cos(factor) * rotPos.z));





	uv = aUV;
	norm = vec3(factor,factor,factor);
	gl_Position = projection * view * model* vec4(smallRot + aInstancePos + offset, 1.0);
}
 