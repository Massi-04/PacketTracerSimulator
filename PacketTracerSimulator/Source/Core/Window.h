#pragma once
#include "Core/Base.h"

struct WindowData
{
	WindowData();
	WindowData(int width, int height, int refreshrate, bool fullscreen, bool vsync, const std::string& title);

	static WindowData LoadWindowData(const std::string& filePath);

	int width, height, refreshrate;
	bool fullscreen, vsync;
	std::string title;

	inline float GetAspectRatio() const { return (float)width / height; }
};

class Window
{
	friend class Application;

public:
	Window(const WindowData& windowData);

	void Clear();
	void Update();
	void SetWindowData(const WindowData& windowData);

	static void WindowResizeCallback(Window* window, uint width, uint height);

	inline const WindowData& GetWindowData() const { return windowData; }

private:
	WindowData windowData;
	struct GLFWwindow* window;

	void UpdateWindowData();
};

