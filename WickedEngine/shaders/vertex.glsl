#version 410

layout (location=0) in vec4 pos;
layout (location=1) in vec3 normal;
layout (location=2) in vec3 tangent;
layout (location=3) in vec2 texcoord;

uniform mat4 mv;
uniform mat4 nm;
uniform mat4 mvp;

uniform vec4 lightPos;
uniform mat4 lightSpaceMatrix; 

out data
{
	vec3 vWorld;
	vec3 nWorld;
	vec3 tWorld;
	vec3 lightVector;
	float lightDistance;
	vec2 texcoord;
	vec4 lightSpacePos;
} v;

void main (void)
{
	v.vWorld = vec3(mv * pos);
	v.nWorld = normalize(vec3(nm * vec4(normal, 0.0f)));
	v.tWorld = normalize(vec3(nm * vec4(tangent, 0.0f)));

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

	v.lightSpacePos = lightSpaceMatrix * vec4(v.vWorld, 1.0);

	v.texcoord = texcoord;
	gl_Position = mvp * pos;
}