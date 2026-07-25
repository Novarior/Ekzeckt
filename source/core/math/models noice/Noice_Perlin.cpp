#include "Noice_Perlin.hpp"

PerlinNoise::PerlinNoise(unsigned int seed ) {
	   // Initialize the permutation vector with the reference values
	for (int i = 0; i < 256; ++i)
		p[i] = i;

	// Shuffle the array with the given seed
	std::mt19937 gen(seed);
	std::shuffle(p, p + 256, gen);

	// Duplicate the permutation vector
	for (int i = 0; i < 256; ++i)
		p[256 + i] = p[i];
}

double PerlinNoise::Noise(double x_cord, double y_cord, double minValue, double maxValue, bool fastmode ) {
	int X = static_cast<int>(floor(x_cord)) & 255;
	int Y = static_cast<int>(floor(y_cord)) & 255;

	x_cord -= floor(x_cord);
	y_cord -= floor(y_cord);

	double u = mmath::Fade(x_cord);
	double v = mmath::Fade(y_cord);

	int A = p[X] + Y;
	int AA = p[A];
	int AB = p[A + 1];
	int B = p[X + 1] + Y;
	int BA = p[B];
	int BB = p[B + 1];

	double res = 0;
	if (fastmode)
		res = mmath::interpolation::QuinticInter(
		v,
		mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AA], x_cord, y_cord), mmath::Gradient_v4(p[BA], x_cord - 1, y_cord)),
		mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AB], x_cord, y_cord - 1), mmath::Gradient_v4(p[BB], x_cord - 1, y_cord - 1)));
	else
		res = mmath::interpolation::QuinticInter(
		v,
		mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AA], x_cord, y_cord), mmath::Gradient_v16(p[BA], x_cord - 1, y_cord)),
		mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AB], x_cord, y_cord - 1), mmath::Gradient_v16(p[BB], x_cord - 1, y_cord - 1)));

	return mmath::normalize(res);
}