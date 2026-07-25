#ifndef CPP_MATH_PERLIN_NOISE_HPP
#define CPP_MATH_PERLIN_NOISE_HPP

#include "../mymath.hpp"
class PerlinNoise {
public:
	PerlinNoise(unsigned int seed = std::random_device{}());
	~PerlinNoise() {}

	double Noise(double x_cord, double y_cord, double minValue = -1, double maxValue = 1.0, bool fastmode = false);

private:
	int p[512]; // Permutation table
};
#endif //