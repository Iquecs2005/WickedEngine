#pragma once

#include "MonoBehaviour.h"

#include <glm/glm.hpp>

class Camera : public MonoBehaviour
{
public:
	inline Camera(GameObject* gameObject);

	virtual glm::mat4 GetProjectionMatrix() = 0;
};

inline Camera::Camera(GameObject* gameObject) : MonoBehaviour(gameObject) {}

