#version 410

layout (location = 0) in vec4 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 tangent;
layout (location = 3) in vec2 texcoord;

uniform mat4 mv;
uniform mat4 lightSpaceMatrix; 

void main (void)
{
	gl_Position = lightSpaceMatrix * mv * pos;
}