#pragma once
#include "Core/Base.h"

#define DEFAULT_QUAD_VERTEX_BUFFER_NUM 16
#define DEFAULT_QUAD_INDEX_BUFFER_NUM 6
#define DEFAULT_LINE_VERTEX_BUFFER_NUM 4
#define DEFAULT_LINE_INDEX_BUFFER_NUM 2

class MeshHelpers
{
public:
	MeshHelpers() = delete;

	static float DEFAULT_QUAD_VERTEX_BUFFER[DEFAULT_QUAD_VERTEX_BUFFER_NUM];
	static uint DEFAULT_QUAD_INDEX_BUFFER[DEFAULT_QUAD_INDEX_BUFFER_NUM];
	static class Mesh* GetDefaultQuadMesh();

	static float DEFAULT_LINE_VERTEX_BUFFER[DEFAULT_LINE_VERTEX_BUFFER_NUM];
	static uint DEFAULT_LINE_INDEX_BUFFER[DEFAULT_LINE_INDEX_BUFFER_NUM];
	static class LineMesh* GetDefaultLineMesh();

	static Vec2 CPUTransformationVertex(const Vec2& actorLocation, const Vec2& actorScale, const Vec2& vertex, float aspectRatio);
};

