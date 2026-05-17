#include "../../../core/header.h"

#include "entity_item.hpp"

EntityItem::EntityItem(std::shared_ptr<Item> _item)
    : Entity(entityEnum::entityBehaviorClass::ebc_ENTITY_ITEM,
             entityEnum::entityMovementState::ems_IDLE,
             entityEnum::entityState::es_DISABLED,
             entityEnum::entityDirection::ed_VOID) {
  // set position of item
  this->e_updateTexture(TextureManager::getTexture("items_stone"));
  this->m_sprite.setTexture(this->m_texture);

  // Создаем хитбокс для предмета
  this->createHitboxComponent(this->m_sprite, 0.f, 0.f, 32.f, 32.f);
  Atri attributes;
  this->createAttributesComponent(&attributes);
  this->createMovementComponent(0.f, 0.f, 0.f);

  // Устанавливаем позицию
  e_setPosition(0.f, 0.f);

  // Устанавливаем предмет в сущность
  this->createItemComponent(_item);
}

void EntityItem::e_update(const float &delta_time) {}

void EntityItem::e_render(sf::RenderTarget &target, const bool show_hitbox) {
  target.draw(this->m_sprite);
  if (show_hitbox && this->e_hitbox) {

    this->e_hitbox->render(target);
  }
}