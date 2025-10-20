#pragma once

#include <GLFW/glfw3.h>
#include "Camera.h"
#include "../../General/Vector3.h"
#include "../GameObject.h"

class Camera3D : public Camera
{
public:
	float fOV;
	float zNear, zFar;

	Vector3 eyeVector;
	Vector3 upVector;
	Vector3 centerPos;

	glm::mat4 GetViewMatrix() override;
	glm::mat4 GetProjectionMatrix() override;

	friend class GameObject;

protected:
	inline Camera3D(GameObject* gameObject);
	inline ~Camera3D() {};
};

inline Camera3D::Camera3D(GameObject* gameObject) : Camera(gameObject), fOV(90.0f), zNear(0.1f), zFar(1000.0f),
													centerPos(0,0,0), eyeVector(gameObject->transform.position),
													upVector(0,1,0) {}
