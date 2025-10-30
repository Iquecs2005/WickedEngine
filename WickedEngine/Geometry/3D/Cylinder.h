#include <memory>

class Cylinder;
using CylinderPtr = std::shared_ptr<Cylinder>;

#pragma once

#include "GridMesh.h"
#include "Mesh3D.h"

class Cylinder : public Mesh3D
{
public:
	static inline CylinderPtr Make(unsigned int nstack = 64);
protected:
	Cylinder(unsigned int nstack);
private:
	GridMeshPtr grid;

	GridMeshPtr CreateGrid(unsigned int nstack);
	std::vector<Vertex3D> GenerateLidVertices(unsigned int nVertices, float yValue);
	std::vector<unsigned int> GenerateLidIncidence(unsigned int nVertices, unsigned int offset, bool bottomLid);
	std::vector<Vertex3D> GetVerticeList(unsigned int nstack);
	std::vector<unsigned int> GetIncidenceList(unsigned int nstack);
};

inline CylinderPtr Cylinder::Make(unsigned int nstack)
{
	return CylinderPtr(new Cylinder(nstack));
}