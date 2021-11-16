#include "Window.h"
#include "Libs/GLFW/glfw3.h"
#include "Libs/ImGui/imgui.h"
#include "Libs/ImGui/imgui_impl_opengl3.h"
#include "Libs/ImGui/imgui_impl_glfw.h"
#include "Utils/TextParser.h"
#include "Libs/RapidXML/rapidxml.hpp"
#include "Utils/FileManager.h"

Window::Window(const WindowData& windowData) : window(nullptr)
{
	window = glfwCreateWindow(windowData.width, windowData.height, windowData.title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) 
	{ 
		Window::WindowResizeCallback((Window*)glfwGetWindowUserPointer(window), width, height); 
	});
	SetWindowData(windowData);
}

void Window::Clear()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Update()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwPollEvents();
	glfwSwapBuffers(window);
}

void Window::SetWindowData(const WindowData& windowData)
{
	this->windowData = windowData;
	UpdateWindowData();
}

void Window::WindowResizeCallback(Window* window, uint width, uint height)
{
	if (window != nullptr)
	{
		window->windowData.width = width;
		window->windowData.height = height;
		glViewport(0, 0, width, height);
	}
}

void Window::UpdateWindowData()
{
	WindowData& data = windowData;
	glfwSetWindowMonitor(window, data.fullscreen ? glfwGetPrimaryMonitor() : nullptr, 100, 100, data.width, data.height, data.refreshrate);
	glfwSwapInterval(data.vsync ? 1 : 0);
#ifdef ENGINE_DEBUG
	glfwSetWindowTitle(window, (data.title + " - Development version").c_str());
#else
	glfwSetWindowTitle(window, data.title.c_str());
#endif
}

WindowData::WindowData() : width(1280), height(720), refreshrate(GLFW_DONT_CARE), fullscreen(false), vsync(false), title("Window")
{
}

WindowData::WindowData(int width, int height, int refreshrate, bool fullscreen, bool vsync, const std::string& title)
	: width(width), height(height), refreshrate(refreshrate), fullscreen(fullscreen), vsync(vsync), title(title)
{
}

WindowData WindowData::LoadWindowData(const std::string& filePath)
{
	WindowData result;
	std::string file = FileManager::ReadFile(filePath);
	if (!file.empty())
	{
		rapidxml::xml_document<>* configXml = new rapidxml::xml_document<>();
		configXml->parse<0>(&file[0]);
		rapidxml::xml_node<>* root = configXml->first_node("EngineConfig");
		if (root != nullptr)
		{
			rapidxml::xml_node<>* widthNode = root->first_node("ResolutionX");
			rapidxml::xml_node<>* heightNode = root->first_node("ResolutionY");
			rapidxml::xml_node<>* fullscreenNode = root->first_node("Fullscreen");
			rapidxml::xml_node<>* vsyncNode = root->first_node("VSync");
			rapidxml::xml_node<>* titleNode = root->first_node("Title");
			if (widthNode != nullptr && heightNode != nullptr && fullscreenNode != nullptr && vsyncNode != nullptr && titleNode != nullptr)
			{
				TextParser::ParseInt(widthNode->value(), result.width);
				TextParser::ParseInt(heightNode->value(), result.height);
				result.refreshrate = GLFW_DONT_CARE;
				result.fullscreen = std::string("True").compare(fullscreenNode->value()) == 0;
				result.vsync = std::string("True").compare(vsyncNode->value()) == 0;
				result.title = titleNode->value();
			}
		}
		delete configXml;
	}
	return result;
}
