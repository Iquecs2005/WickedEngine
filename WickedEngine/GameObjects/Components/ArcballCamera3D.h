#pragma once

#include "Camera3D.h"
#include "../../Rendering/Arcball.h"

class ArcballCamera3D : public Camera3D
{
public:
	inline ArcballCamera3D(GameObject* gameObject) : Camera3D(gameObject), arcball(1) {}
	glm::mat4 GetViewMatrix() const override;
private:
	Arcball arcball;
};

