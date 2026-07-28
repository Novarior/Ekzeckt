#include "Noice_Perlin.hpp"

#include <algorithm>

PerlinNoise::PerlinNoise(NoiceData* _data):data(_data) {
	// Initialize the permutation vector with the reference values
	for (int i = 0; i < 256; ++i)
		p[i] = i;

	// Shuffle the array with the given seed
	std::mt19937 gen(data->seed + data->offsetSeed);
	std::shuffle(p, p + 256, gen);

	// Duplicate the permutation vector
	for (int i = 0; i < 256; ++i)
		p[256 + i] = p[i];
}

// Single public Noise function supporting single-octave and fBM using NoiceData
double PerlinNoise::Noise(double x_cord, double y_cord, double minValue, double maxValue) {
	// Validate config pointer
	if (!data) return 0.0;

	// Determine whether to use fast gradients
	bool useFast = data->fastMode;

	// Prepare fBM parameters from config (fallbacks where appropriate)
	unsigned int octaves = (data->octaves == 0 ? 1u : data->octaves);
	double persistence = static_cast<double>(data->persistence);
	double baseFrequency = (data->frequency == 0.0f ? 1.0 : static_cast<double>(data->frequency / 1000.0));
	double baseAmplitude = (data->amplifire == 0.0f ? 1.0 : static_cast<double>(data->amplifire / 10.0));

	// Single-octave shortcut
	if (octaves <= 1) {
		double freq = baseFrequency;
		// compute lattice and fractional parts
		double xf_floor = std::floor(x_cord * freq);
		double yf_floor = std::floor(y_cord * freq);
		int X = static_cast<int>(xf_floor) & 255;
		int Y = static_cast<int>(yf_floor) & 255;
		double x = x_cord * freq - xf_floor; // fractional part in [0,1)
		double y = y_cord * freq - yf_floor;

		double u = mmath::Fade(x);
		double v = mmath::Fade(y);

		int A = p[X] + Y;
		int AA = p[A];
		int AB = p[A + 1];
		int B = p[X + 1] + Y;
		int BA = p[B];
		int BB = p[B + 1];

		double res;
		if (useFast) {
			res = mmath::interpolation::QuinticInter(
				v,
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AA], x, y), mmath::Gradient_v4(p[BA], x - 1.0, y)),
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AB], x, y - 1.0), mmath::Gradient_v4(p[BB], x - 1.0, y - 1.0))
			);
		} else {
			res = mmath::interpolation::QuinticInter(
				v,
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AA], x, y), mmath::Gradient_v16(p[BA], x - 1.0, y)),
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AB], x, y - 1.0), mmath::Gradient_v16(p[BB], x - 1.0, y - 1.0))
			);
		}

		// Clamp small numerical overshoot and rescale to requested range
		if (res > 1.0) res = 1.0;
		if (res < -1.0) res = -1.0;
		return mmath::Rescale(res, -1.0, 1.0, minValue, maxValue);
	}

	// Fractal Brownian Motion (fBM) for multiple octaves
	double total = 0.0;
	double amplitude = baseAmplitude;
	double frequency = baseFrequency;
	double maxAmplitude = 0.0;

	for (unsigned int i = 0; i < octaves; ++i) {
		double xf_floor = std::floor(x_cord * frequency);
		double yf_floor = std::floor(y_cord * frequency);
		int X = static_cast<int>(xf_floor) & 255;
		int Y = static_cast<int>(yf_floor) & 255;
		double x = x_cord * frequency - xf_floor;
		double y = y_cord * frequency - yf_floor;

		double u = mmath::Fade(x);
		double v = mmath::Fade(y);

		int A = p[X] + Y;
		int AA = p[A];
		int AB = p[A + 1];
		int B = p[X + 1] + Y;
		int BA = p[B];
		int BB = p[B + 1];

		double res;
		if (useFast) {
			res = mmath::interpolation::QuinticInter(
				v,
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AA], x, y), mmath::Gradient_v4(p[BA], x - 1.0, y)),
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v4(p[AB], x, y - 1.0), mmath::Gradient_v4(p[BB], x - 1.0, y - 1.0))
			);
		} else {
			res = mmath::interpolation::QuinticInter(
				v,
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AA], x, y), mmath::Gradient_v16(p[BA], x - 1.0, y)),
				mmath::interpolation::QuinticInter(u, mmath::Gradient_v16(p[AB], x, y - 1.0), mmath::Gradient_v16(p[BB], x - 1.0, y - 1.0))
			);
		}

		total += res * amplitude;
		maxAmplitude += amplitude;

		amplitude *= persistence;
		frequency *= 2.0;
	}

	// Normalize and clamp
	double normalized = 0.0;
	if (maxAmplitude != 0.0) normalized = total / maxAmplitude;
	normalized = mmath::clamp(normalized, -1.0, 1.0);

	return mmath::Rescale(normalized, -1.0, 1.0, minValue, maxValue);
}