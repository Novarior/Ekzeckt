#include "hitbox.hpp"

HitboxComponent::HitboxComponent(sf::Sprite &sprite, float offset_x,
                                 float offset_y, float width, float height)
    : sprite(sprite), offsetX(offset_x), offsetY(offset_y) {

  this->nextPosition.position.x = 0.f;
  this->nextPosition.position.y = 0.f;
  this->nextPosition.size.x = width;
  this->nextPosition.size.y = height;

  this->hitbox.setPosition({this->sprite.getPosition().x + offset_x,
                            this->sprite.getPosition().y + offset_y});
  this->hitbox.setSize(sf::Vector2f(width, height));
  this->hitbox.setFillColor(sf::Color::Transparent);
  this->hitbox.setOutlineThickness(-1.f);
  this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent() {}

// Accessors
const sf::Vector2f HitboxComponent::getPosition() const {
  return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBounds() const {
  return this->hitbox.getGlobalBounds();
}

const sf::FloatRect
HitboxComponent::getNextPosition(const sf::Vector2f velocity) {
  this->nextPosition.position.x = this->hitbox.getPosition().x + velocity.x;
  this->nextPosition.position.y = this->hitbox.getPosition().y + velocity.y;

  return this->nextPosition;
}

// Modifiers
void HitboxComponent::setPosition(const sf::Vector2f &position) {
  this->hitbox.setPosition(position);
  this->sprite.setPosition(
      {position.x - this->offsetX, position.y - this->offsetY});
}

void HitboxComponent::setPosition(const float x, const float y) {
  this->hitbox.setPosition({x, y});
  this->sprite.setPosition({x - this->offsetX, y - this->offsetY});
}

// Functions
bool HitboxComponent::intersects(const sf::FloatRect &frect) {
  return this->hitbox.getGlobalBounds().findIntersection(frect).has_value();
}

void HitboxComponent::update() {
  this->hitbox.setPosition({this->sprite.getPosition().x + this->offsetX,
                            this->sprite.getPosition().y + this->offsetY});
}

void HitboxComponent::render(sf::RenderTarget &target) {
  target.draw(this->hitbox);
}