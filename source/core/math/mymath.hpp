#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP
#include <cmath>
#include <random>

namespace mmath {
constexpr double M_PI = 3.14159265358979;
constexpr double M_PI2 = 6.28318530717959;
constexpr double M_PI_2 = 1.5707963267949;

// interpolations
namespace interpolation {

		  //////////////////////
		 /// INTERPOLATIONS ///
		//////////////////////

static double  LinInter(double t, double a, double b) {
	return a + t * (b - a);
}

static double  CosInter(double t, double a, double b) {
	double ft = t * M_PI;
	double f = (1 - cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

static double  CubicInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}

static double  QuinticInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	double t5 = t3 * t2;
	double t4 = t2 * t2;
	return a * (1 - 6 * t5 + 15 * t4 - 10 * t3) + b * (6 * t5 - 15 * t4 + 10 * t3);
}

static double  QuarticInter(double t, double a, double b) {
	double t2 = t * t;
	double t4 = t2 * t2;
	return a * (1 - t4) + b * t4;
}

static double  QuadraticInter(double t, double a, double b) {
	return a * (1 - t) * (1 - t) + b * t * t;
}

static double  HermiteInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}

}; // namespace interpolation

const double randZeroToOne();

template <typename T>
T randIntFromToNum(T _min, T _max) {
	return _min + (rand() / (RAND_MAX / (_max - _min)));
}

template <typename T>
T p2pX(T _percent, T _size);

const float normalize(float value);
const double normalize(double value);

// fade function
static const double Fade(double t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

// gradient
double Gradient_v4(int hash, double x, double y);
double Gradient_v16(int hash, double x, double y);

const double Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput);

template <typename T>
T  calcCharSize(T _rx, T _ry, T _m = 60) {
	return static_cast<unsigned int>((_rx + _ry) / _m);
}
}; // namespace mmath

#endif // CPP_MATH_CORE_HPP