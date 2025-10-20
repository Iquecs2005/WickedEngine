#pragma once

#include "../GameObject.h"
#include "MonoBehaviour.h"

#include "../../Rendering/shader.h"

class Light : public MonoBehaviour
{
public:
	inline Light* GetCurrentLight();

	static void LoadLights(ShaderPtr currentShader);
protected:
	float lightIntensity;

	Light(GameObject* gameObject) : MonoBehaviour(gameObject), lightIntensity(10)
	{
		currentLight = this;
	}
	inline ~Light() {};
private:
	static Light* currentLight;
};

Light* Light::GetCurrentLight()
{
	return currentLight;
}