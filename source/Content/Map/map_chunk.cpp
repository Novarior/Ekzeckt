#include "map_chunk.hpp"

Chunk::Chunk(sf::Vector2i cPosition) {
	mBlocks.clear();
	mBlocks.resize(CHUNK_VECTOR_SIZE);
	chunkState = ChunkMemoryState::CHS_NULL;
	chunkPosition = cPosition;
	
}

Chunk::~Chunk() {
	mBlocks.clear();
}

const ChunkMemoryState Chunk::getChunkMemoryState() const {
	return chunkState;
}

void Chunk::update() {
	//for (auto& bl : mBlocks)
}

void Chunk::render(sf::RenderTarget& target, sf::RenderStates states) {
	for (auto& bl : mBlocks)
		target.draw(bl, states);
}
