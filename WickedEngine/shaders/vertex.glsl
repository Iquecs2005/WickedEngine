#version 410

layout (location=0) in vec4 pos;
layout (location=1) in vec3 normal;
layout (location=2) in vec3 tangent;
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
	float lightDistance;
	vec2 texcoord;
	mat3 TBN;
} v;

mat3 CreateTBNMatrix();

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

	v.TBN = CreateTBNMatrix();
}

mat3 CreateTBNMatrix()
{
	vec3 binormal = cross(tangent, normal);

	vec3 T = normalize(vec3(nm * vec4(tangent,  0.0)));
	vec3 B = normalize(vec3(nm * vec4(binormal, 0.0)));
	vec3 N = normalize(vec3(nm * vec4(normal,   0.0)));
	
	return mat3(T, B, N);
}

