#ifndef ENTITY
#define ENTITY

#include "../Content/ItemsStuff/Inventory.hpp"
#include "entityEnum.hpp"
#include "properties/attributes.hpp"
#include "properties/hitbox.hpp"
#include "properties/movement.hpp"
#include <memory>

/**
 * @class Entity
 * @brief This class represents a general game entity.
 *
 * An entity in a game is an object which exists in the game world. Examples of
 * entities include players, enemies, items, etc. This class provides a base for
 * creating different types of entities, with common properties like texture,
 * sprite, movement, hitbox, and attributes. It also provides methods for
 * creating these components and getting their values. Each entity has a unique
 * ID for identification and a flag to indicate whether it is in collision with
 * another entity. The movement state of the entity is also tracked.
 */
class Entity
{
private:
protected:
    // The texture used to visually represent the entity in the game.
    sf::Texture m_texture;
    // The sprite that applies the texture and can be manipulated to move, rotate,
    // scale the entity.
    sf::Sprite m_sprite;
    // The component that handles the movement logic of the entity (speed,
    // direction, etc.).
    std::unique_ptr<MovementComponent> e_movement;
    // The component that handles the collision detection for the entity.
    std::unique_ptr<HitboxComponent> e_hitbox;
    // The component that handles the entity's attributes (health, strength,
    // etc.).
    std::unique_ptr<Attributes> e_attributes;
    // The component that handles the entity's inventory (items, equipment, etc.).
    std::shared_ptr<Inventory> e_inventory;
    // basic slot for item for entity
    std::shared_ptr<Item> e_item;

    bool isCollision;       // A flag indicating whether the entity is currently in a
                            // state of collision with another entity or not.
    float gridSizeF;        // The size of a single grid cell in the game world. Used for
                            // positioning and movement calculations.
    unsigned int ID_entity; // A unique identifier for each entity instance.
                            // Useful for entity management and referencing.

    // The behavior class of the entity, which defines its type and
    // behavior in the game world.
    entityEnum::entityBehaviorClass e_enumBehavior;
    entityEnum::entityMovementState e_enumMovementState;
    entityEnum::entityState e_enumState;
    entityEnum::entityDirection e_enumDirection;

    // Method to create a hitbox component for the entity.
    // The hitbox is defined by an offset from the entity's position and a width
    // and height.
    void createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);

    // Method to create a movement component for the entity.
    // The movement component is defined by acceleration, deceleration, and
    // maximum velocity values.
    void createMovementComponent(const float acceleration, const float deceleration, const float maxVelocity);

    // Method to create an attributes component for the entity.
    // The attributes component can be initialized with a pre-defined set of
    // attributes.
    void createAttributesComponent(Atri *attributes = nullptr);

    // Method to create an inventory component for the entity.
    void createInventoryComponent(unsigned int rows, unsigned int cols);

    // Method to create an item for entity
    void createItemComponent(std::shared_ptr<Item> _shrd_item);

public:
    // Count of entities
    static unsigned int count_entitys;

    // Default constructor for the Entity class
    Entity(entityEnum::entityBehaviorClass enumBehavior = entityEnum::entityBehaviorClass::ebc_VOID,
           entityEnum::entityMovementState enumMovementState = entityEnum::entityMovementState::ems_VOID,
           entityEnum::entityState enumState = entityEnum::entityState::es_VOID,
           entityEnum::entityDirection enumDirection = entityEnum::entityDirection::ed_VOID);

    // Virtual destructor for the Entity class
    virtual ~Entity();

    /// @brief Returns a pointer to the HitboxComponent of the entity.
    /// The HitboxComponent is used for collision detection in the game.
    inline HitboxComponent *getHitbox() { return this->e_hitbox.get(); }

    /// @brief Returns a pointer to the MovementComponent of the entity.
    /// The MovementComponent is used for controlling the movement of the entity
    /// in the game world.
    inline MovementComponent *getMovement() { return this->e_movement.get(); }

    /// @brief Returns a pointer to the AttributesComponent of the entity.
    /// The AttributesComponent is used for managing the attributes (like health,
    /// strength, etc.) of the entity.
    inline Attributes *getAttributes() { return this->e_attributes.get(); }

    /// @brief Returns the unique identifier (ID) of the entity.
    /// The ID is used for distinguishing between different entities in the game.
    inline const unsigned int &e_getID() const { return this->ID_entity; }

    /// @brief Returns the total number of entities that have been created.
    /// This count is useful for keeping track of how many entities exist in the
    /// game at any given time.
    inline const unsigned int &e_getCountEntitys() const { return this->count_entitys; }

    /// @brief return the inventory of the entity
    /// @return pointer to the inventory of the entity
    inline std::shared_ptr<Inventory> e_getInventory() const { return this->e_inventory; }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Checks if the entity is alive or not.
    inline const bool e_isAlive() const { return this->e_attributes->getAttributes().isAlive; }

    // Returns the grid size used for the entity.
    // This is typically used for positioning and movement calculations.
    inline virtual const float getGridSizeFloat() const { return this->gridSizeF; }

    // Returns the current velocity of the entity.
    // This is the speed and direction in which the entity is currently moving.
    inline virtual const sf::Vector2f e_getVelocity() { return this->e_movement->getVelocity(); }

    // Returns the current position of the entity.
    // This is the point in the 2D space where the entity is located.
    inline virtual const sf::Vector2f e_getPosition() { return this->m_sprite.getPosition(); }

    // Returns the center position of the entity.
    // This is the point in the 2D space where the center of the entity is
    // located.
    virtual const sf::Vector2f e_getCenterPosition();

    // Returns the entity's position in the grid, converted to a floating point
    // number. This is used for grid-based calculations.
    virtual const sf::Vector2f e_getGridPositionFloat(const float &gridsize)
    {
        return sf::Vector2f(this->m_sprite.getPosition().x / gridsize, this->m_sprite.getPosition().y / gridsize);
    }

    // Returns the global bounds of the entity.
    // This is the rectangle that encloses the entity in the 2D space.
    virtual const sf::FloatRect getGlobalBounds();

    // Returns the bounds of the entity's next position.
    // This is the rectangle that would enclose the entity if it moved according
    // to its current velocity.
    virtual const sf::FloatRect getNextPositionBounds(const float &delta_time);

    // Returns the entity's position in the grid, converted to an integer.
    // This is used for grid-based calculations where precision is not required.
    virtual const sf::Vector2i e_getGridPositionInt(const unsigned int &grisSize);

    /// @brief Sets the collision state of the entity.
    /// @param isCollision A boolean value indicating the collision state.
    inline virtual void e_setCollision(const bool isCollision) { this->isCollision = isCollision; }

    /// @brief Loads a texture from a file and applies it to the entity's sprite.
    /// @param file_path The path to the texture file.
    inline virtual void e_updateTexture(const sf::Texture &_texture) { this->m_texture.update(_texture); }

    /// @brief Sets the entity's sprite texture using a pointer to an sf::Texture.
    /// @param texture A pointer to the sf::Texture to apply.
    inline virtual void e_setTexture(sf::Texture *texture) { this->m_sprite.setTexture(*texture); }

    /// @brief Sets the entity's sprite texture using a reference to an
    /// sf::Texture.
    /// @param texture A reference to the sf::Texture to apply.
    inline virtual void e_setTexture(sf::Texture &texture) { this->m_sprite.setTexture(texture); }

    /// @brief Sets the position of the entity using an sf::Vector2f.
    /// @param pos The new position for the entity.
    inline virtual void e_setPosition(const sf::Vector2f pos) { this->m_sprite.setPosition(pos); }

    /// @brief Sets the position of the entity using separate x and y coordinates.
    /// @param pos_x The new x-coordinate for the entity.
    /// @param pos_y The new y-coordinate for the entity.
    inline virtual void e_setPosition(const float pos_x, const float pos_y) { this->m_sprite.setPosition(sf::Vector2f(pos_x, pos_y)); }

    /// @brief Sets the unique identifier (ID) of the entity.
    /// @param ID The new ID for the entity.
    inline virtual void e_setID(const unsigned int &ID) { this->ID_entity = ID; }

    /// @brief Updates the entity's movement based on the elapsed time.
    /// @param delta_time The time elapsed since the last update.
    inline virtual void e_updateMovement(const float &delta_time) { this->e_movement->update(delta_time); }

    /// @brief Updates the entity's hitbox.
    inline virtual void e_updateHitbox(sf::IntRect rectEntity, sf::IntRect rectCollision) { this->e_hitbox->update(); }

    /// @brief Updates the entity's animation based on the elapsed time.
    /// @param keyNameAnimation The name of the animation to update.
    /// @param delta_time The time elapsed since the last update.
    virtual void e_updateAnimation(std::string keyNameAnimation, const float &delta_time) {}

    /// @brief Moves the entity in the specified direction.
    /// @param dir_x The x-coordinate of the direction vector.
    /// @param dir_y The y-coordinate of the direction vector.
    /// @param delta_time The time elapsed since the last update.
    virtual void e_move(const float &dir_x, const float &dir_y, const float &delta_time);

    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////

    // Action methods

    /// @brief Executes the entity's attack action on a target entity.
    /// @param target The entity to be attacked.
    /// @param delta_time The time elapsed since the last update.

    /// @brief Applies damage to the entity.
    /// @param damage The amount of damage to apply.
    inline virtual void e_takeDamage(const int &damage) { this->e_attributes->takeDamage(damage); }

    virtual void e_attack(Entity *target, const float &delta_time) {}
    /// @brief Executes the entity's death action.
    void e_die();

    /// @brief Executes the entity's interaction action.
    void e_interact();

    /// @brief Executes the entity's interaction action with another entity.
    /// @param _entity The entity to interact with.
    void e_interact(Entity &_entity);

    // Update and render methods

    /// @brief Updates the entity's state.
    /// @param dt The time elapsed since the last update.
    virtual void e_update(const float &dt) {}
    /// @brief Renders the entity on a render target.
    /// @param target The render target to draw the entity on.
    /// @param show_hitbox A flag indicating whether to draw the entity's hitbox
    /// or not.
    virtual void e_render(sf::RenderTarget &target, const bool show_hitbox = false) {}
};

#endif /* ENTITY */
