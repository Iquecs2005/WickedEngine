#include "MeshRenderer.h"

#include "../GameObject.h"

MeshRenderer::MeshRenderer(GameObject* gameObject) : Renderer(gameObject), color(Color::Make())
{

}

void MeshRenderer::Draw(const MVPMatrixPtr mvp)
{
	material->Load();
	ShaderPtr currentShader = material->GetShader();

	currentShader->SetUniform("mv", mvp->model);
	currentShader->SetUniform("nm", glm::inverse(glm::transpose(mvp->model)));
	currentShader->SetUniform("mvp", mvp->mvp);
	currentShader->SetUniform("uniformColor", (glm::vec4)*color);

	mesh->Draw();
	material->Unload();
}