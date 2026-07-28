#include "Noice_PGN.hpp"

// Linear / selectable interpolation
double ProcessGenerationNoice::Interpolate(double a, double b, double x) {
	if (!m_data) return mmath::interpolation::LinInter(x, a, b);

	if (m_data && m_data->fastMode)
		return mmath::interpolation::LinInter(x, a, b);

	switch (m_data->smoothMode) {
	case 0: return mmath::interpolation::LinInter(x, a, b);
	case 1: return mmath::interpolation::CosInter(x, a, b);
	case 2: return mmath::interpolation::CubicInter(x, a, b);
	case 3: return mmath::interpolation::QuinticInter(x, a, b);
	case 4: return mmath::interpolation::QuarticInter(x, a, b);
	case 5: return mmath::interpolation::QuadraticInter(x, a, b);
	case 6: return mmath::interpolation::HermiteInter(x, a, b);
	default: return mmath::interpolation::LinInter(x, a, b);
	}
}

// large 64bit function
//double ProcessGenerationNoice::Noise(double i, double x, double y) {
//	// Use integer lattice coordinates for hashing
//	int32_t xi = static_cast<int32_t>(std::floor(x));
//	int32_t yi = static_cast<int32_t>(std::floor(y));
//
//	// Compose a 64-bit seed/hash safely
//	uint64_t n = static_cast<uint64_t>(static_cast<int64_t>(xi) + static_cast<int64_t>(yi) * 31LL);
//	n = (n * 0x5DEECE66DULL) & 0xFFFFFFFFFFFFFFFFULL;
//
//	int32_t a = m_data ? (m_data->offsetSeed + m_data->seed * xi) : 0;
//	int32_t b = m_data ? (m_data->offsetSeed + m_data->seed * yi) : 0;
//	int32_t c = m_data ? (m_data->offsetSeed + m_data->seed * (xi + yi)) : 0;
//
//	uint64_t t = (n * (n * n * static_cast<uint64_t>(std::abs(a)) + static_cast<uint64_t>(std::abs(b))) + static_cast<uint64_t>(std::abs(c))) & 0x7FFFFFFFFFFFFFFFULL;
//	// scale to [-1,1]: divide by large constant (2^62 ~ 4.6e18) then map to [-1,1]
//	double v = static_cast<double>(t) / static_cast<double>(0x7FFFFFFFFFFFFFFFULL); // in [0,1]
//	return v * 2.0 - 1.0; // map to [-1,1]
//}

double ProcessGenerationNoice::Noise(double /*i*/, double x, double y) {
	// Use integer lattice coordinates
	int32_t xi = static_cast<int32_t>(std::floor(x));
	int32_t yi = static_cast<int32_t>(std::floor(y));

	// Combine coordinates into 64-bit key (cheap)
	uint64_t key = (static_cast<uint64_t>(static_cast<uint32_t>(xi)) << 32) | static_cast<uint32_t>(yi);

	// Mix with seed(s) — compute only once per call (or cache externally for many calls)
	uint64_t seedMix = 0ULL;
	if (m_data) {
		seedMix = static_cast<uint64_t>(static_cast<uint32_t>(m_data->seed)) + static_cast<uint64_t>(static_cast<uint32_t>(m_data->offsetSeed));
	}

	uint64_t h = mmath::splitmix64(key + seedMix);

	// Map to [-1,1] using double range
	const double inv = 1.0 / static_cast<double>(0xFFFFFFFFFFFFFFFFULL);
	double v = static_cast<double>(h) * inv; // [0,1]
	return v * 2.0 - 1.0; // [-1,1]
}
// Proper smoothed noise with normalized weights: corners/16 + sides/8 + center/4
double ProcessGenerationNoice::SmoothedNoise(double i, double x, double y) {
	double corners = (Noise(i, x - 1, y - 1) + Noise(i, x + 1, y - 1) + Noise(i, x - 1, y + 1) + Noise(i, x + 1, y + 1)) / 16.0;
	double sides = (Noise(i, x - 1, y) + Noise(i, x + 1, y) + Noise(i, x, y - 1) + Noise(i, x, y + 1)) / 8.0;
	double center = Noise(i, x, y) / 4.0;
	return corners + sides + center;
}

// Faster approximate smoothing: simple 4-sample average
double ProcessGenerationNoice::FastSmoothedNoise(double i, double x, double y) {
	double v00 = Noise(i, x, y);
	double v10 = Noise(i, x + 1, y);
	double v01 = Noise(i, x, y + 1);
	double v11 = Noise(i, x + 1, y + 1);
	return (v00 + v10 + v01 + v11) * 0.25;
}

// Fractal interpolation (interpolated smoothed noise)
double ProcessGenerationNoice::InterpolatedNoise(double i, double x, double y) {
	// integer/fractional parts must be computed with floor
	double integer_X = std::floor(x);
	double fractional_X = x - integer_X;
	double integer_Y = std::floor(y);
	double fractional_Y = y - integer_Y;

	double v1, v2, v3, v4;
	if (m_data && !m_data->fastMode) {
		v1 = SmoothedNoise(i, integer_X, integer_Y);
		v2 = SmoothedNoise(i, integer_X + 1.0, integer_Y);
		v3 = SmoothedNoise(i, integer_X, integer_Y + 1.0);
		v4 = SmoothedNoise(i, integer_X + 1.0, integer_Y + 1.0);
	} else {
		v1 = FastSmoothedNoise(i, integer_X, integer_Y);
		v2 = FastSmoothedNoise(i, integer_X + 1.0, integer_Y);
		v3 = FastSmoothedNoise(i, integer_X, integer_Y + 1.0);
		v4 = FastSmoothedNoise(i, integer_X + 1.0, integer_Y + 1.0);
	}

	double i1 = Interpolate(v1, v2, fractional_X);
	double i2 = Interpolate(v3, v4, fractional_X);
	return Interpolate(i1, i2, fractional_Y);
}

//double ProcessGenerationNoice::getNoice(double x, double y) {
//	double total = 0;
//	double frequency = pow(2, m_data->frequency);
//	double amplifire = m_data->amplifire;
//
//	for (int i = 0; i < m_data->octaves; ++i) {
//		total += InterpolatedNoise((1 + i) % 10, m_data->seed + x / frequency, m_data->seed + y / frequency) * amplifire;
//		frequency /= 2;
//		amplifire *= m_data->persistence;
//	}
//	return total / frequency;
//}

double ProcessGenerationNoice::getNoice(double x, double y) {
	double total = 0.0;
	double frequency = (m_data->frequency == 0.0f) ? 1.0 : static_cast<double>(m_data->frequency);
	frequency *= frequency;
	double amplitude = (m_data->amplifire == 0.0f) ? 1.0 : static_cast<double>(m_data->amplifire);
	double persistence = static_cast<double>(m_data->persistence);

	double maxAmplitude = 0.0;
	unsigned int octaves = (m_data->octaves == 0) ? 1u : m_data->octaves;

	// Use offsets as added translation (optional)
	double ox = static_cast<double>(m_data->offsetSeed + m_data->seed);
	double oy = static_cast<double>(m_data->offsetSeed + m_data->seed);

	for (unsigned int i = 0; i < octaves; ++i) {
		double sampleX = ox + x / frequency;
		double sampleY = oy + y / frequency;
		total += InterpolatedNoise(static_cast<double>(i), sampleX, sampleY) * amplitude;
		amplitude *= persistence;
		maxAmplitude += amplitude;

		frequency *= 0.5;
	}

	//if (maxAmplitude == 0.0) return 0.0;
	double result = total / frequency;
	// result already in approx [-1,1], return as-is (caller can rescale)
	//return result;
	return mmath::normalize(result);
	//return mmath::Rescale(result, -1.0, 1.0, 0.0, 255);
}