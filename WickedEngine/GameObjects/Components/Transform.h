#pragma once

#include "../../General/Vector3.h"
#include <glm/ext/matrix_transform.hpp>

class GameObject;

class Transform
{
public:
	GameObject& gameObject;

	Vector3 position = { 0,0,0 };
	Vector3 rotation = { 0,0,0 };
	Vector3 scale = { 1,1,1 };

	Transform(GameObject& gameObject) : gameObject(gameObject) {}
	
	glm::mat4 getTransformMatrix()
	{
		glm::mat4 transformMatrix(1);

		transformMatrix = glm::translate(transformMatrix, (glm::vec3)position);

		transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.x), glm::vec3(1, 0, 0));
		transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.y), glm::vec3(0, 1, 0));
		transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.z), glm::vec3(0, 0, 1));

		transformMatrix = glm::scale(transformMatrix, (glm::vec3)scale);

		return transformMatrix;
	}
};