#version 410

layout (location=0) in vec4 pos;
layout (location=1) in vec3 normal;
layout (location=3) in vec2 texcoord;

uniform mat4 mv;
uniform mat4 nm;
uniform mat4 mvp;

out data
{
	vec2 texcoord;
} v;

void main (void)
{
  v.texcoord = texcoord;
  gl_Position = mvp * pos;
}

