#include "Camera3D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp> 
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera3D::GetViewMatrix()
{
	return glm::lookAt(glm::vec3(eyeVector), glm::vec3(centerPos), glm::vec3(upVector));
}

glm::mat4 Camera3D::GetProjectionMatrix()
{
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float ratio = (float)viewport[2] / viewport[3];

	return glm::perspective(glm::radians(fOV), ratio, zNear, zFar);
}