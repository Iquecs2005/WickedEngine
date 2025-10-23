#include "Camera.h"

#include "../GameObject.h"

Camera* Camera::mainCamera = nullptr;

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::mat4(1);
};

glm::vec4 Camera::GetCameraPos() const
{
	return gameObject->transform.GetModelMatrix() * glm::vec4(0,0,0,1);
}