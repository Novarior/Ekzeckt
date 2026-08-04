#ifndef CPP_MATH_PERLIN_NOISE_HPP
#define CPP_MATH_PERLIN_NOISE_HPP

#include "../mymath.hpp"
#include "Noise_data.h"

class PerlinNoise {
public:
	PerlinNoise(NoiceData* _data);
	~PerlinNoise() {}

	double Noise(double x_cord, double y_cord, double minValue = -1, double maxValue = 1.0);

private:
	NoiceData* data;
	int p[512]; // Permutation table
};
#endif //