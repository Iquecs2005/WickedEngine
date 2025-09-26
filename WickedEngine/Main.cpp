#ifdef _WIN32

#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#undef GLAD_GL_IMPLEMENTATION
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

#include <iostream>
#include <chrono>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Geometry/Polygon.h"
#include "Geometry/Circle.h"
#include "Geometry/Triangle.h"
#include "General/Vector3.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "Scene.h"
#include "General/Color.h"
#include "Time.h"
#include "GameObjects/Components/UserCreated/PlanetRotator.h"
#include "GameObjects/Components/Camera2D.h"

#include "Rendering/shader.h"
#include "error.h"

static ShaderPtr shd;

static CirclePtr circleGeometry;

static Scene scene;
static GameObjectPtr earthPivot;
static GameObjectPtr moonPivot;

static void initialize()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_CULL_FACE);

	shd = Shader::Make();
	shd->AttachVertexShader("shaders/vertex.glsl");
	shd->AttachFragmentShader("shaders/fragment.glsl");
	shd->Link();

	circleGeometry = Circle::Make(65);

	MaterialPtr defaultMaterial = Material::Make(shd);

	GameObjectPtr sun = scene.CreateNewGameObject("Sun");
	MeshRenderer* sunMR = sun->AttachComponent<MeshRenderer>();
	sunMR->mesh = circleGeometry;
	sunMR->AttachMaterial(defaultMaterial);
	sunMR->color->SetColor(1.0f, 0.4f, 0.0f);

	GameObjectPtr cameraObject = sun->CreateEmptyChild("Camera");
	Camera2D* camera2D = cameraObject->AttachComponent<Camera2D>();

	earthPivot = sun->CreateEmptyChild("EarthPivot");
	earthPivot->transform.rotation = Vector3(0,0,0);
	earthPivot->AttachComponent<PlanetRotator>()->rotatingSpeed = 6;
	GameObjectPtr earth = earthPivot->CreateEmptyChild("Earth");
	MeshRenderer* earthMR = earth->AttachComponent<MeshRenderer>();
	earthMR->mesh = circleGeometry;
	earthMR->AttachMaterial(defaultMaterial);
	earthMR->color->SetColor(50, 170, 230);
	earth->transform.position = Vector3(3.5, 0, 0);
	earth->transform.scale = Vector3(0.5, 0.5, 0.5);

	moonPivot = earth->CreateEmptyChild("MoonPivot");
	moonPivot->transform.rotation = Vector3(0, 0, 0);
	moonPivot->AttachComponent<PlanetRotator>();
	GameObjectPtr moon = moonPivot->CreateEmptyChild("Earth");
	MeshRenderer* moonMR = moon->AttachComponent<MeshRenderer>();
	moonMR->mesh = circleGeometry;
	moonMR->AttachMaterial(defaultMaterial);
	moonMR->color->SetColor(200, 200, 200);
	moon->transform.position = Vector3(2, 0, 0);
	moon->transform.scale = Vector3(0.25, 0.25, 0.25);

	/*GameObjectPtr child1_1 = child1->CreateEmptyChild("child1.1");
	MeshRenderer* child1_1MR = child1_1->AttachComponent<MeshRenderer>();
	child1_1MR->mesh = circleGeometry;
	child1_1MR->AttachMaterial(defaultMaterial);
	child1_1->transform.position = Vector3(2, 0, 0);*/
	//scene.CreateNewGameObject("child2", root1);
	//root1->createEmptyChild("child3");
	//scene.CreateNewGameObject("GameObject2")->createEmptyChild("child1");;
	//scene.CreateNewGameObject("GameObject3");
	//scene.printScene();
	//secondsPointer.geometryList.push_front(triangleGeometry);

	Error::Check("initialize");
}

static void error(int code, const char* msg)
{
	printf("GLFW error %d: %s\n", code, msg);
	glfwTerminate();
	exit(0);
}

static glm::mat4 getDistorcionlessMatrix(GLFWwindow* win)
{
	int wn_w, wn_h;
	glfwGetWindowSize(win, &wn_w, &wn_h);
	const float w = (float)wn_w;
	const float h = (float)wn_h;
	const float screenRatio = w / h;

	float xmax = 5;
	float xmin = -5;
	float ymax = 5;
	float ymin = -5;

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

static void display(GLFWwindow* win)
{
	const glm::mat4 distorcionlessMatrix = getDistorcionlessMatrix(win);
	glm::vec4 uniformColor;

	//Clears the color and depth buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	shd->UseProgram();

	uniformColor = glm::vec4(1, 1, 1, 1);
	shd->SetUniform("uniformColor", uniformColor);

	scene.DrawScene(distorcionlessMatrix);

	//M = distorcionlessMatrix;
	//M = glm::scale(M, { 3, 3, 1 });
	//shd->SetUniform("M", M);
	//
	//uniformColor = glm::vec4(1,1,1,1);
	//shd->SetUniform("uniformColor", uniformColor);

	//circleGeometry->Draw();

	//auto now = std::chrono::system_clock::now();
	//std::time_t time_t_now = std::chrono::system_clock::to_time_t(now);

	//std::tm local_tm;
	//#ifdef _WIN32
	//	localtime_s(&local_tm, &time_t_now);
	//#else
	//	localtime_r(&time_t_now, &local_tm);
	//#endif

	//auto miliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
	//float seconds = time_t_now % 60 + (float)miliseconds.count() / 1000;
	//float minutes = (time_t_now / 60) % 60 + seconds / 60;
	//float hour = local_tm.tm_hour + minutes / 60;

	///*M = distorcionlessMatrix;
	//M = glm::rotate(M, (float)glm::radians(360 * seconds / 60), glm::vec3(0, 0, -1));
	//M = glm::scale(M, { 0.1, 2.75, 1 });*/
	//
	//secondsPointer.transform.rotation = Vector3(0, 0, -6 * seconds);
	//uniformColor = glm::vec4(0.9, 0.3, 0.3, 1);
	//shd->SetUniform("uniformColor", uniformColor);
	//secondsPointer.Draw(distorcionlessMatrix, shd);

	//M = distorcionlessMatrix;
	//M = glm::rotate(M, (float)glm::radians(360 * minutes / 60), glm::vec3(0, 0, -1));
	//M = glm::scale(M, { 0.1, 2, 1 });
	//shd->SetUniform("M", M);

	//uniformColor = glm::vec4(0, 0, 0, 1);
	//shd->SetUniform("uniformColor", uniformColor);

	//triangleGeometry->Draw();

	//M = distorcionlessMatrix;
	//M = glm::rotate(M, (float)glm::radians(360 * hour / 12), glm::vec3(0, 0, -1));
	//M = glm::scale(M, { 0.1, 1, 1 });
	//shd->SetUniform("M", M);

	//triangleGeometry->Draw();

	//M = distorcionlessMatrix;
	//M = glm::scale(M, { 0.2, 0.2, 0.2 });
	//shd->SetUniform("M", M);

	//uniformColor = glm::vec4(0.5, 0.5, 0.5, 1);
	//shd->SetUniform("uniformColor", uniformColor);

	//circleGeometry->Draw();

	Error::Check("display");
}

static void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_Q && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static void resize(GLFWwindow* win, int width, int height)
{
	glViewport(0, 0, width, height);
	display(win);
	glfwSwapBuffers(win);
}

static void cursorpos(GLFWwindow* win, double xpos, double ypos)
{
	// xpos and ypos are the cursor position in pixels, starting from the top left corner 
	// convert screen pos (upside down) to framebuffer pos (e.g., retina displays)

	int wn_w, wn_h, fb_w, fb_h;
	glfwGetWindowSize(win, &wn_w, &wn_h);
	glfwGetFramebufferSize(win, &fb_w, &fb_h);
	double x = xpos * fb_w / wn_w;
	double y = (wn_h - ypos) * fb_h / wn_h;
	std::cout << "(x,y): " << x << ", " << y << std::endl;
}

static void mousebutton(GLFWwindow* win, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
			std::cout << "button 1" << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_2:
			std::cout << "button 2" << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_3:
			std::cout << "button 3" << std::endl;
			break;
		}

		glfwSetCursorPosCallback(win, cursorpos);  // cursor position callback
	}
	else // GLFW_RELEASE 
		glfwSetCursorPosCallback(win, nullptr);   // callback disabled
}

static void update(double dt)
{
	//scene.UpdateScene();
}

int main()
{
	glfwSetErrorCallback(error);

	if (glfwInit() != GLFW_TRUE) {
		std::cerr << "Could not initialize GLFW" << std::endl;
		return 0;
	}
	//Tells GLFW the current OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	//Tells GLFW to use the core profile of OPENGL
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);     // required for mac os

#if __APPLE__
	glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);  // option for mac os
#endif

	GLFWwindow* win = glfwCreateWindow(600, 600, "Window title", nullptr, nullptr);
	if (!win)
	{
		std::cerr << "Could not create GLFW window" << std::endl;
		return 0;
	}
	glfwMakeContextCurrent(win);

#ifdef GLAD_GL_H_
	// Initializes glad
	if (!gladLoadGL(glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD OpenGL context\n");
		exit(1);
	}
#endif

	std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;

	glfwSetFramebufferSizeCallback(win, resize);  // resize callback
	glfwSetKeyCallback(win, keyboard);   // keyboard callback
	glfwSetMouseButtonCallback(win, mousebutton); // mouse button callback

	initialize();


	//QuadPtr square = Quad::Make();
	double t;
	double t0 = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		t = glfwGetTime();
		Time::deltaTime = t - t0;
		update(t - t0);
		t0 = t;
		display(win);
		//square->Draw();
		glfwSwapBuffers(win);
		//Realizes queued events
		glfwPollEvents();
	}

	// Destroys remaining windows and cursors
	glfwTerminate();

	return 0;
}

