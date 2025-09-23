#pragma once

#include <iostream>
#include "Renderer.h"
#include "../../Geometry/Shape.h"
#include "../../Rendering/Material.h"

class MeshRenderer : public Renderer
{
public:
	ShapePtr mesh;
	MaterialPtr material;

	MeshRenderer(GameObject* gameObject);
	~MeshRenderer() {};
	void Draw(glm::mat4x4 mvp) override;
	inline void AttachMaterial(MaterialPtr material);
};

void MeshRenderer::AttachMaterial(MaterialPtr material) 
{
	this->material = material;
}