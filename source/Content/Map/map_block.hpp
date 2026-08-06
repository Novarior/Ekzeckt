#ifndef CPP_CONTENT_BLOCKS_HPP
#define CPP_CONTENT_BLOCKS_HPP
#include "../../core/header.h"

enum BLOCKTYPE {
	NAN_DEF = 0,
	BLOCK_DEEP_OCEAN,
	BLOCK_OCEAN,
	BLOCK_SAND,
	BLOCK_GRASS,
	BLOCK_DIRT,
	BLOCK_STONE,
	BLOCK_SNOWMOUNT
};

class BrickBlock:public sf::Drawable {
private:
	sf::Sprite m_sprite;
	bool m_collision;
	bool m_isAnim;
	const unsigned short m_type;
	sf::Vector2i m_size;
	static uint16_t currentFrame;
	unsigned framesCounter;
	bool isSetTree;

public:
	BrickBlock(sf::Vector2i size, sf::Vector2i position, sf::Color color,
			   bool collosion, sf::Texture& texture, unsigned short type,
			   bool isAnim = false, bool isSetTree = false);
	virtual ~BrickBlock();

	const sf::FloatRect getGlobalBounds();
	const bool intersects(sf::FloatRect rect);
	inline const bool getCollision() const { return this->m_collision; }
	void updateFrame();
	sf::Color getBlockColor() { return this->m_sprite.getColor(); }

	void updateAnimation();

	// override draw() from sf::Drawable
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
#endif