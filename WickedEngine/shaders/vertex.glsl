#version 410

layout (location=0) in vec4 pos;
layout (location=1) in vec3 normal;
layout (location=3) in vec2 texcoord;

uniform mat4 mv;
uniform mat4 nm;
uniform mat4 mvp;

uniform vec4 lightPos;

out data
{
	vec3 vWorld;
	vec3 nWorld;
	vec3 lightVector;
	float  lightDistance;
	vec2 texcoord;
} v;

void main (void)
{
	v.vWorld = vec3(mv * pos);
	v.nWorld = normalize(vec3(nm * vec4(normal, 0.0f)));

	if (lightPos.w == 0)
	{
		v.lightVector = normalize(vec3(lightPos));
		v.lightDistance = 0;
	}
	else
	{
		v.lightVector = normalize(vec3(lightPos) - v.vWorld);
		v.lightDistance = distance(vec3(lightPos), v.vWorld);
	}

	v.texcoord = texcoord;
	gl_Position = mvp * pos;
}

