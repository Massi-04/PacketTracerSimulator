#include "Light.h"
#include "Graphics/Mesh.h"
#include "Graphics/MeshHelpers.h"
#include "Graphics/Shader.h"

Light::Light() : colorChangeSpeed(2.0f), currentAlpha(0.0f), sending(false)
{
	Mesh* lightMesh = MeshHelpers::GetDefaultQuadMesh();
	lightShader = Shader::LoadShader("Vertex.shader.txt", "LightFragment.shader.txt");
	lightMesh->SetShader(lightShader);
	SetMesh(lightMesh);
}

void Light::SetSending(bool sending)
{
	currentAlpha = 0.0f; // reset alpha
	lightShader->SetUniform4f("_color", 1.0f, 0.0f, 0.0f, 0.0f);
	this->sending = sending;
}

void Light::Update(float deltaTime)
{
	Actor::Update(deltaTime); 
	if (!sending) return;
	static float dir = 1.0f;
	currentAlpha += colorChangeSpeed * deltaTime * dir;
	if (currentAlpha >= 1.0f)
		dir = -1.0f;
	if (currentAlpha <= 0.0f)
		dir = 1.0f;
	lightShader->SetUniform4f("_color", 1.0f, 0.0f, 0.0f, currentAlpha);
}
