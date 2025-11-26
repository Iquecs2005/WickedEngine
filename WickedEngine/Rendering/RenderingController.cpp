#include "RenderingController.h"

#include "../error.h"
#include "../GameObjects/Components/Light.h"
#include "../GameObjects/Components/Camera3D.h"
#include "GBuffer.h"

#include <iostream>

ShaderPtr RenderingController::shadowShader = nullptr;
ShaderPtr RenderingController::geometryPassShader = nullptr;
ShaderPtr RenderingController::lightPassShader = nullptr;
DepthTexturePtr RenderingController::depthTex = nullptr;
FrameBufferPtr RenderingController::frameBuffer = nullptr;
QuadPtr RenderingController::cameraQuad = nullptr;

void RenderingController::Initialize()
{
	Error::Check("RenderingController Initialization Start");

	depthTex = DepthTexture::Make("ShadowMap", 1024, 1024);
	frameBuffer = FrameBuffer::Make(1024, 1024, depthTex);
	
	shadowShader = Shader::Make();
	shadowShader->AttachVertexShader("shaders/shadowVertex.glsl");
	shadowShader->AttachFragmentShader("shaders/shadowFragment.glsl");
	shadowShader->Link();

	geometryPassShader = Shader::Make();
	geometryPassShader->AttachVertexShader("shaders/deferredVertex.glsl");
	geometryPassShader->AttachFragmentShader("shaders/deferredFragment.glsl");
	geometryPassShader->Link();

	lightPassShader = Shader::Make();
	lightPassShader->AttachVertexShader("shaders/lightVertex.glsl");
	lightPassShader->AttachFragmentShader("shaders/lightFragment.glsl");
	lightPassShader->Link();

	cameraQuad = Quad::Make();

	Error::Check("RenderingController Initialization End");
}

void RenderingController::Render(GLFWwindow* win, ShaderPtr baseShader, Scene& scene)
{
	Error::Check("Before Rendering");

	//FowardRender(win, baseShader, scene);
	DeferredRender(win, baseShader, scene);

	Error::Check("Render End");
}

void RenderingController::FowardRender(GLFWwindow* win, ShaderPtr baseShader, Scene& scene)
{
	Error::Check("Before Rendering");

	GameObject shadowCameraObject;
	Camera3D* shadowCamera = shadowCameraObject.AttachComponent<Camera3D>();
	Camera* mainCamera = Camera::getMainCamera();

	Error::Check("Before Shadow Mapping Generation");

	glm::mat4 mat;
	if (Light::GetCurrentLight() != nullptr)
	{
		SetUpShadowCamera(win, shadowCamera, Light::GetCurrentLight());
		mat = SetUpShadowShader(shadowShader, shadowCamera);
		GenerateShadowMap(scene);
		DeactivateShadowShader(shadowCamera);
	}

	Error::Check("After Shadow Mapping Generation");

	SetUpShader(baseShader, mainCamera);
	baseShader->SetUniform("lightSpaceMatrix", mat);
	depthTex->Load(baseShader, "shadowMap");

	StandardRender(win, mainCamera, scene);

	depthTex->Unload(baseShader);
	mainCamera->UnloadCamera();

	Error::Check("Render Step 1");

	glfwSwapBuffers(win);
	glfwPollEvents();

	Error::Check("Render End");
}

void RenderingController::DeferredRender(GLFWwindow* win, ShaderPtr baseShader, Scene& scene)
{
	Error::Check("Before Deferred Rendering");

	GameObject shadowCameraObject;
	Camera3D* shadowCamera = shadowCameraObject.AttachComponent<Camera3D>();
	Camera* mainCamera = Camera::getMainCamera();

	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	if (width != 0 && height != 0)
	{
		glViewport(0, 0, width, height);
	}

	Error::Check("Before GBuffer Generation");

	GBufferPtr gBuffer = GBuffer::Make(width, height);

	Error::Check("After GBuffer Generation");

	glm::mat4 mat;
	if (Light::GetCurrentLight() != nullptr)
	{
		SetUpShadowCamera(win, shadowCamera, Light::GetCurrentLight());
		mat = SetUpShadowShader(shadowShader, shadowCamera);
		GenerateShadowMap(scene);
		DeactivateShadowShader(shadowCamera);
	}
	Error::Check("After Shadow Mapping Generation");

	geometryPassShader->UseProgram();
	gBuffer->Activate();
	mainCamera->SetCurrentShader(geometryPassShader);
	mainCamera->setMainCamera();
	mainCamera->LoadCamera();

	glClearColor(0, 0, 0, 0);
	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.DrawScene();

	mainCamera->UnloadCamera();
	gBuffer->Deactivate();

	Error::Check("Deferred Shading: After Geometry pass");
	
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	lightPassShader->UseProgram();
	gBuffer->LoadTextures(lightPassShader);
	lightPassShader->SetUniform("lightSpaceMatrix", mat);
	depthTex->Load(lightPassShader, "shadowMap");
	mainCamera->SetCurrentShader(lightPassShader);
	mainCamera->LoadCamera();
	Light::LoadLights(lightPassShader);

	lightPassShader->SetUniform("screenSize", glm::vec3(width, height, 0));
	lightPassShader->SetUniform("mvp", glm::mat4(1.0f));
	cameraQuad->Draw();

	depthTex->Unload(lightPassShader);
	gBuffer->UnloadTextures(lightPassShader);

	Error::Check("Render Step 1");

	glfwSwapBuffers(win);
	glfwPollEvents();

	Error::Check("Render End");
}

void RenderingController::SetUpShadowCamera(GLFWwindow* win, Camera3D* camera, Light* currentLight)
{
	camera->zNear = 1;
	camera->SetCurrentWindow(win);
	camera->SetCurrentShader(shadowShader);
	camera->gameObject->transform.position = currentLight->gameObject->transform.position;
	//TODO: Calculate the angle correctly
	//TODO: Fix Gimble lock
	camera->gameObject->transform.rotation.y = 90;
	camera->fOV = 90;
}

glm::mat4 RenderingController::SetUpShadowShader(ShaderPtr shader, Camera3D* camera)
{
	frameBuffer->Activate();
	shader->UseProgram();
	camera->LoadCamera();
	camera->setMainCamera();

	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
	glm::mat4 modelView = camera->GetProjectionMatrix() * camera->GetViewMatrix();
	glm::mat4 mat = translate * scale * modelView;
	shader->SetUniform("lightSpaceMatrix", mat);

	return mat;
}

void RenderingController::GenerateShadowMap(Scene& scene)
{
	glCullFace(GL_FRONT);
	glClear(GL_DEPTH_BUFFER_BIT);

	scene.DrawScene();
}

void RenderingController::DeactivateShadowShader(Camera* camera)
{
	frameBuffer->Deactivate();
	camera->UnloadCamera();
}

void RenderingController::SetUpShader(ShaderPtr shader, Camera* camera)
{
	shader->UseProgram();
	camera->setMainCamera();
	camera->LoadCamera();
	Light::LoadLights(shader);
}

void RenderingController::StandardRender(GLFWwindow* win, Camera* camera, Scene& scene)
{
	int width, height;
	glfwGetFramebufferSize(win, &width, &height);
	if (width != 0 && height != 0)
	{
		glViewport(0, 0, width, height);
	}

	glCullFace(GL_BACK);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene.DrawScene();
}