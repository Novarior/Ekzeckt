#ifndef NOICE_DATA_HPP
#define NOICE_DATA_HPP
struct NoiceData {
	unsigned int mapSizeX = 0;
	unsigned int mapSizeY = 0;
	unsigned int mapSizeZ = 0;
	int seed = 0;
	int offsetSeed = 0;
	int gridSize = 0;
	float chanceToSpawnTree = 0.0f;
	float amplifire = 0.f;
	float persistence = 0.f;
	float frequency = 0.f;
	unsigned octaves = 0;
	unsigned int RenderWindowX = 0;
	unsigned int RenderWindowY = 0;
	unsigned int smoothMode = 0;
	bool fastMode = false;
};
#endif NOICE_DATA_HPP