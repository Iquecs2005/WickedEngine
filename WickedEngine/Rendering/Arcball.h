#pragma once
class Arcball
{
public:
	Arcball(float distance);
	void InitMouseMotion(float x, float y);
	void AccumulateMouseMotion(float x, float y);
	const float* GetMatrix() const;
private:
	float distance;
	float x0, y0;
	float matrix[16];

	static void Map(int width, int height, float x, float y, float& px, float& py, float& pz);
};

