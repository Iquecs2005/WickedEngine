#pragma once

#ifdef _WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

#include "shader.h"
#include "../Scene.h"
#include "../GameObjects/Components/Camera3D.h"
#include "../GameObjects/Components/Light.h"
#include "FrameBuffer.h"
#include "DepthTexture.h"

class RenderingController
{
public:
	static void Initialize();
	static void Render(GLFWwindow* win, ShaderPtr baseShader, Scene& scene);
private:
	static ShaderPtr shadowShader;
	static DepthTexturePtr depthTex;
	static FrameBufferPtr frameBuffer;

	RenderingController();

	static glm::mat4 GenerateShadowMap(Camera3D* shadowCamera, Light* light, Scene& scene);
};

