#include <memory>

class Triangle;
using TrianglePtr = std::shared_ptr<Triangle>;

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Polygon.h"

class Triangle : public Polygon
{
protected:
	Triangle() : Polygon({ { 1, 0, 1, 0 },
						   {-1, 0, 0, 0 },
						   { 0, 1, 0.5f, 1 } }, { 2, 1, 0 }) {};
public:
	static inline TrianglePtr Make();
};

inline TrianglePtr Triangle::Make()
{
	return TrianglePtr(new Triangle());
}

#endif