#include "player.hpp"
// Initializer functions

// Constructors / Destructors
Player::Player(sf::Vector2f pos)
  : Entity(entityEnum::entityBehaviorClass::ebc_PLAYER,
       entityEnum::entityMovementState::ems_IDLE,
       entityEnum::entityState::es_ALIVE,
       entityEnum::entityDirection::ed_VOID)
{
  Atri attributes;
  // initialaize attributes for new entity
  attributes.level = 1;
  // calculate max health and mana
  attributes.health = 1;
  attributes.mana = 1;
  // set experience to 0 and experience_for_level
  attributes.some_points = 0;
  attributes.experience = 0;
  attributes.experience_for_level = 200 + ((attributes.level - 1) * 200);
  // calculate new max health and max mana
  attributes.max_health = 10.f + std::floor(5 * (attributes.level - 1)) + (attributes.some_points * 18);
  attributes.max_mana = 5.f + std::floor(5 * (attributes.level * 0.25)) + (attributes.some_points / 16) * 10;
  // calculate new regen and max health
  attributes.regeneration_health = 1 + (attributes.level * 0.15) + (attributes.some_points * 0.0625 / 2);
  attributes.regeneration_mana = 1 + (attributes.level + (attributes.some_points * 0.01 - 1)) * 0.1;
  // calculate new damage
  attributes.damage = 1 + (attributes.level * 1.25) + (attributes.some_points * 0.0625 / 2);
  attributes.isAlive = true;

  this->m_texture = TextureManager::getTexture("texture_Player");
  this->m_sprite.setTexture(this->m_texture);
  this->m_sprite.setScale({0.02f, 0.02f});
  this->createHitboxComponent(this->m_sprite, 0.f, 0.f, 16.f, 16.f);
  this->createMovementComponent(10.f, 5.f, 3.f);
  this->createAttributesComponent(&attributes);
  this->e_setPosition(pos);
  this->m_radius.setRadius(100.f);
  this->m_radius.setOrigin({this->m_radius.getRadius(), this->m_radius.getRadius()});
  this->m_radius.setPosition(this->m_sprite.getPosition());
  this->m_radius.setFillColor(sf::Color::Transparent);
  this->m_radius.setOutlineColor(sf::Color::Red);
  this->m_radius.setOutlineThickness(1.f);

  this->createInventoryComponent();
}

Player::~Player() {}

void Player::e_update(const float &delta_time)
{
  this->e_movement->update(delta_time);
  this->e_hitbox->update();
  this->e_attributes->update(delta_time);
  this->m_radius.setPosition(this->m_sprite.getPosition());
  this->m_radius.setOutlineColor(sf::Color::Red);
}

void Player::e_render(sf::RenderTarget &target, const bool show_hitbox)
{
  target.draw(this->m_sprite);

  if (show_hitbox)
  {
    this->e_hitbox->render(target);
    target.draw(this->m_radius);
  }
}

void Player::e_attack(Entity *target, const float &delta_time)
{ // chek if some entity is in range

  if (this->m_radius.getGlobalBounds().findIntersection(target->getGlobalBounds()))
  {
    this->m_radius.setOutlineColor(sf::Color::Green);
    target->e_takeDamage(this->e_attributes->getAttributes().damage);
  }
}
