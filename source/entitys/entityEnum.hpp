#pragma once

namespace entityEnum
{

    // Enumerations for entity state, to short saying what is the entity doing right
    // now VOID nonused (default init)
    enum class entityMovementState
    {
        ems_VOID,    // non used (default)
        ems_STAYING, // staying is for the case that the entity is not moving
        ems_IDLE,    // idle is for the case that the entity is not moving, but can be  used
        ems_WALKING, // walking is for the case that the entity is moving, but not running
        ems_RUNNING  // running is for the case that the entity is moving fast

    };

    // enum for direction, to short saying where the entity is looking at
    // VOID is for the case that the entity is not moving
    // UP, DOWN, LEFT, RIGHT are for the main case that the entity is moving
    // four more directions are for the case that the entity is moving diagonal
    // MAXENUM is for the case that the entity is not moving
    enum class entityDirection
    {
        ed_VOID,
        ed_UP,
        ed_DOWN,
        ed_LEFT,
        ed_RIGHT,
        ed_UP_LEFT,
        ed_UP_RIGHT,
        ed_DOWN_LEFT,
        ed_DOWN_RIGHT,
        ed_MAXENUM
    };

    // enum for entity state, saying if the entity is alive or dead, or if the
    // entity is not used (disabled) VOID is for the case that the entity is not
    // used (default) ALIVE the entity is alive and now can be used in the game DEAD
    // the entity is dead and now can be used in the game, but the entity is not
    // alive DISABLE the entity is disabled and now can't be used in the game
    enum class entityState
    {
        es_VOID,
        es_ALIVE,
        es_DEAD,
        es_DISABLED,
        es_MAXENUM
    };

    // enum for Behavior it, can be
    // VOID non used (default initialisation)
    // PLAYER not friendly and not Enemy, some like a neutral but can kill your ass)
    // ENEMY that all non friendly entity, like a slime, rat, bosses, etc
    // NEUTRAL that is neutral entity, but if player (you) did some bad or gut, can
    // be changed Behavior to some side NPC for that case need coments?
    enum class entityBehaviorClass
    {
        ebc_VOID,     // default (like NULL)
        ebc_PLAYER,   // player
        ebc_FRIENDLY, // friendly entitys
        ebc_ENEMY,
        ebc_NEUTRAL,
        ebc_NPC,
        ebc_ENTITY_ITEM,
        ebc_CHEST,
        ebc_OBJECT
    };

    // CLASSes
    // idk for what use this shiet, stiil coments down
    enum class entityClass
    {
        ec_VOID,
        ec_WARRIOR,
        ec_MAGE,
        ec_ROGUE,
        ec_MAXENUM
    };
}; // namespace entityEnum