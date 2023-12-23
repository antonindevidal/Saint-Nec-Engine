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


    vec4 cam = vec4(cameraPos,1.0f);
	 if (gl_InvocationID == 0)
    {
        vec4 center0 = gl_in[0].gl_Position + (gl_in[3].gl_Position - gl_in[0].gl_Position) / 2.0; // left side
        vec4 center1 = gl_in[1].gl_Position + (gl_in[0].gl_Position - gl_in[1].gl_Position) / 2.0; // bot side
        vec4 center2 = gl_in[2].gl_Position + (gl_in[1].gl_Position - gl_in[2].gl_Position) / 2.0; // right side
        vec4 center3 = gl_in[3].gl_Position + (gl_in[2].gl_Position - gl_in[3].gl_Position) / 2.0; // top side
        
        float dist0 = length(cam - center0);
        float dist1 = length(cam - center1);
        float dist2 = length(cam - center2);
        float dist3 = length(cam - center3);

        int tes0 = int(mix(maxTess, minTess, clamp(dist0 / maxDist, 0.0, 1.0)));
        int tes1 = int(mix(maxTess, minTess, clamp(dist1 / maxDist, 0.0, 1.0)));
        int tes2 = int(mix(maxTess, minTess, clamp(dist2 / maxDist, 0.0, 1.0)));
        int tes3 = int(mix(maxTess, minTess, clamp(dist3 / maxDist, 0.0, 1.0)));

        gl_TessLevelOuter[0] = tes0; // left for quads
        gl_TessLevelOuter[1] = tes1; // bot for quads
        gl_TessLevelOuter[2] = tes2; // right for quads
        gl_TessLevelOuter[3] = tes3; // top for quads
        
        gl_TessLevelInner[0] = max(tes1, tes3); // top bot for quads
        gl_TessLevelInner[1] = max(tes0, tes2); // left right for quads
    }
}