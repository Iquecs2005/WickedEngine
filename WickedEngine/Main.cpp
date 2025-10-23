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
#include "Geometry/Square.h"
#include "Geometry/3D/Cube.h"
#include "Geometry/3D/GridGeometry.h"
#include "Geometry/3D/Sphere.h"

#include "General/Vector3.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Components/MeshRenderer.h"
#include "Scene.h"
#include "General/Color.h"
#include "Time.h"
#include "GameObjects/Components/UserCreated/PlanetRotator.h"
#include "GameObjects/Components/Camera2D.h"
#include "GameObjects/Components/Camera3D.h"
#include "GameObjects/Components/ArcballCamera3D.h"
#include "GameObjects/Components/PointLight.h"

#include "Rendering/shader.h"
#include "error.h"

static ShaderPtr shd;

static CirclePtr circleGeometry;
static SquarePtr squareGeometry;
static CubePtr cube;
static GridGeometryPtr grid;
static SpherePtr sphere;

static Scene* sceneptr = new Scene("Sistema Solar");
static Scene& scene = *sceneptr;

static ArcballCamera3D* mainCamera;

static void SolarSystem(GLFWwindow* win)
{
	GameObject* cameraObject = scene.CreateNewGameObject("Camera");
	cameraObject->transform.position.z = 0;
	mainCamera = cameraObject->AttachComponent<ArcballCamera3D>();
	mainCamera->SetCurrentWindow(win);

	MaterialPtr backgroundMaterial = Material::Make(shd);
	backgroundMaterial->AttachTexture(Texture::Make("decal", "Images/Background.jpg"));

	GameObject* background = cameraObject->CreateEmptyChild("Background");
	background->transform.position.z = -1.5f;
	background->transform.scale = { 15, 15, 15 };
	MeshRenderer* backgroundMR = background->AttachComponent<MeshRenderer>();
	backgroundMR->mesh = squareGeometry;
	backgroundMR->AttachMaterial(backgroundMaterial);
	
	MaterialPtr sunMaterial = Material::Make(shd);
	sunMaterial->AttachTexture(Texture::Make("decal", "Images/Sun.jpg"));

	GameObject* sun = scene.CreateNewGameObject("Sun");
	GameObject* sunMesh = sun->CreateEmptyChild("SunMesh");
	MeshRenderer* sunMR = sunMesh->AttachComponent<MeshRenderer>();
	sunMR->mesh = sphere;
	sunMR->AttachMaterial(sunMaterial);

	GameObject* venusPivot = sun->CreateEmptyChild("VenusPivot");
	venusPivot->AttachComponent<PlanetRotator>()->rotatingSpeed = 14;

	MaterialPtr venusMaterial = Material::Make(shd);
	venusMaterial->AttachTexture(Texture::Make("decal", "Images/Venus.jpg"));

	GameObject* venus = venusPivot->CreateEmptyChild("Venus");
	venus->transform.position = Vector3(1.75f, 0, 0);
	venus->transform.scale = Vector3(0.25, 0.25, 0.3);
	GameObject* venusMesh = venus->CreateEmptyChild("VenusMesh");
	MeshRenderer* venusMR = venusMesh->AttachComponent<MeshRenderer>();
	venusMR->mesh = circleGeometry;
	venusMR->AttachMaterial(venusMaterial);

	GameObject* earthPivot = sun->CreateEmptyChild("EarthPivot");
	earthPivot->AttachComponent<PlanetRotator>()->rotatingSpeed = 6;

	MaterialPtr earthMaterial = Material::Make(shd);
	earthMaterial->AttachTexture(Texture::Make("decal", "Images/Earth.jpg"));

	GameObject* earth = earthPivot->CreateEmptyChild("Earth");

	GameObject* earthMesh = earth->CreateEmptyChild("EarthMesh");
	MeshRenderer* earthMR = earthMesh->AttachComponent<MeshRenderer>();
	earthMesh->AttachComponent<PlanetRotator>()->rotatingSpeed = 32;
	earthMR->mesh = circleGeometry;
	earthMR->AttachMaterial(earthMaterial);
	earth->transform.position = Vector3(3.5, 0, 0);
	earth->transform.scale = Vector3(0.5, 0.5, 0.5);

	GameObject* moonPivot = earth->CreateEmptyChild("MoonPivot");
	moonPivot->AttachComponent<PlanetRotator>();

	MaterialPtr moonMaterial = Material::Make(shd);
	moonMaterial->AttachTexture(Texture::Make("decal", "Images/Moon.jpg"));

	GameObject* moon = moonPivot->CreateEmptyChild("Moon");
	MeshRenderer* moonMR = moon->AttachComponent<MeshRenderer>();
	moonMR->mesh = circleGeometry;
	moonMR->AttachMaterial(moonMaterial);
	moon->transform.position = Vector3(2, 0, 0);
	moon->transform.scale = Vector3(0.25, 0.25, 0.25);
}

static void T1(GLFWwindow* win)
{
	GameObject* cameraObject = scene.CreateNewGameObject("Camera");
	cameraObject->transform.position.z = 4;
	mainCamera = cameraObject->AttachComponent<ArcballCamera3D>();
	mainCamera->SetCurrentWindow(win);

	GameObject* lightObject = scene.CreateNewGameObject("Light");
	lightObject->transform.position = { 5, 5, 0 };
	lightObject->AttachComponent<PointLight>();

	MaterialPtr Material = Material::Make(shd);

	GameObject* greenBall1 = lightObject->CreateEmptyChild("GreenBall");
	greenBall1->transform.scale = { 0.5, 0.5, 0.5 };
	greenBall1->transform.rotation = { 90, 0, 0 };
	MeshRenderer* greenBallMR1 = greenBall1->AttachComponent<MeshRenderer>();
	greenBallMR1->mesh = sphere;
	greenBallMR1->color = Color::green;
	greenBallMR1->AttachMaterial(Material);

	GameObject* table = scene.CreateNewGameObject("Table");
	table->transform.position.y = -1.5;
	table->transform.scale = { 8, 1, 8 };
	MeshRenderer* tableMR = table->AttachComponent<MeshRenderer>();
	tableMR->mesh = cube;
	tableMR->AttachMaterial(Material);

	GameObject* rectangle = scene.CreateNewGameObject("YellowCube");
	rectangle->transform.position.y = -0.5;
	rectangle->transform.scale = { 3, 1, 3 };
	MeshRenderer* rectangleMR = rectangle->AttachComponent<MeshRenderer>();
	rectangleMR->mesh = cube;
	rectangleMR->color = Color::yellow;
	rectangleMR->AttachMaterial(Material);

	GameObject* greenBall = scene.CreateNewGameObject("GreenBall");
	greenBall->transform.position.y = 0.75;
	greenBall->transform.scale = {0.8, 0.8, 0.8};
	greenBall->transform.rotation = { 90, 0, 0 };
	MeshRenderer* greenBallMR = greenBall->AttachComponent<MeshRenderer>();
	greenBallMR->mesh = sphere;
	greenBallMR->color = Color::green;
	greenBallMR->AttachMaterial(Material);

	GameObject* redBall = scene.CreateNewGameObject("RedBall");
	redBall->transform.position = {3, -0.15, -3};
	MeshRenderer* redBallMR = redBall->AttachComponent<MeshRenderer>();
	redBallMR->mesh = sphere;
	redBallMR->color = Color::red;
	redBallMR->AttachMaterial(Material);
}

static void initialize(GLFWwindow* win)
{
	glClearColor(0.5, 0.5, 0.5, 0);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	shd = Shader::Make();
	shd->AttachVertexShader("shaders/vertex.glsl");
	shd->AttachFragmentShader("shaders/fragment.glsl");
	shd->Link();
	shd->UseProgram();

	circleGeometry = Circle::Make(65);
	squareGeometry = Square::Make();
	cube = Cube::Make();
	grid = GridGeometry::Make(2, 2);
	sphere = Sphere::Make();

	T1(win);

	scene.printScene();

	Error::Check("initialize");
}

static void error(int code, const char* msg)
{
	printf("GLFW error %d: %s\n", code, msg);
	glfwTerminate();
	exit(0);
}

static void display(GLFWwindow* win)
{
	//Clears the color and depth buffer with the clear color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shd->SetUniform("cameraPos", Camera3D::getMainCamera()->GetCameraPos());
	Light::LoadLights(shd);
	scene.DrawScene();

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

	Error::Check("a");
	mainCamera->GetArcball()->AccumulateMouseMotion((float)x, (float)y);
	Error::Check("b");
}

static void cursorinit(GLFWwindow* win, double xpos, double ypos)
{
	// xpos and ypos are the cursor position in pixels, starting from the top left corner 
	// convert screen pos (upside down) to framebuffer pos (e.g., retina displays)

	int wn_w, wn_h, fb_w, fb_h;
	glfwGetWindowSize(win, &wn_w, &wn_h);
	glfwGetFramebufferSize(win, &fb_w, &fb_h);
	double x = xpos * fb_w / wn_w;
	double y = (wn_h - ypos) * fb_h / wn_h;

	mainCamera->GetArcball()->InitMouseMotion((float)x, (float)y);
	glfwSetCursorPosCallback(win, cursorpos);
}

static void mousebutton(GLFWwindow* win, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (button)
		{
		case GLFW_MOUSE_BUTTON_1:
			//Camera::getMainCamera()->gameObject->transform.position.x -= 1;

			break;
		case GLFW_MOUSE_BUTTON_2:
			//Camera::getMainCamera()->gameObject->transform.position.x += 1;
			break;
		case GLFW_MOUSE_BUTTON_3:
			std::cout << "button 3" << std::endl;
			break;
		}

		glfwSetCursorPosCallback(win, cursorinit);  // cursor position callback
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

	initialize(win);

	double t;
	double t0 = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		t = glfwGetTime();
		Time::deltaTime = t - t0;
		update(t - t0);
		t0 = t;
		display(win);
		glfwSwapBuffers(win);
		//Realizes queued events
		glfwPollEvents();
	}

	delete sceneptr;

	// Destroys remaining windows and cursors
	glfwTerminate();

	std::cout << "Program exit" << std::endl;

	return 0;
}

