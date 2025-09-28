#include <memory>

class Circle;
using CirclePtr = std::shared_ptr<Circle>;

#ifndef CIRCLE_H
#define CIRCLE_H

#include "Polygon.h"

class Circle : public Polygon
{
protected:
	Circle(unsigned int nVertices) : Polygon(GenerateVertex(nVertices), GenerateIncidence(nVertices)) {};
public:
	static inline CirclePtr Make(unsigned int nVertices);
private:
	std::vector<VertexData> GenerateVertex(unsigned int nVertices);
	std::vector<unsigned int> GenerateIncidence(unsigned int nVertices);
};

inline CirclePtr Circle::Make(unsigned int nVertices = 32)
{
	return CirclePtr(new Circle(nVertices));
}

#endif