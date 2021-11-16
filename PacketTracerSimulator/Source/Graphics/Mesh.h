#pragma once
#include "Core/Base.h"
#include "Libs/GL/glew.h"

enum EMeshType
{
	Triangles = GL_TRIANGLES,
	Lines = GL_LINES,
};

class Mesh
{
	friend class Renderer;

public:
	Mesh();
	virtual ~Mesh();
	

	inline bool HasBuffer() { return vertexBuffer != nullptr; }
	inline bool HasShader() { return shader != nullptr; }
	inline bool HasTexture() { return texture != nullptr; }
	inline bool IsVisible() const { return bVisible; }

	void SetParent(class Actor* parent);
	void SetType(EMeshType type);
	void SetVertexBuffer(class VertexBuffer* vertexBuffer);
	void SetShader(class Shader* shader);
	void SetTexture(class Texture* texture);
	void SetVisibility(bool bVisible);
	virtual void UpdateMesh();
	inline EMeshType GetType() const { return meshType; }

protected:
	class Actor* parent;
	EMeshType meshType;
	class VertexBuffer* vertexBuffer;
	class Shader* shader;
	class Texture* texture;

private:
	bool bVisible;
};

