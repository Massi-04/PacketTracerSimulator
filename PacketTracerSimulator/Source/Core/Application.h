#pragma once

#include "Core/Base.h"
#include "Window.h"
#include "Utils/List.h"
#include "GameFramework/Actor.h"

Application& GetApplication();

#define SET_APPLICATION(Class) Application& GetApplication() { static Class app; return app; }

class Application
{
public:
	Application();
	virtual ~Application();

	bool Init();

	inline const WindowData& GetWindowData() const { return window->windowData; }

	void Run();

	template <class T>
	T* SpawnActor()
	{
		Actor* actor = new T();
		actors.Add(actor);
		actor->Start();
		return (T*)actor;
	}

	template <class T>
	T* SpawnActor(Vec2 location, Vec2 size)
	{
		Actor* actor = SpawnActor<T>();
		actor->SetLocation(location);
		actor->SetSize(size);
		return (T*)actor;
	}

	void RemoveActor(Actor* actor);
	void Shutdown();

protected:
	void RemoveAllActors();
	virtual void Start();
	virtual void Update();
	inline const List<Actor*>& GetActors() { return actors; }

private:
	Window* window;
	List<Actor*> actors;
	float time, deltaTime;

	void UpdateTime();
	void Render();
};

