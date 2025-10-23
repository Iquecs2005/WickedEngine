#pragma once

#include "Camera3D.h"
#include "../../Rendering/Arcball.h"

class ArcballCamera3D : public Camera3D
{
public:
	inline ArcballCamera3D(GameObject* gameObject);
	glm::mat4 GetViewMatrix() const override;
	glm::vec4 GetCameraPos() const override;
	inline ArcballPtr GetArcball() const;
private:
	ArcballPtr arcball;
};

inline ArcballCamera3D::ArcballCamera3D(GameObject* gameObject)
	: Camera3D(gameObject)
{
	Vector3 cameraPos = eyeVector + gameObject->transform.position;
	arcball = Arcball::Make(glm::distance((glm::vec4)cameraPos, (glm::vec4)centerPos));
}

ArcballPtr ArcballCamera3D::GetArcball() const
{
	return arcball;
}