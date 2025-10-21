#pragma once

#include <glm/ext/matrix_transform.hpp>
#include "../../General/Vector3.h"

class GameObject;

class Transform
{
public:
	GameObject& gameObject;

	Vector3 position = { 0,0,0 };
	Vector3 rotation = { 0,0,0 };
	Vector3 scale = { 1,1,1 };

	Transform(GameObject& gameObject) : gameObject(gameObject), parent(nullptr) {}
	glm::mat4 getTransformMatrix() const;
	glm::mat4 GetModelMatrix() const;
	inline Transform* GetParent() const;
	inline void SetParent(Transform* transform);

private:
	Transform* parent;
};

Transform* Transform::GetParent() const
{
	return parent;
}

void Transform::SetParent(Transform* transform)
{
	parent = transform;
}