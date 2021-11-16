#include "Packet.h"
#include "Graphics/MeshHelpers.h"
#include "Graphics/Mesh.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"
#include "Utils/Random.h"
#include "PacketTracerSimulator.h"
#include "Computer.h"

const std::string Packet::colors[3] = {"Pink", "Green", "Blue"};

Packet::Packet() : currentTarget(0), collisionDistance(1.0f), speed(50.0f)
{
	Mesh* packetMesh = MeshHelpers::GetDefaultQuadMesh();
	packetMesh->SetShader(Shader::LoadShader("TexturedVertex.shader.txt", "TexturedFragment.shader.txt"));
	packetMesh->SetTexture(Texture::LoadTexture("Cisco" + colors[GetRandomInt(0, 2)] + "Packet.texture.png"));
	SetScale({ 0.13f, 0.1f });
	SetMesh(packetMesh);
}

void Packet::AddTarget(Actor* target)
{
	targets.Add(target);
}

void Packet::Update(float deltaTime)
{
	Actor::Update(deltaTime);
	MoveToTarget(deltaTime);
}

int Packet::GetNextTarget()
{
	if (currentTarget < targets.GetSize())
		return currentTarget++;
	return -1;
}

void Packet::MoveToTarget(float deltaTime)
{
	static int target = GetNextTarget();
	if (target == -1)
		return;
	float distance = Vec2::GetDistance(GetLocation(), targets[target]->GetLocation());
	if (distance <= collisionDistance)
	{
		Computer* pc = dynamic_cast<Computer*>(targets[target]);
		if (pc != nullptr)
			pc->OnPacketReceived();
		target = GetNextTarget();
		if (target == -1)
		{
			Destroy(); // we reached the last target
			lastPacketReachedCallback.CallProcedure();
			// reset this static variable, it is the same in all instances!
			target = 0;
		}
	}
	else
	{
		Vec2 direction = targets[target]->GetLocation() - GetLocation();
		direction /= direction.GetMagnitude();
		SetLocation(direction * (deltaTime * speed) + GetLocation());
	}

}
