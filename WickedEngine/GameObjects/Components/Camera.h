#pragma once

#include "MonoBehaviour.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class Camera : public MonoBehaviour
{
public:
	static inline Camera* getMainCamera();
	inline void setMainCamera();
	inline void SetCurrentWindow(GLFWwindow* window);
	virtual glm::mat4 GetProjectionMatrix() = 0;

	friend class GameObject;

protected:
	inline Camera(GameObject* gameObject);
	inline ~Camera();

	GLFWwindow* currentWin;
	static Camera* mainCamera;
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
		mainCamera = nullptr;
}

inline void Camera::SetCurrentWindow(GLFWwindow* window) 
{ 
	currentWin = window; 
}

inline Camera* Camera::getMainCamera() { return mainCamera; }
inline void Camera::setMainCamera() { mainCamera = this; }

