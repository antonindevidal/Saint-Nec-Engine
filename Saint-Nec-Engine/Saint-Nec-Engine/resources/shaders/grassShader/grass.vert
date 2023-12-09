#version 410 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV;
layout (location = 2) in vec3 aInstancePos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 grassColorTop;
uniform vec3 grassColorBottom;

out vec2 uv;
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

void main()
{
	uv = aUV;
    uint h = lowbias32(gl_InstanceID);
    float angle = (h/10.0) *2.0 *3.14;
    vec3 pos = aPos +aInstancePos;
	vec3 rotPos = vec3(cos(angle) * aPos.x + sin(angle)* aPos.z,
                        pos.y, 
                        (-sin(angle)* aPos.x) + (cos(angle) * aPos.z));
    gl_Position = projection * view * model* vec4(rotPos + aInstancePos, 1.0);
}
 