#version 410

in data 
{
	vec3 vWorld;
	vec3 nWorld;
	vec3 tWorld;
	vec2 texcoord;
} f;

layout (location = 0) out vec3 fPosition;
layout (location = 1) out vec3 fNormal;
layout (location = 2) out vec4 fAmbient;
layout (location = 3) out vec4 fDiffuse;
layout (location = 4) out vec4 fSpecular;

uniform sampler2D decal;
uniform sampler2D gloss;
uniform sampler2D normalMap;

uniform vec4 uniformColor;

uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform vec4 materialSpecularColor;
uniform float spotCoeficient;

mat3 CreateTBNMatrix();

void main (void)
{
	vec3 vNorm = normalize(f.vWorld);

	mat3 TBN = CreateTBNMatrix();

	vec3 nNorm = texture(normalMap, f.texcoord).rgb;
	nNorm = (nNorm * 2.0) - 1.0;
	nNorm = normalize(TBN * nNorm);

	fPosition = f.vWorld.xyz;
	fNormal = nNorm;
	fAmbient = materialAmbientColor * uniformColor * texture(decal, f.texcoord);
	fDiffuse = materialDiffuseColor * uniformColor * texture(decal, f.texcoord);
	fSpecular = materialSpecularColor * texture(gloss, f.texcoord);
	fSpecular.a = spotCoeficient;
}

mat3 CreateTBNMatrix()
{
	vec3 normal = normalize(f.nWorld);
	vec3 tangent = normalize(f.tWorld);
	vec3 binormal = cross(tangent, normal);

	vec3 T = normalize(tangent);
	vec3 B = normalize(binormal);
	vec3 N = normalize(normal);
	
	return mat3(T, B, N);
}