#include "MeshRenderer.h"

void MeshRenderer::Draw(glm::mat4x4 mvp)
{
	ShaderPtr currentShader = material->GetShader();

	currentShader->UseProgram();
	currentShader->SetUniform("M", mvp);
	currentShader->SetUniform("uniformColor", glm::vec4(1, 1, 1, 1));

	mesh->Draw();
}