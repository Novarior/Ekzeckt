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
	return (value + 1.0f) * 127.5f; // Преобразуем значение из диапазона [-1, 1] в [0, 255]
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

		  //////////////////////
		 /// INTERPOLATIONS ///
		//////////////////////

static double mmath::interpolation::LinInter(double t, double a, double b) {
	return a + t * (b - a);
}

static double mmath::interpolation::CosInter(double t, double a, double b) {
	double ft = t * M_PI;
	double f = (1 - cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

static double mmath::interpolation::CubicInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}
static double mmath::interpolation::QuinticInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	double t5 = t3 * t2;
	double t4 = t2 * t2;
	return a * (1 - 6 * t5 + 15 * t4 - 10 * t3) + b * (6 * t5 - 15 * t4 + 10 * t3);
}

static double mmath::interpolation::QuarticInter(double t, double a, double b) {
	double t2 = t * t;
	double t4 = t2 * t2;
	return a * (1 - t4) + b * t4;
}

static double mmath::interpolation::QuadraticInter(double t, double a, double b) {
	return a * (1 - t) * (1 - t) + b * t * t;
}

static double mmath::interpolation::HermiteInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}
