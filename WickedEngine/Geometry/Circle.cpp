#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include "Circle.h"

std::vector<VertexData> Circle::GenerateVertex(unsigned int nVertices)
{
	std::vector<VertexData> vertexVector(nVertices);

	float currentAngle = 0;
	float angleStep = 2 * M_PI / (nVertices - 1);

	vertexVector[0] = { 0, 0, 0.5, 0.5 };
	for (int i = 1; i < nVertices; i++)
	{
		float cossine = cosf(currentAngle);
		float sine = sinf(currentAngle);

		vertexVector[i] = { cossine, sine, 0.5f + 0.5f * cossine, 0.5f + 0.5f * sine };
		currentAngle += angleStep;
	}

	return vertexVector;
}

std::vector<unsigned int> Circle::GenerateIncidence(unsigned int nVertices)
{
	const unsigned int nTriangles = nVertices - 1;
	std::vector<unsigned int> incidenceVector(nTriangles * 3);
	int currentVertice = 1;

	for (int i = 0; i < nTriangles; i++)
	{
		incidenceVector[i * 3] = 0;
		incidenceVector[i * 3 + 1] = currentVertice++;
		if (currentVertice >= nVertices) currentVertice = 1;
		incidenceVector[i * 3 + 2] = currentVertice;
	}

	return incidenceVector;
}