#version 410 core

layout (vertices = 4) out;

in vec2 uvs[];
out vec2 uvsCoord[];

uniform vec3 cameraPos;
uniform int minTess;
uniform int maxTess;
uniform float maxDist;



void main()
{
	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position ;
	uvsCoord[gl_InvocationID] = uvs[gl_InvocationID];



	vec4 center0 = gl_in[gl_InvocationID].gl_Position + (gl_in[(gl_InvocationID +3) %4].gl_Position - gl_in[gl_InvocationID].gl_Position) / 2.0; // left side
	float distance = length(center0 - vec4(cameraPos,1.0f));

	float dist0 = length(vec4(cameraPos,1.0f) - center0);
	int tes0 = int(mix(maxTess, minTess, clamp(dist0 / maxDist, 0.0, 1.0)));
	gl_TessLevelOuter[0] = tes0; // left for quads
	gl_TessLevelInner[(gl_InvocationID +1) %2] = max(tes0, gl_TessLevelInner[1]); // left right for quads
	
}