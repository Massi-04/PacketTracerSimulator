#pragma once
#include "Core/Base.h"
#include "Libs/GLFW/glfw3.h"

enum EKey
{
	A = GLFW_KEY_A,
	B, C, D, E, F, G, H, I, J, K, L, M,
	N, O, P, Q, R, S, T, U, V, W, X, Y,
	Z = GLFW_KEY_Z,
	UnknownKey = GLFW_KEY_UNKNOWN
};

enum EMouseButton
{
	LeftButton = GLFW_MOUSE_BUTTON_LEFT,
	RightButton = GLFW_MOUSE_BUTTON_RIGHT,
	UnknownButton = GLFW_KEY_UNKNOWN
};

enum EActionType
{
	Pressed = GLFW_PRESS,
	Released = GLFW_RELEASE,
	Repeat = GLFW_REPEAT
};

class InputManager
{
public:
	InputManager() = delete;
	
	static void Init(GLFWwindow* window);

	static Vec2 GetMousePosition(bool normalize);
	static EActionType GetMouseButton(EMouseButton button);
	static EActionType GetKey(EKey key);

private:
	static GLFWwindow* window;
};

