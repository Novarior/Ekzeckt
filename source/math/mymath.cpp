#include "mymath.hpp"

const double mmath::randDoubleFromToNum(double Min_val, double Max_val) {
  return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}
const int mmath::randIntFromToNum(int Min_val, int Max_val) {
  return Min_val + (rand() / (RAND_MAX / (Max_val - Min_val)));
}
const double mmath::randZeroToOne() { return rand() / (RAND_MAX + 1.); }

// precent to X
const float mmath::p2pX(const float perc, const sf::VideoMode &vm) {
  return floor(static_cast<float>(vm.size.x) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const unsigned int &i) {
  return floor(static_cast<float>(i) * (perc / 100.f));
}
const float mmath::p2pX(const float perc, const float &i) {
  return floor(static_cast<float>(i) * (perc / 100.f));
}

const float mmath::normalize(float value) {
  // Для корректной работы с погрешностью, ограничиваем значение в пределах [-1,
  // 1]
  value = std::fmin(1.0f, std::fmax(-1.0f, value));

  // Преобразуем значение из диапазона [-1, 1] в [0, 255]
  return (value + 1.0f) * 127.5f;
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

const double mmath::Rescale(double r_value, double minInput, double maxInput,
                            double minOutput, double maxOutput) {
  return minOutput +
         (r_value - minInput) * (maxOutput - minOutput) / (maxInput - minInput);
}

//  Calculates the character size for text using the current resolution and a
//  constant.
///  @brief	sf::VideoMode& vm		The current videomode of the
///  window (resolution).
///  @param		unsigned modifier		Used to modify the
///  character size in a more custom way.
///  @return		unsigned int			The calculated character
///  size value.
const unsigned int mmath::calcCharSize(const sf::VideoMode &vm,
                                       const unsigned modifier) {
  return static_cast<unsigned int>((vm.size.x + vm.size.y) / modifier);
}
//  Calculates the character size for text using the current resolution and a
//  constant.
//  @param		sf::VideoMode& vm		The current videomode of
//  the window (resolution).
//  @param		unsigned modifier		Used to modify the
//  character size in a more custom way.
//  @return		unsigned int			The calculated character
//  size value.
const unsigned int mmath::calcCharSize(const sf::Vector2u resolution,
                                       const unsigned modifier) {
  return static_cast<unsigned int>((resolution.x + resolution.y) / modifier);
}
//  Calculates the character size for text using the current resolution and a
//  constant.
//  @param		sf::VideoMode& vm		The current videomode of
//  the window (resolution).
//  @param		unsigned modifier		Used to modify the
//  character size in a more custom way.
//  @return		unsigned int			The calculated character
//  size value.
const unsigned int mmath::calcCharSize(const sf::Vector2f resolution,
                                       const unsigned modifier) {
  return static_cast<unsigned int>((resolution.x + resolution.y) / modifier);
}