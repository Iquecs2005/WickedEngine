#version 410

uniform sampler2D positionMap;
uniform sampler2D normalMap;
uniform sampler2D ambientMap;
uniform sampler2D diffuseMap;
uniform sampler2D specularMap;
uniform sampler2DShadow shadowMap;

uniform vec3 screenSize;
uniform vec4 cameraPos;

uniform vec4 lightPos;
uniform mat4 lightSpaceMatrix;

uniform float lightAttConstantCoefficient;
uniform float lightAttLinearCoefficient;
uniform float lightAttQuadraticCoefficient;

uniform float fogDensity = 0;
uniform vec4 fogColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

const float globalAttenuation = 0.75f;

out vec4 fcolor;

void main (void)
{
	vec2 texCoord = gl_FragCoord.xy / screenSize.xy;
	vec3 worldPos = texture(positionMap, texCoord).xyz;
	vec3 worldNormal = normalize(texture(normalMap, texCoord).xyz);
	vec4 ambientColor = texture(ambientMap, texCoord);
	vec4 diffuseColor = texture(diffuseMap, texCoord);
	vec4 specularData = texture(specularMap, texCoord);
	vec4 specularColor = vec4(specularData.rgb, 1);
	float spotCoeficient = specularData.a;

	vec3 lightVector;
	float lightDistance;
	if (lightPos.w == 0)
	{
		lightVector = normalize(vec3(lightPos));
		lightDistance = 0;
	}
	else
	{
		lightVector = normalize(vec3(lightPos) - worldPos);
		lightDistance = distance(vec3(lightPos), worldPos);
	}

	float nDotL = dot(worldNormal, lightVector);

	//fcolor = ambientColor * globalAttenuation;
	fcolor = ambientColor;

	vec4 lightSpacePos = lightSpaceMatrix * vec4(worldPos, 1.0);
	float lcolor = textureProj(shadowMap, lightSpacePos);
	lcolor = 1;

	float lightDivisor = lightAttConstantCoefficient;
	lightDivisor += lightAttLinearCoefficient * lightDistance;
	lightDivisor += lightAttQuadraticCoefficient * pow(lightDistance, 2);

	float lightAttenuation = 1 / lightDivisor;
	lightAttenuation = clamp(lightAttenuation, 0.0f, 1.0f);

	fcolor += diffuseColor * max(0, nDotL) * lightAttenuation * lcolor;

	if (nDotL > 0)
	{
		vec3 refL = normalize(reflect(-lightVector, worldNormal));
		vec3 eyeVector = normalize(vec3(cameraPos) - worldPos);
		fcolor += pow(max(0, dot(refL, eyeVector)), spotCoeficient) * specularColor * lightAttenuation * lcolor;
	}

	//Fog effect
	float cameraDistance = distance(vec3(cameraPos), worldPos);
	float fogValue = exp(-pow(cameraDistance * fogDensity, 2));
	fogValue = clamp(fogValue, 0.0f, 1.0f);

	fcolor = fogValue * fcolor + (1 - fogValue) * fogColor;
}