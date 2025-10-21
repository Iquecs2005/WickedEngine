#include "Transform.h"

glm::mat4 Transform::getTransformMatrix() const
{
	glm::mat4 transformMatrix(1);

	transformMatrix = glm::translate(transformMatrix, (glm::vec3)position);

	transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.x), glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.y), glm::vec3(0, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, (float)glm::radians(rotation.z), glm::vec3(0, 0, 1));

	transformMatrix = glm::scale(transformMatrix, (glm::vec3)scale);

	return transformMatrix;
}

glm::mat4 Transform::GetModelMatrix() const
{
	glm::mat4 modelMatrix = getTransformMatrix();

	if (parent != nullptr)
		modelMatrix = parent->GetModelMatrix() * modelMatrix;

	return modelMatrix;
}