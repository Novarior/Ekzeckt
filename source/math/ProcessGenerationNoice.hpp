#ifndef CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#define CPP_MATH_PSEDO_GENERATION_NOICE_HPP

#include "mymath.hpp"

class ProcessGenerationNoice {
private:
    mmath::noiceData& m_data;

public:
    double InterpolatedNoise(int i, double x, double y);
    double Interpolate(double a, double b, double x);
    double SmoothedNoise(int i, int x, int y);
    double Noise(int i, int x, int y);

    ProcessGenerationNoice(mmath::noiceData& data);
    virtual ~ProcessGenerationNoice();

    void setNoiceData(mmath::noiceData& data) { this->m_data = data; }

    void setSeed(double seed);
    mmath::noiceData& getNoiceData() { return this->m_data; }
    double getSeed();
    double getNoice(double x, double y);
};
#endif