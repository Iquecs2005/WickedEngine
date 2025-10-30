#include "GridMesh.h"

GridMesh::GridMesh(unsigned int nX, unsigned int nY)
	: nVerticesX(nX), nVerticesY(nY), nVertices(nX * nY), 
	nTriangles(2 * (nX - 1) * (nY - 1)), verticeList(nVertices), incidenceList(nTriangles * 3)
{
	float deltaX = 1.0f / (nVerticesX - 1);
	float deltaY = 1.0f / (nVerticesY - 1); 

	unsigned int nv = 0;
	for (unsigned int i = 0; i < nVerticesX; i++)
	{
		for (unsigned int j = 0; j < nVerticesY; j++)
		{
			verticeList[nv++] = Vertex3D( Vector3(deltaX * i, deltaY * j, 0),
										  Vector3(0, 0, 1),
										  Vector3(1, 0, 0),
										  Vector2(deltaX * i, deltaY * j));
		}
	}

	unsigned int ni = 0;
	for (unsigned int i = 0; i < nVerticesX - 1; i++)
	{
		for (unsigned int j = 0; j < nVerticesY - 1; j++)
		{
			incidenceList[ni++] = calculateIndex(i, j, nY);
			incidenceList[ni++] = calculateIndex(i+1, j, nY);
			incidenceList[ni++] = calculateIndex(i+1, j+1, nY);

			incidenceList[ni++] = calculateIndex(i, j, nY);
			incidenceList[ni++] = calculateIndex(i+1, j+1, nY);
			incidenceList[ni++] = calculateIndex(i, j+1, nY);
		}
	}
}