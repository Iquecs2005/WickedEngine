#pragma once

#include "Camera3D.h"
#include "../../Rendering/Arcball.h"

class ArcballCamera3D : public Camera3D
{
public:
	inline ArcballCamera3D(GameObject* gameObject) : Camera3D(gameObject) 
	{
		arcball = Arcball::Make(glm::distance((glm::vec4)eyeVector, (glm::vec4)centerPos));
	}
	glm::mat4 GetViewMatrix() const override;
	inline ArcballPtr GetArcball() const;
private:
	ArcballPtr arcball;
};

ArcballPtr ArcballCamera3D::GetArcball() const
{
	return arcball;
}