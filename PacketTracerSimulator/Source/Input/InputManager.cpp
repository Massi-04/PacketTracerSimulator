#include "InputManager.h"
#include "Core/Window.h"
#include "Core/Application.h"

GLFWwindow* InputManager::window = nullptr;

void InputManager::Init(GLFWwindow* window)
{
	InputManager::window = window;
}

Vec2 InputManager::GetMousePosition(bool normalize)
{
	WindowData windowData = GetApplication().GetWindowData();
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	x = Math::Clamp(x, 0.0, (double)windowData.width);
	y = Math::Clamp(y, 0.0, (double)windowData.height);
	if (normalize)
	{
		int width = windowData.width;
		int height = windowData.height;
		x = Math::Normalize(x, width / 2, width);
		y = Math::Normalize(y, height / 2, height) * -1.0;
	}
	return Vec2(x, y);
}

EActionType InputManager::GetMouseButton(EMouseButton button)
{
	return (EActionType)glfwGetMouseButton(window, button);
}

EActionType InputManager::GetKey(EKey key)
{
	return (EActionType)glfwGetKey(window, key);
}
