#include "../../core/header.h"

#include "block.hpp"

BrickBlock::BrickBlock(sf::Vector2i size, sf::Vector2i position,
                       sf::Color color, bool collision, sf::Texture &texture,
                       unsigned short type, bool isAnim, bool isSetTree)
    : m_sprite(texture, {{0, 0}, {size}}), m_type(type), m_isAnim(isAnim),
      isSetTree(isSetTree), m_collision(collision), m_size(size) {
  this->m_sprite.setPosition(static_cast<sf::Vector2f>(position));
  this->m_sprite.setColor(color);

  if (isAnim) {
    this->currentFrame = 0;
    this->framesCounter = this->m_sprite.getTexture().getSize().y / size.y;
  }
}

BrickBlock::~BrickBlock() {}

void BrickBlock::updateFrame() { this->currentFrame++; }

const sf::FloatRect BrickBlock::getGlobalBounds() {
  return this->m_sprite.getGlobalBounds();
}

const bool BrickBlock::intersects(sf::FloatRect rect) {
  return this->m_sprite.getGlobalBounds()
      .findIntersection(static_cast<sf::FloatRect>(rect))
      .has_value();
}

void BrickBlock::updateAnimation() {
  if (this->m_isAnim) {
    if (this->currentFrame >= this->framesCounter)
      this->currentFrame = 0;

    this->m_sprite.setTextureRect(
        sf::IntRect({0, static_cast<int>(this->currentFrame) * this->m_size.y},
                    {this->m_size.x, this->m_size.y}));
  }
}

void BrickBlock::render(sf::RenderTarget *target) {
  target->draw(this->m_sprite);
}