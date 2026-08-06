#pragma once

#include <vector>

#include "map_block.hpp"

constexpr unsigned CHUNK_SIZE_X = 16U;
constexpr unsigned CHUNK_SIZE_Y = 16U;
constexpr unsigned CHUNK_VECTOR_SIZE = CHUNK_SIZE_X*CHUNK_SIZE_Y;

enum class ChunkMemoryState {
	CHS_NULL,
	CHS_UNLOAD,
	CHS_PRELOAD,
	CHS_LOAD
};

class Chunk {
private:
	std::vector<BrickBlock> mBlocks;
	ChunkMemoryState chunkState;
	sf::Vector2i chunkPosition;


public:
	Chunk(sf::Vector2i cPosition);
	~Chunk();

	const ChunkMemoryState getChunkMemoryState() const;

	void update();
	void render(sf::RenderTarget& target, sf::RenderStates states);
};

