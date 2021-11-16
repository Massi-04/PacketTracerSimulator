#pragma once
#include "Core/Base.h"
#include "Utils/List.h"

class VertexBuffer
{
	friend class Mesh;
	friend class LineMesh;
	friend class Renderer;

public:
	VertexBuffer(const List<float>& vertices, const List<uint>& indices, const List<uint>& attributeSizes);
	~VertexBuffer();

	void Bind(bool bind);

	int GetNAttributes();

	void UpdateBuffer(bool bUpdateLayout);

private:
	uint vertexArrayObjectID;
	uint vertexBufferID;
	uint indexBufferID;

	List<float> vertices;
	List<uint> indices;
	List<uint> attributeSizes;
};

