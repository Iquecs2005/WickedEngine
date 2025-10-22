#include "ArcballCamera3D.h"

#include <glm/gtc/type_ptr.hpp> 

glm::mat4 ArcballCamera3D::GetViewMatrix() const
{
	glm::mat4 view(1.0f);

	view = view * arcball->GetMatrix();
	view = view * Camera3D::GetViewMatrix();

	return view;
}