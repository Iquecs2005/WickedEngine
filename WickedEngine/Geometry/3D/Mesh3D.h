#include <memory>

class Mesh3D;
using Mesh3Dptr = std::shared_ptr<Mesh3D>;

#pragma once

#include "../Shape.h"
#include <vector>

struct VertexData3D
{
	float x, y, z;
	float nx, ny, nz;
	float s, t;
};

class Mesh3D : public Shape
{
	unsigned int m_vao;
	const unsigned int nVertices;
	const unsigned int nTriangles;
	std::vector<unsigned int> shapeBufferIds;

	static const unsigned int nVaos = 1;
	static const unsigned int nBuffers = 2;
	static const unsigned int vertexDataBufferIndex = 0;
	static const unsigned int positionAttributeIndex = 0;
	static const unsigned int positionDimensions = 3;
	static const unsigned int positionOffset = 0;
	static const unsigned int normalAttributeIndex = 1;
	static const unsigned int normalDimensions = 3;
	static const unsigned int normalOffset = sizeof(float) * positionDimensions;
	static const unsigned int textureAttributeIndex = 3;
	static const unsigned int textureDimensions = 2;
	static const unsigned int textureOffset = sizeof(float) * normalDimensions + normalOffset;
	static const unsigned int incidenceBufferIndex = 1;

protected:
	Mesh3D(const std::vector<VertexData3D>& vertexData, const std::vector<unsigned int>& inc);
public:
	static inline Mesh3Dptr Make(const std::vector<VertexData3D>& vertexData, const std::vector<unsigned int>& inc);

	virtual ~Mesh3D();
	virtual void Draw();
};

inline Mesh3Dptr Mesh3D::Make(const std::vector<VertexData3D>& vertexData, const std::vector<unsigned int>& inc)
{
	return Mesh3Dptr(new Mesh3D(vertexData, inc));
}

