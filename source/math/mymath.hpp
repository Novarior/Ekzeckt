#ifndef CPP_MATH_CORE_HPP
#define CPP_MATH_CORE_HPP

#include "../core/header.h"
namespace mmath {
enum eSmoothMode { SMOOTH_MODE = 0, FAST_MODE = 1 };

struct noiceData {
  unsigned int mapSizeX = 0;
  unsigned int mapSizeY = 0;
  unsigned int mapSizeZ = 0;
  float gridSize = 0;
  unsigned long seed = 0;
  int offsetSeed = 0xffffffff;
  float chanceToSpawnTree = 0.0f;
  unsigned octaves = 0;
  double frequency = 0;
  float amplifire = 0;
  float persistence = 0;
  unsigned int RenderWindowX = 0;
  unsigned int RenderWindowY = 0;
  unsigned int smoothMode = 0;
  bool fastMode = false;
};

const double randZeroToOne();

const double randDoubleFromToNum(double Min_val, double Max_val);
const int randIntFromToNum(int Min_val, int Max_val);

/// @brief return float from present of resolution, number, ect
/// @param perc precent from 0 to 100
/// @param vm
/// @return float
const float p2pX(const float perc, const sf::VideoMode &vm);
const float p2pX(const float perc, const unsigned int &i);
const float p2pX(const float perc, const float &i);

const float normalize(float value);

// fade function
static const double Fade(double t) {
  return t * t * t * (t * (t * 6 - 15) + 10);
}
// interpolations
namespace interpolation {
// Linear interpolation
static double LinInter(double t, double a, double b) { return a + t * (b - a); }

// Cosine interpolation
static double CosInter(double t, double a, double b) {
  double ft = t * M_PI;
  double f = (1 - cos(ft)) * 0.5;
  return a * (1 - f) + b * f;
}

// Cubic interpolation (simplified Hermite spline)
static double CubicInter(double t, double a, double b) {
  double t2 = t * t;
  double t3 = t2 * t;
  return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}

// Quintic interpolation
static double QuinticInter(double t, double a, double b) {
  double t2 = t * t;
  double t3 = t2 * t;
  double t5 = t3 * t2;
  double t4 = t2 * t2;
  return a * (1 - 6 * t5 + 15 * t4 - 10 * t3) +
         b * (6 * t5 - 15 * t4 + 10 * t3);
}

// Quartic interpolation (adjusted to follow proper smoothstep logic)
static double QuarticInter(double t, double a, double b) {
  double t2 = t * t;
  double t4 = t2 * t2;
  return a * (1 - t4) + b * t4;
}

// Quadratic interpolation
static double QuadraticInter(double t, double a, double b) {
  return a * (1 - t) * (1 - t) + b * t * t;
}

// Hermite interpolation (cubic Hermite spline)
static double HermiteInter(double t, double a, double b) {
  double t2 = t * t;
  double t3 = t2 * t;
  return a * (2 * t3 - 3 * t2 + 1) + b * (3 * t2 - 2 * t3);
}
}; // namespace interpolation

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
const double Rescale(double r_value, double minInput, double maxInput,
                     double minOutput, double maxOutput);

const unsigned int calcCharSize(const sf::VideoMode &vm,
                                const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2u resolution,
                                const unsigned modifier = 60);
const unsigned int calcCharSize(const sf::Vector2f resolution,
                                const unsigned modifier = 60);
}; // namespace mmath

#endif // CPP_MATH_CORE_HPP