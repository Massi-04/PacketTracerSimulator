#pragma once
#include "Core/Base.h"

class Renderer
{
public:
	Renderer() = delete;

	static void Init();
	static void RenderMesh(class Mesh* mesh);

};

