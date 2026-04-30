#ifndef CPP_MATH_SIMPLEX_NOICE_HPP
#define CPP_MATH_SIMPLEX_NOICE_HPP

#include "mymath.hpp"

class SimplexNoise
{
public:
    SimplexNoise();
    ~SimplexNoise();

    float noise(float xin, float yin);

private:
    int fastfloor(float x);
    float dot(int *g, float x, float y);
    float computeNoise(float x, float y, int gi, int grad3[][3]);

    int grad3[12][3] = {{1, 1, 0}, {-1, 1, 0}, {1, -1, 0}, {-1, -1, 0}, {1, 0, 1}, {-1, 0, 1}, {1, 0, -1}, {-1, 0, -1}, {0, 1, 1}, {0, -1, 1}, {0, 1, -1}, {0, -1, -1}};

    int p[512];
    uint8_t perm[512];
};
#endif // CPP_MATH_SIMPLEX_NOICE_HPP