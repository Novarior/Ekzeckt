#ifndef NOICE_DATA_HPP
#define NOICE_DATA_HPP
struct NoiceData {
	// map size info not-4-gen
	unsigned int mapSizeX = 0;
	unsigned int mapSizeY = 0;
	unsigned int mapSizeZ = 0;
	int gridSize = 0;
	float chanceToSpawnTree = 0.0f;
	// data 4-gen 
	int seed = 0;
	int offsetSeed = 0;
	unsigned octaves = 0;
	float amplifire = 0.f;
	float persistence = 0.f;
	float frequency = 0.f;
	// non-4-gen info
	unsigned int RenderWindowX = 0;
	unsigned int RenderWindowY = 0;
	// 4-gen info
	unsigned int smoothMode = 0;
	bool fastMode = false;
};
#endif NOICE_DATA_HPP