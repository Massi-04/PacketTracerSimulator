#include "Application.h"
#include "Libs/GL/glew.h"
#include "Libs/GLFW/glfw3.h"
#include "Graphics/Renderer.h"
#include "Input/InputManager.h"
#include "Libs/ImGui/imgui.h"
#include "Libs/ImGui/imgui_impl_opengl3.h"
#include "Libs/ImGui/imgui_impl_glfw.h"

Application::Application() : window(nullptr), time(0.0f), deltaTime(0.0f)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	LOG("Application started\n");
}

Application::~Application()
{
	delete window;
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
	LOG("Application terminated\n");
}

bool Application::Init()
{
	if (!glfwInit())
		return false;
	window = new Window(WindowData::LoadWindowData("Config.xml"));
	if (glewInit() != GLEW_OK)
		return false;
	ImGui::CreateContext();
	ImGui::GetIO().IniFilename = ""; // disable .ini file
	if (!ImGui_ImplGlfw_InitForOpenGL(window->window, false))
		return false;
	if (!ImGui_ImplOpenGL3_Init())
		return false;
	InputManager::Init(window->window);
	Renderer::Init();
	LOG("GPU Manufacturer: " << glGetString(GL_VENDOR) << "\n");
	LOG("GPU Model: " << glGetString(GL_RENDERER) << "\n");
	LOG("GPU Driver: " << glGetString(GL_VERSION) << "\n");
	return true;
}

void Application::Run()
{
	Start();
	while (!glfwWindowShouldClose(window->window))
	{
		UpdateTime();
		window->Clear();
		Update();
		Render(); 
		window->Update();
	}
}

void Application::RemoveActor(Actor* actor)
{
	actors.Remove(actor);
	delete actor;
}

void Application::RemoveAllActors()
{
	for (int i = 0; i < actors.GetSize(); i++)
		delete actors[i];
	actors.Erase();
}

void Application::UpdateTime()
{
	float currentTime = glfwGetTime();
	deltaTime = currentTime - time;
	time = glfwGetTime();
}

void Application::Update()
{
	for (int i = 0; i < actors.GetSize(); i++)
		if (actors[i]->bPendingKill)
			RemoveActor(actors[i--]);
		else
			actors[i]->Update(deltaTime);
#ifdef ENGINE_DEBUG
	ImGui::StyleColorsDark();
	ImGui::Begin("Debug info");
	ImGui::Text("GPU manufacturer: %s", glGetString(GL_VENDOR));
	ImGui::Text("GPU model: %s", glGetString(GL_RENDERER));
	ImGui::Text("GPU driver: %s", glGetString(GL_VERSION));
	ImGui::Text("FPS: %f", 1.0f / deltaTime);
	ImGui::End();
	ImGui::StyleColorsLight();
#endif // ENGINE_DEBUG
}

void Application::Shutdown()
{
	RemoveAllActors();
}

void Application::Render()
{
	for (int i = 0; i < actors.GetSize(); i++)
		Renderer::RenderMesh(actors[i]->mesh);
}

void Application::Start()
{
}
