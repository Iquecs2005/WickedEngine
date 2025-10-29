#version 410

uniform vec4 uniformColor;

uniform sampler2D decal;
uniform sampler2D gloss;

uniform vec4 cameraPos;

uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform vec4 materialSpecularColor;

uniform float lightAttConstantCoefficient;
uniform float lightAttLinearCoefficient;
uniform float lightAttQuadraticCoefficient;

uniform float spotCoeficient; 

in data 
{
	vec3 vWorld;
	vec3 nWorld;
	vec3 lightVector;
	float lightDistance;
	vec2 texcoord;
} f;

out vec4 fcolor;

const float globalAttenuation = 0.75f;

void main (void)
{
	vec3 vNorm = normalize(f.vWorld);
	vec3 nNorm = normalize(f.nWorld);
	vec3 lightNorm = normalize(f.lightVector);

	vec4 ambientColor = materialAmbientColor * uniformColor * texture(decal, f.texcoord);
	vec4 diffuseColor = materialDiffuseColor * uniformColor * texture(decal, f.texcoord);
	vec4 specularColor = materialSpecularColor * texture(gloss, f.texcoord);

	float nDotL = dot(nNorm, lightNorm);

	fcolor = ambientColor * globalAttenuation;

	float lightDivisor = lightAttConstantCoefficient;
	lightDivisor += lightAttLinearCoefficient * f.lightDistance;
	lightDivisor += lightAttQuadraticCoefficient * pow(f.lightDistance, 2);

	float lightAttenuation = 1 / lightDivisor;
	fcolor += diffuseColor * max(0, nDotL) * lightAttenuation;

	if (nDotL > 0)
	{
		vec3 refL = normalize(reflect(-lightNorm, nNorm));
		vec3 eyeVector = normalize(vec3(cameraPos) - f.vWorld);
		fcolor += pow(max(0, dot(refL, eyeVector)), spotCoeficient) * specularColor * lightAttenuation;
	}
}
