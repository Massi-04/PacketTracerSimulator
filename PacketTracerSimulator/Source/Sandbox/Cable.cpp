#include "Cable.h"
#include "Graphics/LineMesh.h"
#include "Graphics/MeshHelpers.h"
#include "Graphics/Shader.h"

Cable::Cable()
{
	SetConnected(nullptr, nullptr);
	cableMesh = MeshHelpers::GetDefaultLineMesh();
	cableMesh->SetShader(Shader::LoadShader("LineVertex.shader.txt", "CableFragment.shader.txt"));
	SetMesh(cableMesh);
}

void Cable::SetConnected(Actor* start, Actor* end)
{
	connected[0] = start;
	connected[1] = end;
}

void Cable::Update(float ts)
{
	Actor::Update(ts);
	if (connected[0] != nullptr && connected[1] != nullptr)
		cableMesh->SetLineCoords(connected[0]->GetLocation() * ENGINE_UNIT, connected[1]->GetLocation() * ENGINE_UNIT);
}
