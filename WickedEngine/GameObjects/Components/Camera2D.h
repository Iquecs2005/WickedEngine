#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class Camera2D : public Camera 
{
public:
	float cameraWidth;
	float cameraHeight;

	glm::mat4 GetProjectionMatrix() override;

	friend class GameObject;

protected:
	inline Camera2D(GameObject* gameObject);
	inline ~Camera2D() {};
};

inline Camera2D::Camera2D(GameObject* gameObject) : Camera(gameObject), cameraWidth(5), cameraHeight(5) {}
