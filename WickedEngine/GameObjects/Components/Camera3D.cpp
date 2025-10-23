#include "Camera3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp> 
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera3D::GetViewMatrix() const
{
	glm::mat4 view(1.0f);

	view = view * glm::lookAt(glm::vec3(eyeVector), glm::vec3(centerPos), glm::vec3(upVector));

	view = view * glm::inverse(gameObject->transform.GetModelMatrix());

	return view;
}

glm::mat4 Camera3D::GetProjectionMatrix() const
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = (float)viewport[2] / viewport[3];

	return glm::perspective(glm::radians(fOV), ratio, zNear, zFar);
}

glm::vec4 Camera3D::GetCameraPos() const
{
	glm::mat4 transformMatrix = glm::translate(gameObject->transform.GetModelMatrix(), (glm::vec3)eyeVector);

	glm::vec4 globalPos = transformMatrix * glm::vec4(0,0,0,1);

	return globalPos;
}