#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <list>

#include "MonoBehaviour.h"
#include "../../Rendering/RenderModifier.h"
#include "../../Rendering/shader.h"

class Camera : public MonoBehaviour
{
public:
	static inline Camera* getMainCamera();

	inline void setMainCamera();

	inline void SetCurrentWindow(GLFWwindow* window);
	inline void SetCurrentShader(ShaderPtr shader);

	void AddRenderModifier(RenderModifierPtr renderModifier);

	void LoadCamera() const;
	void UnloadCamera() const;

	virtual glm::mat4 GetProjectionMatrix() const = 0;
	virtual glm::mat4 GetViewMatrix() const;
	virtual glm::vec4 GetCameraPos() const;

	friend class GameObject;

protected:
	inline Camera(GameObject* gameObject);
	inline ~Camera();

	void UnloadRenderModifiers() const;
	void LoadRenderModifiers() const;

	static Camera* mainCamera;

	GLFWwindow* currentWin;
	ShaderPtr currentShader;

	std::list<RenderModifierPtr> renderModifiers;
};

inline Camera::Camera(GameObject* gameObject) : MonoBehaviour(gameObject), currentWin(nullptr)
{
	if (mainCamera == nullptr)
		this->setMainCamera();
}

inline Camera::~Camera()
{
	std::cout << "Deleted Camera" << std::endl;

	if (mainCamera == this)
	{
		mainCamera = nullptr;
		UnloadRenderModifiers();
	}
}

inline void Camera::SetCurrentWindow(GLFWwindow* window) 
{ 
	currentWin = window; 
}

inline void Camera::SetCurrentShader(ShaderPtr shader)
{
	currentShader = shader;
}

inline Camera* Camera::getMainCamera() { return mainCamera; }

inline void Camera::setMainCamera() 
{ 
	mainCamera = this; 
}

