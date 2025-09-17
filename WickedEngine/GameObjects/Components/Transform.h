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
	
	glm::mat4 getTransformMatrix(const glm::mat4 baseMatrix)
	{
		glm::mat4 transformMatrix = baseMatrix;
		transformMatrix = glm::translate(transformMatrix, (glm::vec3)position);
		glm::vec3 rotationVector;
		for (int i = 0; i < 3; i++)
		{
			rotationVector[i] = 1;
			transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation[i]), rotationVector);
			rotationVector[i] = 0;
		}
		transformMatrix = glm::scale(transformMatrix, (glm::vec3)scale);

		return transformMatrix;
	}
};