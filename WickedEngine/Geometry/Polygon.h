#include <memory>

class Polygon;
struct VertexData;
using PolygonPtr = std::shared_ptr<Polygon>;

#ifndef POLYGON_H
#define POLYGON_H

#include "shape.h"
#include <vector>

struct VertexData
{
	float x, y;
	unsigned char r, g, b;
};

class Polygon : public Shape
{
	unsigned int m_vao;
	const unsigned int nVertices;
	const unsigned int nTriangles;
	std::vector<unsigned int> shapeBufferIds;

	static const unsigned int nVaos = 1;
	static const unsigned int nBuffers = 2;
	static const unsigned int vertexDataBufferIndex = 0;
	static const unsigned int positionAttributeIndex = 0;
	static const unsigned int positionDimensions = 2;
	static const unsigned int positionOffset = 0;
	static const unsigned int colorAttributeIndex = 1;
	static const unsigned int colorDimensions = 3;
	static const unsigned int colorOffset = sizeof(float) * positionDimensions;
	static const unsigned int incidenceBufferIndex = 1;

protected:
	Polygon(const std::vector<VertexData>& vertexData, const std::vector<unsigned int>& inc);
public:
	static inline PolygonPtr Make(const std::vector<VertexData>& vertexData, const std::vector<unsigned int>& inc);
	virtual ~Polygon();
	virtual void Draw();
};

inline PolygonPtr Polygon::Make(const std::vector<VertexData>& vertexData, const std::vector<unsigned int>& inc)
{
	return PolygonPtr(new Polygon(vertexData, inc));
}

#endif