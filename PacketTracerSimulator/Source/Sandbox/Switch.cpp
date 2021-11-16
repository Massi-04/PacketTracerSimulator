#include "Switch.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshHelpers.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Input/InputManager.h"
#include "Core/Application.h"

Switch::Switch()
{
	Mesh* switchMesh = MeshHelpers::GetDefaultQuadMesh();
	switchMesh->SetShader(Shader::LoadShader("TexturedVertex.shader.txt", "TexturedFragment.shader.txt"));
	switchMesh->SetTexture(Texture::LoadTexture("CiscoSwitch.texture.png"));
	SetScale({ 0.2f, 0.1f });
	SetMesh(switchMesh);
}

bool Switch::CanInteract() const
{
	return IsPointInQuadCollision(InputManager::GetMousePosition(true));
}
