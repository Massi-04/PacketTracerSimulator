#include "Computer.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshHelpers.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Libs/ImGui/imgui.h"
#include "Core/Application.h"
#include "Input/InputManager.h"


Computer::Computer() : packetReceived(0)
{
	Mesh* computerMesh = MeshHelpers::GetDefaultQuadMesh();
	computerMesh->SetShader(Shader::LoadShader("TexturedVertex.shader.txt", "TexturedFragment.shader.txt"));
	computerMesh->SetTexture(Texture::LoadTexture("CiscoComputer.texture.png"));
	SetScale({ 0.3f, 0.3f });
	SetMesh(computerMesh);
}

bool Computer::CanInteract() const
{
	return IsPointInQuadCollision(InputManager::GetMousePosition(true));
}

void Computer::OnPacketReceived()
{
	packetReceived++;
	LOG("PC: " << GetName() << "Has received a packet!!!\n");
}

void Computer::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	Vec2 screenCoord;
	int width = GetApplication().GetWindowData().width;
	int height = GetApplication().GetWindowData().height;
	screenCoord.x = Math::DeNormalize(GetLocation().x * ENGINE_UNIT, width / 2, width);
	screenCoord.y = Math::DeNormalize(GetLocation().y * ENGINE_UNIT * -1, height / 2, height);
	screenCoord.x = Math::Clamp((int)screenCoord.x, 0, width);
	screenCoord.y = Math::Clamp((int)screenCoord.y, 0, height);
	screenCoord.y -= GetScale().y / ENGINE_UNIT * 3.3f;
	screenCoord.x -= 90;
	ImGui::Begin(GetName().c_str(), (bool*)1, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBackground);
	ImGui::SetWindowPos({ screenCoord.x, screenCoord.y });
	ImGui::Text("Packets received: %i", packetReceived);
	ImGui::End();
}

