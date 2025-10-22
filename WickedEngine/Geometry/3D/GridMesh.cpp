#include "GridMesh.h"

GridMesh::GridMesh(unsigned int nX, unsigned int nY)
	: nVerticesX(nX), nVerticesY(nY), nVertices(nX * nY), 
	nTriangles(2 * (nX - 1) * (nX - 1))
{

	for (int i = 0; i < nVertices; i++)
	{
		
	}
}