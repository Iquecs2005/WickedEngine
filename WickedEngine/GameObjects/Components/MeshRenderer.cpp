#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(GameObject* gameObject) : Renderer(gameObject), color(Color::Make())
{

}

void MeshRenderer::Draw(glm::mat4x4 mvp)
{
	ShaderPtr currentShader = material->GetShader();

	currentShader->UseProgram();
	currentShader->SetUniform("M", mvp);
	currentShader->SetUniform("uniformColor", (glm::vec4)*color);

	mesh->Draw();
}