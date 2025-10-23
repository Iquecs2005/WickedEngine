#include <memory>

class Arcball;
using ArcballPtr = std::shared_ptr<Arcball>;

#pragma once

#include <glm/glm.hpp>

class Arcball
{
public:
	float distance;

	static inline ArcballPtr Make(float distance);
	void InitMouseMotion(float x, float y);
	void AccumulateMouseMotion(float x, float y);
	const glm::mat4& GetMatrix() const;
protected:
	Arcball(float distance);
private:
	float x0, y0;
	glm::mat4 matrix;

	static void Map(int width, int height, float x, float y, float& px, float& py, float& pz);
};

inline ArcballPtr Arcball::Make(float distance)
{
	return ArcballPtr(new Arcball(distance));
}
