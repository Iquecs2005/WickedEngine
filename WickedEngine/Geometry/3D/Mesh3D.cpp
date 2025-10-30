#include "Mesh3D.h"

#ifdef _WIN32

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#elif __APPLE__

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

#endif

Mesh3D::Mesh3D(const std::vector<Vertex3D>& vertexData, const std::vector<unsigned int>& inc) :
	nVertices(vertexData.size()), nTriangles(inc.size() / 3), shapeBufferIds(nBuffers)
{
	glGenVertexArrays(nVaos, &m_vao);
	glGenBuffers(nBuffers, shapeBufferIds.data());
	glBindVertexArray(m_vao);

	//Vertex Data buffer
	glBindBuffer(GL_ARRAY_BUFFER, shapeBufferIds[vertexDataBufferIndex]);
	glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(Vertex3D), vertexData.data(), GL_STATIC_DRAW);

	//Position attribute
	glVertexAttribPointer(positionAttributeIndex, positionDimensions, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)positionOffset);
	glEnableVertexAttribArray(positionAttributeIndex);

	//Normal attribute
	glVertexAttribPointer(normalAttributeIndex, normalDimensions, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)normalOffset);
	glEnableVertexAttribArray(normalAttributeIndex);

	//Tangent attribute
	glVertexAttribPointer(tangentAttributeIndex, tangentDimensions, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)tangentOffset);
	glEnableVertexAttribArray(tangentAttributeIndex);

	//Texture attribute
	glVertexAttribPointer(textureAttributeIndex, textureDimensions, GL_FLOAT, GL_FALSE, sizeof(Vertex3D), (void*)textureOffset);
	glEnableVertexAttribArray(textureAttributeIndex);

	//Incidence Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shapeBufferIds[incidenceBufferIndex]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * nTriangles * sizeof(GLuint), inc.data(), GL_STATIC_DRAW);
}

Mesh3D::~Mesh3D()
{
	glDeleteVertexArrays(nVaos, &m_vao);
	glDeleteBuffers(nBuffers, shapeBufferIds.data());
}

void Mesh3D::Draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, 3 * nTriangles, GL_UNSIGNED_INT, 0);
}