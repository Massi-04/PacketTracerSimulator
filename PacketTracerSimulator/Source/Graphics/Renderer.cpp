#include "Renderer.h"
#include "Libs/GL/glew.h"
#include "Libs/GLFW/glfw3.h"
#include "Mesh.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "Libs/ImGui/imgui.h"

void Renderer::Init()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glActiveTexture(GL_TEXTURE0);
	glLineWidth(1.5f);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // background
	ImGui::StyleColorsLight();
}

void Renderer::RenderMesh(Mesh* mesh)
{
	if (mesh != nullptr && mesh->bVisible && mesh->HasBuffer())
	{
		mesh->UpdateMesh();
		mesh->vertexBuffer->Bind(true);
		if (mesh->HasShader())
			mesh->shader->Bind(true);
		if (mesh->HasTexture())
			mesh->texture->Bind(true);

		glDrawElements(mesh->GetType(), mesh->vertexBuffer->indices.GetSize(), GL_UNSIGNED_INT, nullptr);

		if (mesh->HasShader())
			mesh->shader->Bind(false);
		if (mesh->HasTexture())
			mesh->texture->Bind(false);
		mesh->vertexBuffer->Bind(false);
	}
}
