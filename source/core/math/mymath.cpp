#include "mymath.hpp"
const double mmath::randZeroToOne() { return rand() / (RAND_MAX + 1.); }

// map [-1, 1] -> [0, 255]
const float mmath::normalize(float value) {
	value = std::fmin(1.0f, std::fmax(-1.0f, value));
	return (value + 1.0f) * 127.5f;
}

// map [-1, 1] -> [0, 255]
const double mmath::normalize(double value) {
	value = std::fmin(1.0, std::fmax(-1.0, value));
	return (value + 1.0) * 127.5;
}

const double mmath::Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput) {
	if (maxInput == minInput) return minOutput; // def from div by zero
	return minOutput + (r_value - minInput) * (maxOutput - minOutput) / (maxInput - minInput);
}

double mmath::Gradient_v16(int hash, double x, double y) {
	int h = hash & 15;
	double grad = 1 + (h & 7);
	if (h & 8)
		grad = -grad;
	return (grad * x + grad * y);
}

double mmath::Gradient_v4(int hash, double x, double y) {
	int h = hash & 3; // Take the first 2 bits of the hash
	double u = h < 2 ? x : y;
	double v = h < 2 ? y : x;
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}