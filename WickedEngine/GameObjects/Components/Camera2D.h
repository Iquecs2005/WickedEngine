#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"

class Camera2D : public Camera 
{
public:
	float cameraWidth;
	float cameraHeight;

	inline Camera2D(GameObject* gameObject);
	glm::mat4 GetProjectionMatrix() override;
	inline void SetCurrentWindow(GLFWwindow* window);
private:
	GLFWwindow* currentWin;
};

inline Camera2D::Camera2D(GameObject* gameObject) : Camera(gameObject), cameraWidth(5), cameraHeight(2.8125f), currentWin(nullptr) {}
inline void Camera2D::SetCurrentWindow(GLFWwindow* window) { currentWin = window; }