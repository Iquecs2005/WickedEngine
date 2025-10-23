#include "GridMesh.h"

GridMesh::GridMesh(unsigned int nX, unsigned int nY)
	: nVerticesX(nX), nVerticesY(nY), nVertices(nX * nY), 
	nTriangles(2 * (nX - 1) * (nX - 1)), verticeList(nVertices), incidenceList(nTriangles * 3)
{
	float deltaX = 1.0f / nVerticesX;
	float deltaY = 1.0f / nVerticesX;

	unsigned int nv = 0;
	for (int i = 0; i < nVerticesX; i++)
	{
		for (int j = 0; j < nVerticesY; j++)
		{
			verticeList[nv++] = { deltaX * i, deltaY * j, 0, 0, 0, 1, deltaX * i, deltaY * j };
		}
	}

	unsigned int ni = 0;
	for (int i = 0; i < nVerticesX - 1; i++)
	{
		for (int j = 0; j < nVerticesY - 1; j++)
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