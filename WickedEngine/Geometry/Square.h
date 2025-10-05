#include <memory>

class Square;
using SquarePtr = std::shared_ptr<Square>;

#pragma once

#include "Polygon.h"

class Square : public Polygon
{
public:
	static inline SquarePtr Make();
protected:
	Square() : Polygon({ {-0.5f, -0.5f, 0, 0 },
						 {-0.5f,  0.5f, 0, 1 },
						 { 0.5f, -0.5f, 1, 0 }, 
						 { 0.5f,  0.5f, 1, 1 } }, { 0, 2, 1, 2, 3, 1}) 
	{
		
	};
};

inline SquarePtr Square::Make()
{
	return SquarePtr(new Square());
}

