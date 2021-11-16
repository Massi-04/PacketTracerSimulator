#include "Actor.h"
#include "Core/Application.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshHelpers.h"

Actor::Actor() : bPendingKill(false), location(0.0f, 0.0f), scale(1.0f, 1.0f), mesh(nullptr), name("Actor")
{
	LOG("Actor object created\n");
}

Actor::~Actor()
{
	delete mesh;
	LOG("Actor object destroyed" << "(" << name << ")\n");
}

void Actor::Start()
{
	
}

void Actor::Update(float deltaTime)
{
	
}

void Actor::Destroy()
{
	bPendingKill = true;
}

void Actor::SetName(const std::string& name)
{
	this->name = name;
}

void Actor::SetLocation(const Vec2& location)
{
	this->location = location;
}

void Actor::SetScale(const Vec2& scale)
{
	this->scale = scale;
}

void Actor::SetMesh(Mesh* mesh)
{
	delete this->mesh;
	this->mesh = mesh;
	if (mesh != nullptr)
		mesh->SetParent(this);
}

void Actor::GetQuadCollision(Vec2 outQuad[4]) const
{
	// get quad 
	for (int i = 0; i < 4; i++)
	{
		Vec2 point = { MeshHelpers::DEFAULT_QUAD_VERTEX_BUFFER[4 * i], MeshHelpers::DEFAULT_QUAD_VERTEX_BUFFER[4 * i + 1] };
		outQuad[i] = MeshHelpers::CPUTransformationVertex(location, scale, point, GetApplication().GetWindowData().GetAspectRatio());
	}
}

bool Actor::IsPointInQuadCollision(const Vec2& normalizedPoint) const
{
	Vec2 quad[4];
	GetQuadCollision(quad);
	return  
	{
		(normalizedPoint.x >= quad[0].x && normalizedPoint.x <= quad[1].x)
		&&
		(normalizedPoint.y >= quad[0].y && normalizedPoint.y <= quad[3].y)
	};
}
