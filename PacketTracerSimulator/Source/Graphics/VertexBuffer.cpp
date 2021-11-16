#include "VertexBuffer.h"
#include "Libs/GL/glew.h"

VertexBuffer::VertexBuffer(const List<float>& vertices, const List<uint>& indices, const List<uint>& attributeSizes)
	: vertices(vertices), indices(indices), attributeSizes(attributeSizes)
{
	// create vao
	glGenVertexArrays(1, &vertexArrayObjectID);
	// create vertex and index buffer
	glCreateBuffers(1, &vertexBufferID);
	glCreateBuffers(1, &indexBufferID);
	Bind(true);
	// allocate memory on gpu
	glBufferData(GL_ARRAY_BUFFER, vertices.GetSize() * sizeof(float), nullptr, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.GetSize() * sizeof(float), nullptr, GL_STATIC_DRAW);
	// Update memory on gpu and buffer layout
	UpdateBuffer(true);
	Bind(false);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteVertexArrays(1, &vertexArrayObjectID);
	glDeleteBuffers(1, &vertexBufferID);
	glDeleteBuffers(1, &indexBufferID);
}

void VertexBuffer::Bind(bool bind)
{
	glBindVertexArray(bind ? vertexArrayObjectID : 0);
	glBindBuffer(GL_ARRAY_BUFFER, bind ? vertexBufferID : 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bind ? indexBufferID : 0);
}

int VertexBuffer::GetNAttributes()
{
	int nAttributes = 0;
	for (int i = 0; i < attributeSizes.GetSize(); i++)
		nAttributes += attributeSizes[i];
	return nAttributes;
}

void VertexBuffer::UpdateBuffer(bool bUpdateLayout)
{
	// Update buffer
	Bind(true);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.GetSize() * sizeof(float), &vertices[0]);
	if (bUpdateLayout)
	{
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices.GetSize() * sizeof(float), &indices[0]);
		int nAttributes = GetNAttributes();
		int offsetPtr = 0;
		// Update buffer layout
		for (int i = 0; i < attributeSizes.GetSize(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, attributeSizes[i], GL_FLOAT, GL_FALSE, sizeof(float) * nAttributes, (const void*)(offsetPtr * sizeof(float)));
			offsetPtr += attributeSizes[i];
		}
	}
	Bind(false);
}
