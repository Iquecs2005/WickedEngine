#define _USE_MATH_DEFINES
#include "Cylinder.h"
#include <cmath>
#include <iostream>

Cylinder::Cylinder(unsigned int nstack)
	: Mesh3D(GetVerticeList(nstack), GetIncidenceList(nstack))
{

}

GridMeshPtr Cylinder::CreateGrid(unsigned int nstack)
{
	grid = GridMesh::Make(nstack, 2);

	float currentAngle = 0;
	float angleStep = (float)(2 * M_PI / (nstack - 1));

	std::vector<Vertex3D>& vertexDataList = grid->GetVerticeList();
	for (unsigned int i = 0; i < nstack * 2; i += 2)
	{
		Vertex3D& vertexData1 = vertexDataList[i];
		Vertex3D& vertexData2 = vertexDataList[i+1];

		float x = sin(currentAngle);
		float z = cos(currentAngle);

		vertexData1.x = x;
		vertexData1.y = -1;
		vertexData1.z = z;

		vertexData2.x = x;
		vertexData2.y = 1;
		vertexData2.z = z;

		vertexData1.nx = vertexData1.x;
		vertexData1.ny = 0;
		vertexData1.nz = vertexData1.z;

		vertexData2.nx = vertexData2.x;
		vertexData2.ny = 0;
		vertexData2.nz = vertexData2.z;

		vertexData1.tx = -vertexData1.nz;
		vertexData1.ty = 0;
		vertexData1.tz = vertexData1.nx;

		vertexData2.tx = -vertexData2.nz;
		vertexData2.ty = 0;
		vertexData2.tz = vertexData2.nx;

		currentAngle += angleStep;
	}

	return grid;
}

std::vector<Vertex3D> Cylinder::GenerateLidVertices(unsigned int nVertices, float yValue)
{
	std::vector<Vertex3D> vertexVector(nVertices);

	float currentAngle = 0;
	float angleStep = (float)(2 * M_PI / (nVertices - 1));

	Vertex3D& centerVector = vertexVector[0];

	centerVector.x = 0;
	centerVector.y = yValue;
	centerVector.z = 0;

	centerVector.nx = 0;
	if (yValue > 0)
		centerVector.ny = 1;
	else
		centerVector.ny = -1;
	centerVector.nz = 0;

	centerVector.tx = 1;
	centerVector.ty = 0;
	centerVector.tz = 0;

	centerVector.s = 0.5f;
	centerVector.t = 0.5f;

	for (unsigned int i = 1; i < nVertices; i++)
	{
		Vertex3D& currentVertice = vertexVector[i];

		float cossine = cosf(currentAngle);
		float sine = sinf(currentAngle);
		
		currentVertice.x = sine;
		currentVertice.y = yValue;
		currentVertice.z = cossine;

		currentVertice.nx = 0;
		currentVertice.ny = yValue * 2;
		currentVertice.nz = 0;

		currentVertice.tx = 1;
		currentVertice.ty = 0;
		currentVertice.tz = 0;

		currentVertice.s = 0.5f + 0.5f * cossine;
		currentVertice.t = 0.5f + 0.5f * sine;

		currentAngle += angleStep;
	}

	return vertexVector;
}

std::vector<unsigned int> Cylinder::GenerateLidIncidence(unsigned int nVertices, unsigned int offset, bool bottomLid)
{
	const unsigned int nTriangles = nVertices - 1;
	std::vector<unsigned int> incidenceVector(nTriangles * 3);
	unsigned int currentVertice = 1;

	for (unsigned int i = 0; i < nTriangles; i++)
	{
		if (!bottomLid)
		{
			incidenceVector[i * 3] = offset;
			incidenceVector[i * 3 + 1] = offset + currentVertice++;
			if (currentVertice >= nVertices) currentVertice = 1;
			incidenceVector[i * 3 + 2] = offset + currentVertice;
		}
		else
		{
			incidenceVector[i * 3 + 2] = offset;
			incidenceVector[i * 3 + 1] = offset + currentVertice++;
			if (currentVertice >= nVertices) currentVertice = 1;
			incidenceVector[i * 3] = offset + currentVertice;
		}
	}

	return incidenceVector;
}

std::vector<Vertex3D> Cylinder::GetVerticeList(unsigned int nstack)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack);

	std::vector<Vertex3D> completeVertexData;
	completeVertexData.reserve(grid->nVertices + nstack * 2);
	
	std::vector<Vertex3D> tempList;
	
	tempList = grid->GetVerticeList();
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());
	
	tempList = GenerateLidVertices(nstack, 1);
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());
	
	tempList = GenerateLidVertices(nstack, -1);
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());

	return completeVertexData;
}

std::vector<unsigned int> Cylinder::GetIncidenceList(unsigned int nstack)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack);

	std::vector<unsigned int> completeIncidenceList;
	completeIncidenceList.reserve(grid->nTriangles * 3 + 6 * (nstack - 1));

	std::vector<unsigned int> tempList;
	
	tempList = grid->GetIncidenceList();
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());
	
	tempList = GenerateLidIncidence(nstack, grid->nVertices, false);
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());
	
	tempList = GenerateLidIncidence(nstack, grid->nVertices + nstack, true);
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());

	return completeIncidenceList;
}