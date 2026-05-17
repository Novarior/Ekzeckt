#include "mymath.hpp"
const double mmath::randZeroToOne() { return rand() / (RAND_MAX + 1.); }

// precent to X
template <typename T>
T mmath::p2pX(T _percent, T _size) {
	return floor(static_cast<float>(_size) * (_percent / 100.f));
}

// Для корректной работы с погрешностью, ограничиваем значение в пределах [-1,// 1]
const float mmath::normalize(float value) {
	value = std::fmin(1.0f, std::fmax(-1.0f, value));
	return (value + 1.0f) * 127.f; // Преобразуем значение из диапазона [-1, 1] в [0, 255]
}
const double mmath::normalize(double value) {
	value = std::fmin(1.0f, std::fmax(-1.0f, value));
	return (value + 1.0f) * 127.f; // Преобразуем значение из диапазона [-1, 1] в [0, 255]
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

const double mmath::Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput) {
	return minOutput + (r_value - minInput) * (maxOutput - minOutput) / (maxInput - minInput);
}
