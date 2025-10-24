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
	Light(GameObject* gameObject);
	inline ~Light() {};
	virtual void LoadLight(ShaderPtr currentShader);
private:
	static Light* currentLight;
};

Light* Light::GetCurrentLight()
{
	return currentLight;
}