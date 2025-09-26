#include "Camera2D.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp> 
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera2D::GetProjectionMatrix()
{
	int wn_w, wn_h;
	glfwGetWindowSize(currentWin, &wn_w, &wn_h);
	const float w = (float)wn_w;
	const float h = (float)wn_h;
	const float screenRatio = w / h;

	float xmax = cameraWidth;
	float xmin = -cameraWidth;
	float ymax = cameraHeight;
	float ymin = -cameraHeight;

	float dx = xmax - xmin;
	float dy = ymax - ymin;

	if (screenRatio > dx / dy)
	{
		float xc = (xmin + xmax) / 2;
		xmin = xc - dx / 2 * screenRatio;
		xmax = xc + dx / 2 * screenRatio;
	}
	else
	{
		float yc = (ymin + ymax) / 2;
		ymin = yc - dy / 2 / screenRatio;
		ymax = yc + dy / 2 / screenRatio;
	}

	return glm::ortho(xmin, xmax, ymin, ymax);
}