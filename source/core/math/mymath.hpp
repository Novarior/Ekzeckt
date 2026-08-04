#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP
#define _USE_MATH_DEFINES
#include <random>
#include <math.h>
namespace mmath {
#define M_2PI	6.28318530717958647692	// 2*pi

// interpolations
namespace interpolation {

//////////////////////
/// INTERPOLATIONS ///
//////////////////////

static double LinInter(double t, double a, double b) {
	return a + t * (b - a);
}

static double CosInter(double t, double a, double b) {
	double ft = t * M_PI;
	double f = (1 - cos(ft)) * 0.5;
	return a * (1 - f) + b * f;
}

static double CubicInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}

static double QuinticInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	double t5 = t3 * t2;
	double t4 = t2 * t2;
	return a * (1 - 6 * t5 + 15 * t4 - 10 * t3) + b * (6 * t5 - 15 * t4 + 10 * t3);
}

static double QuarticInter(double t, double a, double b) {
	double t2 = t * t;
	double t4 = t2 * t2;
	return a * (1 - t4) + b * t4;
}

static double QuadraticInter(double t, double a, double b) {
	return a * (1 - t) * (1 - t) + b * t * t;
}

static double HermiteInter(double t, double a, double b) {
	double t2 = t * t;
	double t3 = t2 * t;
	return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}

}; // namespace interpolation

const double randZeroToOne();

static inline uint64_t splitmix64(uint64_t x) {
	// SplitMix64 — small, fast hash
	x += 0x9e3779b97f4a7c15ULL;
	x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
	x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
	return x ^ (x >> 31);
}

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

template <typename _val>
inline _val calcCharSize(_val _rx, _val _ry, _val _m = 60) {
	return static_cast<_val>((_rx + _ry) / _m);
}

template<typename _val>
inline _val clamp(const _val& value, const _val& lo, const _val& hi) {
	return (value < lo) ? lo : (value > hi ? hi : value);
}

template <typename _val>
_val randIntFromToNum(_val _min, _val _max) {
	return _min + (rand() / (RAND_MAX / (_max - _min)));
}

template <typename _val>
inline _val p2pX(_val _percent, _val _size) {
	return (_val)(floor(((_size) * (_percent / 100.f))));
}
}; // namespace mmath

#endif // CPP_MATH_CORE_HPP