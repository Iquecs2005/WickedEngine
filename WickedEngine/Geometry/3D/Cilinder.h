#include <memory>

class Cilinder;
using CilinderPtr = std::shared_ptr<Cilinder>;

#pragma once

#include "GridMesh.h"
#include "Mesh3D.h"

class Cilinder : public Mesh3D
{
public:
	static inline CilinderPtr Make(unsigned int nstack = 4);
protected:
	Cilinder(unsigned int nstack);
private:
	GridMeshPtr grid;

	GridMeshPtr CreateGrid(unsigned int nstack);
	std::vector<VertexData3D> GenerateLidVertices(unsigned int nVertices, float yValue);
	std::vector<unsigned int> GenerateLidIncidence(unsigned int nVertices, unsigned int offset);
	std::vector<VertexData3D> GetVerticeList(unsigned int nstack);
	std::vector<unsigned int> GetIncidenceList(unsigned int nstack);
};

inline CilinderPtr Cilinder::Make(unsigned int nstack)
{
	return CilinderPtr(new Cilinder(nstack));
}