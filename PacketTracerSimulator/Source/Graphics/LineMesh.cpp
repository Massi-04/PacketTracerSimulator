#include "LineMesh.h"
#include "VertexBuffer.h"

LineMesh::LineMesh()
{
	SetType(EMeshType::Lines);
}

void LineMesh::SetLineCoords(const Vec2& start, const Vec2& end)
{
	this->start = start;
	this->end = end;
}

void LineMesh::UpdateMesh()
{
	vertexBuffer->vertices[0] = start.x;
	vertexBuffer->vertices[1] = start.y;
	vertexBuffer->vertices[2] = end.x;
	vertexBuffer->vertices[3] = end.y;
	vertexBuffer->UpdateBuffer(false);
}
