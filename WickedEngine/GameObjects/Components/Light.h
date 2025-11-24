#pragma once

#include "../GameObject.h"
#include "MonoBehaviour.h"
#include "Camera.h"

#include "../../Rendering/shader.h"

class Light : public MonoBehaviour
{
public:
	static inline Light* GetCurrentLight();

	static void LoadLights(ShaderPtr currentShader);
protected:
	Light(GameObject* gameObject);
	inline ~Light() {};
	virtual void LoadLight(ShaderPtr currentShader);
private:
	static Light* currentLight;
};

inline Light* Light::GetCurrentLight()
{
	return currentLight;
}