#include "entity.hpp"



void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height)
{
    this->e_hitbox = std::make_unique<HitboxComponent>(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity)
{
    this->e_movement = std::make_unique<MovementComponent>(this->m_sprite, acceleration, deceleration, maxVelocity);
}

void Entity::createAttributesComponent(Atri *attributes)
{
    if (attributes != nullptr)
        this->e_attributes = std::make_unique<Attributes>(attributes);
    else
        this->e_attributes = std::make_unique<Attributes>();
}

// Method to create an inventory component for the entity.
void Entity::createInventoryComponent(unsigned int rows, unsigned int cols)
{
    this->e_inventory = std::make_shared<Inventory>(rows, cols);
}

// Method to create an item for entity
void Entity::createItemComponent(std::shared_ptr<Item> _shrd_item)
{
    this->e_item = std::make_shared<Item>(*_shrd_item);
}

Entity::Entity(entityEnum::entityBehaviorClass enumBehavior, entityEnum::entityMovementState enumMovementState, entityEnum::entityState enumState, entityEnum::entityDirection enumDirection)
    : e_movement(nullptr), e_hitbox(nullptr), e_attributes(nullptr), e_inventory(nullptr), e_item(nullptr), e_enumBehavior(enumBehavior),
      e_enumMovementState(enumMovementState), e_enumState(enumState), e_enumDirection(enumDirection), m_sprite(TextureManager::getTexture("texture_null"))
{
    // apply id's this entity
    this->ID_entity = this->count_entitys;
    this->count_entitys++;
}

Entity::~Entity()
{
#if __MDEBUG__
    // check memory leak
    if (this->e_inventory != nullptr)
        this->e_inventory->clearInventory();
    this->e_inventory.reset();
    // call logger and print message with "Bit size"
    Logger::logStatic("Entity has been destroyed, ID: " + std::to_string(this->ID_entity), "~Entity", logType::LINFO);
    // send LINFO about inventory
    Logger::logStatic("included inventory memory size: " + std::to_string(sizeof(*this->e_inventory)) + " bytes", "~Entity", logType::LINFO);

#endif
    this->count_entitys--;
}

void Entity::e_move(const float &dir_x, const float &dir_y, const float &delta_time)
{
    this->e_movement->move(dir_x, dir_y, delta_time);
}

const sf::FloatRect Entity::getGlobalBounds()
{
    if (this->e_hitbox != nullptr)
        return this->e_hitbox->getGlobalBounds();

    return this->m_sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float &delta_time)
{
    if (this->e_hitbox != nullptr && this->e_movement != nullptr)
        return this->e_hitbox->getNextPosition(this->e_movement->getVelocity() * delta_time);

    return sf::FloatRect({0, 0}, {1, 1});
}

const sf::Vector2i Entity::e_getGridPositionInt(const unsigned int &grisSize)
{
    if (this->e_hitbox != nullptr)
        return sf::Vector2i(static_cast<int>(this->e_hitbox->getPosition().x) / grisSize, static_cast<int>(this->e_hitbox->getPosition().y) / grisSize);

    return sf::Vector2i(static_cast<int>(this->m_sprite.getPosition().x) / grisSize, static_cast<int>(this->m_sprite.getPosition().y) / grisSize);
}

const sf::Vector2f Entity::e_getCenterPosition()
{
    return sf::Vector2f(this->m_sprite.getPosition().x + this->m_sprite.getGlobalBounds().size.x / 2.f, this->m_sprite.getPosition().y + this->m_sprite.getGlobalBounds().size.y / 2.f);
}