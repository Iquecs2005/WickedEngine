#include "RenderingController.h"

#include "../error.h"
#include "../GameObjects/Components/Light.h"
#include "../GameObjects/Components/Camera3D.h"
#include "DepthTexture.h"

#include <iostream>

ShaderPtr RenderingController::shadowShader = nullptr;
DepthTexturePtr RenderingController::depthTex = nullptr;
FrameBufferPtr RenderingController::frameBuffer = nullptr;

void RenderingController::Initialize()
{
	Error::Check("RenderingController Initialization Start");

	depthTex = DepthTexture::Make("ShadowMap", 1024, 1024);
	frameBuffer = FrameBuffer::Make(depthTex, AttachmentType::DepthAttach);
	
	shadowShader = Shader::Make();
	shadowShader->AttachVertexShader("shaders/shadowVertex.glsl");
	shadowShader->AttachFragmentShader("shaders/shadowFragment.glsl");
	shadowShader->Link();

	Error::Check("RenderingController Initialization End");
}

void RenderingController::Render(GLFWwindow* win, ShaderPtr baseShader, Scene& scene)
{
	Error::Check("Before Rendering");

	GameObject shadowCameraObject;
	Camera3D* shadowCamera = shadowCameraObject.AttachComponent<Camera3D>();

	Error::Check("Before Shadow Mapping Generation");
	
	glm::mat4 mat;
	if (Light::GetCurrentLight() != nullptr)
	{
		mat = GenerateShadowMap(win, shadowCamera, Light::GetCurrentLight(), scene);
	}

	Error::Check("After Shadow Mapping Generation");
	
	Camera* mainCamera = Camera::getMainCamera();

	StandardRender(win, mainCamera, scene);

	baseShader->UseProgram();
	mainCamera->setMainCamera();

	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	if (width != 0 && height != 0) 
	{
		glViewport(0, 0, width, height);
	}

	baseShader->SetUniform("lightSpaceMatrix", mat);
	depthTex->Load(baseShader, "shadowMap");

	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Light::LoadLights(baseShader);
	scene.DrawScene();

	depthTex->Unload(baseShader);
	mainCamera->UnloadCamera();

	Error::Check("Render Step 1");

	glfwSwapBuffers(win);
	glfwPollEvents();

	Error::Check("Render End");
}

glm::mat4 RenderingController::GenerateShadowMap(GLFWwindow* win, Camera3D* shadowCamera, Light* light, Scene& scene)
{
	shadowCamera->zNear = 1;
	shadowCamera->SetCurrentWindow(win);
	shadowCamera->SetCurrentShader(shadowShader);
	shadowCamera->gameObject->transform.position = light->gameObject->transform.position;
	//TODO: Calculate the angle correctly
	//TODO: Fix Gimble lock
	shadowCamera->gameObject->transform.rotation.y = 90;
	shadowCamera->fOV = 90;

	frameBuffer->Activate();
	shadowShader->UseProgram();
	shadowCamera->LoadCamera();
	shadowCamera->setMainCamera();

	glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 modelView = shadowCamera->GetProjectionMatrix() * shadowCamera->GetViewMatrix();
	glm::mat4 mat = translate * scale * modelView;
	shadowShader->SetUniform("lightSpaceMatrix", mat);

	scene.DrawScene();

	shadowCamera->UnloadCamera();
	frameBuffer->Deactivate();

	return mat;
}

void RenderingController::StandardRender(GLFWwindow* win, ShaderPtr shader, Camera* camera, Scene& scene)
{
	shader->UseProgram();
	camera->setMainCamera();
	camera->LoadCamera();

	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	if (width != 0 && height != 0)
	{
		glViewport(0, 0, width, height);
	}

	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Light::LoadLights(shader);
	scene.DrawScene();

	camera->UnloadCamera();
}