#ifndef CPP_MATH_PSEDO_GENERATION_NOICE_HPP
#define CPP_MATH_PSEDO_GENERATION_NOICE_HPP

#include "../mymath.hpp"

struct noiceData {
	unsigned int mapSizeX = 0;
	unsigned int mapSizeY = 0;
	unsigned int mapSizeZ = 0;
	float gridSize = 0;
	uint32_t seed = 0;
	int offsetSeed = 0xffff;
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

class ProcessGenerationNoice {
private:
	noiceData* m_data = nullptr;

	double InterpolatedNoise(int i, double x, double y);
	double Interpolate(double a, double b, double x);
	double SmoothedNoise(int i, int x, int y);
	double FastSmoothedNoise(int i, int x, int y);
	double Noise(int i, int x, int y);

public:
	ProcessGenerationNoice() {}
	virtual ~ProcessGenerationNoice() {}

	void setNoiceData(noiceData* data) { this->m_data = data; }

	double getNoice(double x, double y);
};
#endif