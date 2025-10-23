#include "GridGeometry.h"

GridGeometry::GridGeometry(unsigned int nx, unsigned int ny)
	: Mesh3D(GetVerticeList(nx, ny), GetIncidenceList(nx, ny))
{
	
}