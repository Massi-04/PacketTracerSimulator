#include "Mesh.h"
#include "GameFramework/Actor.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Core/Application.h"
#include "LineMesh.h"

Mesh::Mesh() 
	: parent(nullptr), meshType(EMeshType::Triangles), vertexBuffer(nullptr), shader(nullptr), texture(nullptr),
	bVisible(true)
{
	LOG("Mesh object created\n");
}

Mesh::~Mesh()
{
	delete vertexBuffer;
	delete shader;
	delete texture;
	LOG("Mesh object destroyed\n");
}

void Mesh::SetParent(Actor* parent)
{
	this->parent = parent;
}

void Mesh::SetType(EMeshType type)
{
	this->meshType = type;
}

void Mesh::SetVertexBuffer(VertexBuffer* vertexBuffer)
{
	this->vertexBuffer = vertexBuffer;
}

void Mesh::SetShader(Shader* shader)
{
	this->shader = shader;
	if (this->shader != nullptr)
		this->shader->SetUniform1f("_engineUnit", ENGINE_UNIT);
}

void Mesh::SetTexture(Texture* texture)
{
	this->texture = texture;
}

void Mesh::SetVisibility(bool bVisible)
{
	this->bVisible = bVisible;
}

void Mesh::UpdateMesh()
{
	if (shader != nullptr)
	{
		Vec2 location = parent->GetLocation();
		Vec2 scale = parent->GetScale();
		shader->SetUniform1f("_aspectRatio", GetApplication().GetWindowData().GetAspectRatio());
		shader->SetUniform2f("_location", location.x, location.y);
		shader->SetUniform2f("_scale", scale.x, scale.y);
	}
}


