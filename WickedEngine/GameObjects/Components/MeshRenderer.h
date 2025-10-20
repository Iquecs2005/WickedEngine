#pragma once

#include <iostream>
#include "Renderer.h"
#include "../../Geometry/Shape.h"
#include "../../Rendering/Material.h"
#include "../../General/Color.h"

class MeshRenderer : public Renderer
{
public:
	ShapePtr mesh;
	ColorPtr color;
	MaterialPtr material;

	MeshRenderer(GameObject* gameObject);
	~MeshRenderer() {};
	void Draw(const MVPMatrixPtr mvp) override;
	inline void AttachMaterial(MaterialPtr material);
};

void MeshRenderer::AttachMaterial(MaterialPtr material) 
{
	this->material = material;
}