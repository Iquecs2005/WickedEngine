#include <memory>

class MVPMatrix;
using MVPMatrixPtr = std::shared_ptr<MVPMatrix>;

#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <iostream>

class MVPMatrix
{
protected:
	MVPMatrix(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
		: model(model), view(view), projection(projection), mvp(projection * view * model)
	{
	}
	MVPMatrix(const glm::mat4& model, const MVPMatrixPtr& baseMvp)
		: model(baseMvp->model * model), view(baseMvp->view), projection(baseMvp->projection), mvp(projection * view * this->model)
	{
	}
public:
	const glm::mat4 model;
	const glm::mat4& view;
	const glm::mat4& projection;
	const glm::mat4 mvp;

	inline static MVPMatrixPtr Make(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	inline static MVPMatrixPtr Make(const glm::mat4& model, const MVPMatrixPtr& baseMvp);
};

MVPMatrixPtr MVPMatrix::Make(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection)
{
	return MVPMatrixPtr(new MVPMatrix(model, view, projection));
}

MVPMatrixPtr MVPMatrix::Make(const glm::mat4& model, const MVPMatrixPtr& baseMvp)
{
	return MVPMatrixPtr(new MVPMatrix(model, baseMvp));
}