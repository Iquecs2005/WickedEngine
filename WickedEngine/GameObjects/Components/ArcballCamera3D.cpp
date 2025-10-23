#include "ArcballCamera3D.h"

#include <glm/gtc/type_ptr.hpp> 
#include <glm/ext/matrix_transform.hpp>

glm::mat4 ArcballCamera3D::GetViewMatrix() const
{
	glm::mat4 view(1.0f);

	view = view * arcball->GetMatrix();
	view = view * Camera3D::GetViewMatrix();

	return view;
}

glm::vec4 ArcballCamera3D::GetCameraPos() const
{
	glm::mat4 rotation = glm::inverse(arcball->GetMatrix());

	glm::mat4 transformMatrix = glm::translate(gameObject->transform.GetModelMatrix(), (glm::vec3)eyeVector);

	glm::vec4 globalPos = transformMatrix * rotation * glm::vec4(0,0,0,1);

	return globalPos;
}