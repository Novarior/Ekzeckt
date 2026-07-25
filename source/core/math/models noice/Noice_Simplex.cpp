#include "Noice_Simplex.hpp"

SimplexNoise::SimplexNoise() {
	for (int i = 0; i < 256; ++i)
		perm[i] = static_cast<uint8_t>(i);

	for (int i = 255; i > 0; --i) {
		int j = rand() % (i + 1);
		std::swap(perm[i], perm[j]);
	}
	for (int i = 0; i < 256; ++i)
		perm[i + 256] = perm[i];
}

SimplexNoise::~SimplexNoise() {}

int SimplexNoise::fastfloor(float x) {
	return static_cast<int>(std::floor(x));
}

float SimplexNoise::dot(int* g, float x, float y) {
	return g[0] * x + g[1] * y;
}

float SimplexNoise::computeNoise(float x, float y, int gi, int grad3[][3]) {
	float t = 0.5 - x * x - y * y;
	if (t < 0)
		return 0.0;

	t *= t;
	return t * t * dot(grad3[gi], x, y);
}

float SimplexNoise::noise(float xin, float yin) {
	// Константы для настройки Simplex шума
	static const float F2 = 0.5 * (sqrt(3.0) - 1.0);
	static const float G2 = (3.0 - sqrt(3.0)) / 6.0;

	// Расчет смещения в Simplex сетке
	float s = (xin + yin) * F2;
	int i = fastfloor(xin + s);
	int j = fastfloor(yin + s);
	float t = (i + j) * G2;
	float X0 = i - t;
	float Y0 = j - t;
	float x0 = xin - X0;
	float y0 = yin - Y0;

	// Определение точек сетки
	int i1, j1;
	if (x0 > y0) {
		i1 = 1;
		j1 = 0;
	} else {
		i1 = 0;
		j1 = 1;
	}

	float x1 = x0 - i1 + G2;
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0 + 2.0 * G2;
	float y2 = y0 - 1.0 + 2.0 * G2;

	// Индексы угловых вершин
	int ii = i & 255;
	int jj = j & 255;
	int gi0 = perm[ii + perm[jj]] % 12;
	int gi1 = perm[ii + i1 + perm[jj + j1]] % 12;
	int gi2 = perm[ii + 1 + perm[jj + 1]] % 12;

	double result = 70.0 * (computeNoise(x0, y0, gi0, grad3) + computeNoise(x1, y1, gi1, grad3) + computeNoise(x2, y2, gi2, grad3));
	return mmath::normalize(result);
}
