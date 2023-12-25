#version 410 core

#define PI 3.1415

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aNormal;
layout (location = 3) in vec3 aInstancePos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 grassColorTop;
uniform vec3 grassColorBottom;

uniform vec3 camViewDir;
uniform vec3 windDir;
uniform vec3 offset;
uniform float time;
uniform vec3 sun;

out vec2 uv;
out vec3 norm;
out vec3 lightDir;
out vec3 cameraFront;

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
	// Generate basic hash
	uint h = lowbias32(gl_InstanceID + int(offset.x) + int(offset.z)); 
	
	//Rotation for grass blade
	float angle = (h/10.0) *2.0 *3.14 + 0.2;

	// Generate wind with perlin noise
	float windStrengthNoise = pNoise( (aInstancePos.xz+offset.xz) * windDir.xz  * 100.0+ time *200.0f, 2);
	float windDirStrength = windStrengthNoise *1.4f;

	//Calculate normal for the blade 
	vec3 normalvector = vec3(cos(angle) + sin(angle), 0.0f, -sin(angle)+ cos(angle));

	// Create a base curvature for the blade
	float naturalCurvature =((((h%20)/20.0)/2.0)+0.2) * aPos.y ;

	// Create the curvature due to the wind strength and direction
	float windCurvature = windDirStrength * aPos.y ;

	// Calculate final curvature
	float curvature =  naturalCurvature - windCurvature;

	// Create a rotation factor for the blade to "always" be visible even if parralel to the camera
	float viewDotNormal = clamp(dot(camViewDir,normalvector),0.0f,1.0f);	
	float viewSpaceCenteringfactor =  pow(1-viewDotNormal,3);

	//Matrices are created by columns!!!!
	//Calculate rotation matrices for the blade
	//This can be simplified but I keep it that way to be readable
	mat3 curvMat = mat3(1.0, 0.0, 0.0,
						0.0, cos(curvature), sin(curvature),
						0.0, -sin(curvature), cos(curvature));
	
	mat3 rotBlade = mat3(cos(angle),0.0, -sin(angle),
						 0.0, 1.0, 0.0,
						 sin(angle), 0.0, cos(angle));

	mat3 viewSpaceRotation = mat3( cos(viewSpaceCenteringfactor),0.0, -sin(viewSpaceCenteringfactor),
									0.0, 1.0, 0.0,
									sin(viewSpaceCenteringfactor), 0.0, cos(viewSpaceCenteringfactor));

	mat3 finalRotMatrix = viewSpaceRotation * rotBlade * curvMat ;

	vec3 finalPos = finalRotMatrix * aPos;

	vec3 newNormal = finalRotMatrix * aNormal;

	uv = aUV;
	norm = newNormal;
	lightDir = sun;
	cameraFront = camViewDir;
	gl_Position = projection * view * model* vec4(finalPos + aInstancePos + offset, 1.0);
}
 