#define _USE_MATH_DEFINES
#include "Cilinder.h"
#include <cmath>
#include <iostream>

Cilinder::Cilinder(unsigned int nstack)
	: Mesh3D(GetVerticeList(nstack), GetIncidenceList(nstack))
{

}

GridMeshPtr Cilinder::CreateGrid(unsigned int nstack)
{
	grid = GridMesh::Make(nstack, 2);

	float currentAngle = 0;
	float angleStep = (float)(2 * M_PI / (nstack - 1));

	std::vector<VertexData3D>& vertexDataList = grid->GetVerticeList();
	for (unsigned int i = 0; i < nstack * 2; i += 2)
	{
		VertexData3D& vertexData1 = vertexDataList[i];
		VertexData3D& vertexData2 = vertexDataList[i+1];

		float x = sin(currentAngle);
		float z = cos(currentAngle);

		vertexData1.x = x;
		vertexData2.x = x;
		vertexData1.y = -0.5f;
		vertexData2.y = 0.5f;
		vertexData1.z = z;
		vertexData2.z = z;

		vertexData1.nx = vertexData1.x;
		vertexData2.nx = vertexData2.x;
		vertexData1.ny = 0;
		vertexData2.ny = 0;
		vertexData1.nz = vertexData1.z;
		vertexData2.nz = vertexData2.z;

		currentAngle += angleStep;
	}

	return grid;
}

std::vector<VertexData3D> Cilinder::GenerateLidVertices(unsigned int nVertices, float yValue)
{
	std::vector<VertexData3D> vertexVector(nVertices);

	float currentAngle = 0;
	float angleStep = (float)(2 * M_PI / (nVertices - 1));

	VertexData3D& centerVector = vertexVector[0];

	centerVector.x = 0;
	centerVector.y = yValue;
	centerVector.z = 0;

	centerVector.nx = 0;
	if (yValue > 0)
		centerVector.ny = 1;
	else
		centerVector.ny = -1;
	centerVector.nz = 0;

	centerVector.s = 0.5f;
	centerVector.t = 0.5f;

	for (unsigned int i = 1; i < nVertices; i++)
	{
		VertexData3D& currentVertice = vertexVector[i];

		float cossine = cosf(currentAngle);
		float sine = sinf(currentAngle);
		
		centerVector.x = sine;
		centerVector.y = yValue;
		centerVector.z = cossine;

		centerVector.nx = sine;
		centerVector.ny = 0;
		centerVector.nz = cossine;

		centerVector.s = 0.5f + 0.5f * cossine;
		centerVector.t = 0.5f + 0.5f * sine;

		currentAngle += angleStep;
	}

	return vertexVector;
}

std::vector<unsigned int> Cilinder::GenerateLidIncidence(unsigned int nVertices, unsigned int offset)
{
	const unsigned int nTriangles = nVertices - 1;
	std::vector<unsigned int> incidenceVector(nTriangles * 3);
	unsigned int currentVertice = 1;

	for (unsigned int i = 0; i < nTriangles; i++)
	{
		incidenceVector[i * 3] = offset;
		incidenceVector[i * 3 + 1] = offset + currentVertice++;
		if (currentVertice >= nVertices) currentVertice = 1;
		incidenceVector[i * 3 + 2] = offset + currentVertice;
	}

	return incidenceVector;
}

std::vector<VertexData3D> Cilinder::GetVerticeList(unsigned int nstack)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack);

	std::vector<VertexData3D> completeVertexData;
	completeVertexData.reserve(grid->nVertices + (nstack + 1) * 2);
	
	std::vector<VertexData3D> tempList;
	std::cout << "Total vertices: " << grid->nVertices + 5 * 2 << std::endl;
	
	tempList = grid->GetVerticeList();
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());
	std::cout << "Total vertices: " << completeVertexData.size() << std::endl;
	
	tempList = GenerateLidVertices(5, 0.5);
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());
	std::cout << "Total vertices: " << completeVertexData.size() << std::endl;
	
	tempList = GenerateLidVertices(5, -0.5);
	completeVertexData.insert(completeVertexData.end(), tempList.begin(), tempList.end());
	std::cout << "Total vertices: " << completeVertexData.size() << std::endl;

	std::cout << "Vertices:" << std::endl;
	for (auto a : completeVertexData)
	{
		std::cout << a.x << " " << a.y << " " << a.z << std::endl;
	}

	return completeVertexData;
}

std::vector<unsigned int> Cilinder::GetIncidenceList(unsigned int nstack)
{
	if (grid == nullptr)
		grid = CreateGrid(nstack);

	std::vector<unsigned int> completeIncidenceList;
	completeIncidenceList.reserve(grid->nTriangles * 3 + 6 * nstack);

	std::vector<unsigned int> tempList;
	std::cout << "Total Incidence: " << grid->nTriangles * 3 + 6 * nstack << std::endl;
	
	tempList = grid->GetIncidenceList();
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());
	std::cout << "Total Incidence: " << completeIncidenceList.size() << std::endl;
	
	tempList = GenerateLidIncidence(nstack + 1, grid->nVertices);
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());
	std::cout << "Total Incidence: " << completeIncidenceList.size() << std::endl;
	
	tempList = GenerateLidIncidence(nstack + 1, grid->nVertices + nstack + 1);
	completeIncidenceList.insert(completeIncidenceList.end(), tempList.begin(), tempList.end());
	std::cout << "Total Incidence: " << completeIncidenceList.size() << std::endl;

	std::cout << "Incidence:" << std::endl;
	int i = 0;
	for (auto a : completeIncidenceList)
	{
		std::cout << a << " ";
		i++;
		if (i == 3)
		{
			std::cout << std::endl;
			i = 0;
		}
	}

	return completeIncidenceList;
}