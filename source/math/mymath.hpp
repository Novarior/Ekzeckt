#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP
#include <cmath>

namespace mmath {
constexpr double M_PI = 3.14159265358979;
constexpr double M_PI2 = 6.28318530717959;
constexpr double M_PI_2 = 1.5707963267949;

// interpolations
namespace interpolation {
static double LinInter(double t, double a, double b);
static double CosInter(double t, double a, double b);
static double CubicInter(double t, double a, double b);
static double QuinticInter(double t, double a, double b);
static double QuarticInter(double t, double a, double b);
static double QuadraticInter(double t, double a, double b);
static double HermiteInter(double t, double a, double b);
}; // namespace interpolation

const double randZeroToOne();

template <typename T>
T randIntFromToNum(T _min, T _max) {
	return Min_val + (rand() / (RAND_MAX / (_max - _min)));
}

template <typename T>
T p2pX(T _percent, T _size);

const float normalize(float value);

// fade function
static const double Fade(double t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

// gradient
double Gradient_v4(int hash, double x, double y);
double Gradient_v16(int hash, double x, double y);

/// @brief rescale value from input to output
/// @param r_value rescalable value
/// @param minInput min value from input
/// @param maxInput max value from input
/// @param minOutput min value from output
/// @param maxOutput max value from output
/// @return rescaled value
const double Rescale(double r_value, double minInput, double maxInput, double minOutput, double maxOutput);

template <typename T>
T  calcCharSize(T _rx, T _ry, T _m = 60) {
	return static_cast<unsigned int>((_rx + _ry) / _m);
}
}; // namespace mmath

#endif // CPP_MATH_CORE_HPP