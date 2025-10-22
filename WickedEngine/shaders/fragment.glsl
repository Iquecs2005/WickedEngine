#version 410

uniform vec4 uniformColor;
uniform sampler2D decal;

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
const vec4 materialSpecularColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
const float spotCoeficient = 1.0f; 
const float lightAttConstantCoefficient = 1;
const float lightAttLinearCoefficient = 0.25f;
const float lightAttQuadraticCoefficient = 0.1f;

void main (void)
{
	vec3 vNorm = normalize(f.vWorld);
	vec3 nNorm = normalize(f.nWorld);
	vec3 lightNorm = normalize(f.lightVector);

	vec4 materialAmbientColor = uniformColor * texture(decal, f.texcoord);
	vec4 materialDiffuseColor = materialAmbientColor;

	float nDotL = dot(nNorm, lightNorm);

	fcolor = materialAmbientColor * globalAttenuation;

	float lightDivisor = lightAttConstantCoefficient;
	lightDivisor += lightAttLinearCoefficient * f.lightDistance;
	lightDivisor += lightAttQuadraticCoefficient * pow(f.lightDistance, 2);

	float lightAttenuation = 1 / lightDivisor;
	fcolor += materialDiffuseColor * max(0, nDotL) * lightAttenuation;

	if (nDotL > 0)
	{
		vec3 refL = normalize(reflect(-lightNorm, nNorm));
		fcolor += materialSpecularColor * pow(max(0, dot(refL, normalize(-vNorm))), spotCoeficient) * lightAttenuation;
	}

	//fcolor = uniformColor * texture(decal, f.texcoord);
}
