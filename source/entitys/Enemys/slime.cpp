#include "slime.hpp"

Slime::Slime(float spawn_pos_x, float spawn_pos_y, Entity* targer_follow)
	: Entity(entityEnum::entityBehaviorClass::ebc_ENEMY,
			 entityEnum::entityMovementState::ems_IDLE,
			 entityEnum::entityState::es_DISABLED,
			 entityEnum::entityDirection::ed_VOID) {
	this->m_texture = TextureManager::getTexture("texture_Slime");

	this->m_sprite.setTexture(this->m_texture);
	this->m_sprite.setScale({0.02f, 0.02f});
	this->createHitboxComponent(this->m_sprite, 0.f, 0.f, 32.f, 32.f);
	this->createMovementComponent(2.f, 1.4f, 1.f);
	this->createAttributesComponent();

	this->e_setPosition(spawn_pos_x, spawn_pos_y);
	this->ai_component = std::make_unique<AIComponent>(this, targer_follow);
	this->ai_component.get()->create_follow(150);
	this->ai_component.get()->create_attack();
	this->ai_component.get()->create_wander();
}

Slime::~Slime() {}

void Slime::e_update(const float& delta_time) {
	// check if entity is disabled
	if (e_enumState == entityEnum::entityState::es_DISABLED)
		return;

	this->ai_component->update(delta_time);

	this->e_movement->update(delta_time);
	this->e_attributes->update(delta_time);
	this->e_hitbox->update();
}

void Slime::e_render(sf::RenderTarget& target, const bool show_hitbox) {
	target.draw(this->m_sprite);

#if __MDEBUG__
	if (show_hitbox) {
		this->e_hitbox->render(target);
		this->ai_component->render(target);
	}
#endif
}
