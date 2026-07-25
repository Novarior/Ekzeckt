#ifndef CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#define CPP_MATH_PSEDO_GENERATION_NOICE_HPP

#include "../mymath.hpp"
#include "Noise_data.h"

class ProcessGenerationNoice {
private:
	NoiceData* m_data ;

	double InterpolatedNoise(double i, double x, double y);
	double Interpolate(double a, double b, double x);
	double SmoothedNoise(double i, double x, double y);
	double FastSmoothedNoise(double i, double x, double y);
	double Noise(double i, double x, double y);

public:
	ProcessGenerationNoice() {
		m_data = nullptr;
	}
	ProcessGenerationNoice(NoiceData* data) { m_data = data; }
	virtual ~ProcessGenerationNoice() {}

	void setNoiceData(NoiceData* data) {  m_data = data; }

	double getNoice(double x, double y);
};
#endif