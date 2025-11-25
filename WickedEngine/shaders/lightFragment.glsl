#version 410

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D ambientMap;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2DShadow shadowMap;

uniform vec2 screenSize;

uniform mat4 lightSpaceMatrix;
uniform vec4 cameraPos;

uniform vec4 materialAmbientColor;
uniform vec4 materialDiffuseColor;
uniform vec4 materialSpecularColor;

uniform float lightAttConstantCoefficient;
uniform float lightAttLinearCoefficient;
uniform float lightAttQuadraticCoefficient;

uniform float spotCoeficient; 

uniform float fogDensity = 0;
uniform vec4 fogColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

out vec4 fcolor;

const float globalAttenuation = 0.75f;

void main (void)
{
	vec2 texCoord = gl_FragCoord.xy / screenSize;
	vec3 worldPos = texture(positionMap, texCoord).xyz;
	vec3 worldNormal = normalize(texture(normalMap, texCoord).xyz);
	vec3 ambientColor = texture(ambientMap, texCoord).rgb;
	vec3 diffuseColor = texture(diffuseMap, texCoord).rgb;
	vec4 specularData = texture(specularMap, texCoord);
	vec3 specularColor = specularData.rgb;
	float spotCoeficient = specularData.a;

	vec3 nNorm = texture(normalMap, f.texcoord).rgb;
	nNorm = (nNorm * 2.0) - 1.0;
	nNorm = normalize(TBN * nNorm);

	vec3 lightNorm = normalize(f.lightVector);

	vec4 ambientColor = materialAmbientColor * uniformColor * texture(decal, f.texcoord);
	vec4 diffuseColor = materialDiffuseColor * uniformColor * texture(decal, f.texcoord);
	vec4 specularColor = materialSpecularColor * texture(gloss, f.texcoord);

	float nDotL = dot(worldNormal, lightNorm);

	fcolor = ambientColor * globalAttenuation;

	float lcolor = textureProj(shadowMap, f.lightSpacePos);

	float lightDivisor = lightAttConstantCoefficient;
	lightDivisor += lightAttLinearCoefficient * f.lightDistance;
	lightDivisor += lightAttQuadraticCoefficient * pow(f.lightDistance, 2);

	float lightAttenuation = 1 / lightDivisor;
	lightAttenuation = clamp(lightAttenuation, 0.0f, 1.0f);

	fcolor += diffuseColor * max(0, nDotL) * lightAttenuation * lcolor;

	if (nDotL > 0)
	{
		vec3 refL = normalize(reflect(-lightNorm, worldNormal));
		vec3 eyeVector = normalize(vec3(cameraPos) - f.vWorld);
		fcolor += pow(max(0, dot(refL, eyeVector)), spotCoeficient) * specularColor * lightAttenuation * lcolor;
	}

	//Fog effect
	float cameraDistance = distance(vec3(cameraPos), f.vWorld);
	float fogValue = exp(-pow(cameraDistance * fogDensity, 2));
	fogValue = clamp(fogValue, 0.0f, 1.0f);

	fcolor = fogValue * fcolor + (1 - fogValue) * fogColor;
}