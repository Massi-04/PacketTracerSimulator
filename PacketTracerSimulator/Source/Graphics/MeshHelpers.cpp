#include "MeshHelpers.h"
#include "Mesh.h"
#include "LineMesh.h"
#include "VertexBuffer.h"

float MeshHelpers::DEFAULT_QUAD_VERTEX_BUFFER[DEFAULT_QUAD_VERTEX_BUFFER_NUM]
{
	-0.5f, -0.5f, 0.0f, 0.0f, // vertex1
	0.5f, -0.5f, 1.0f, 0.0f, // vertex2
	0.5f, 0.5f, 1.0f, 1.0f, // vertex3
	-0.5f, 0.5f, 0.0f, 1.0f // vertex4
};

uint MeshHelpers::DEFAULT_QUAD_INDEX_BUFFER[DEFAULT_QUAD_INDEX_BUFFER_NUM]
{
	0,1,2, // triangle 1
	2,3,0  // triangle 2
};

float MeshHelpers::DEFAULT_LINE_VERTEX_BUFFER[DEFAULT_LINE_VERTEX_BUFFER_NUM]
{
	-0.5f, 0.0f, // start
	0.5f, 0.0f // end
};

uint MeshHelpers::DEFAULT_LINE_INDEX_BUFFER[DEFAULT_LINE_INDEX_BUFFER_NUM]
{
	0, // point 1
	1 // point 2
};

Mesh* MeshHelpers::GetDefaultQuadMesh()
{
	Mesh* mesh = new Mesh();
	static uint attribs[2] = { 2, 2 }; // 2 attibs for the location, 2 for the texture coordinates
	static List<float> vertexBuffer(DEFAULT_QUAD_VERTEX_BUFFER, DEFAULT_QUAD_VERTEX_BUFFER_NUM);
	static List<uint> indexBuffer(DEFAULT_QUAD_INDEX_BUFFER, DEFAULT_QUAD_INDEX_BUFFER_NUM);
	static List<uint> attributes(attribs, 2);
	mesh->SetVertexBuffer(new VertexBuffer(vertexBuffer, indexBuffer, attributes));
	return mesh;
}

LineMesh* MeshHelpers::GetDefaultLineMesh()
{
	LineMesh* mesh = new LineMesh();
	static uint attribs[1] = { 2 }; // 2 attibs for the location
	static List<float> vertexBuffer(DEFAULT_LINE_VERTEX_BUFFER, DEFAULT_LINE_VERTEX_BUFFER_NUM);
	static List<uint> indexBuffer(DEFAULT_LINE_INDEX_BUFFER, DEFAULT_LINE_INDEX_BUFFER_NUM);
	static List<uint> attributes(attribs, 1);
	mesh->SetVertexBuffer(new VertexBuffer(vertexBuffer, indexBuffer, attributes));
	return mesh;
}

Vec2 MeshHelpers::CPUTransformationVertex(const Vec2& actorLocation, const Vec2& actorScale, const Vec2& vertex, float aspectRatio)
{
	Vec2 result = vertex;
	result.x /= aspectRatio;
	result.x *= actorScale.x;
	result.y *= actorScale.y;
	result.x += actorLocation.x * ENGINE_UNIT;
	result.y += actorLocation.y * ENGINE_UNIT;
	return result;
}
