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

void Camera::AddRenderModifier(RenderModifierPtr renderModifier) 
{
	renderModifiers.push_back(renderModifier);
}

void Camera::LoadCamera() const
{
	if (currentShader == nullptr)
		std::cerr << "No shader attached to camera" << std::endl;

	currentShader->SetUniform("cameraPos", GetCameraPos());
	LoadRenderModifiers();
}

void Camera::UnloadCamera() const
{
	UnloadRenderModifiers();
}

void Camera::LoadRenderModifiers() const
{
	for (const RenderModifierPtr rmPtr : renderModifiers)
	{
		rmPtr->LoadModifier(currentShader);
	}
}

void Camera::UnloadRenderModifiers() const
{
	for (const RenderModifierPtr rmPtr : renderModifiers)
	{
		rmPtr->UnloadModifier(currentShader);
	}
}