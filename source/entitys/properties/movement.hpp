#ifndef CPP_MovementComponent_HPP
#define CPP_MovementComponent_HPP

#include "../../core/header.h"

enum MovamentState
{
  NONe = -1,
  Idle,
  Walk,
  Fall,
  Shift
};

#define MAXSPEEDENTITY = 0x3ff;
class MovementComponent
{
private:
  sf::Sprite &sprite;

  float acceleration;
  float deceleration;
  float maxVelocity;
  sf::Vector2f velocity;
  sf::Vector2f directons;
  bool onGround;
  MovamentState mov_state;

  const float gravity = 9.2f; // m/s^2 like in real life
  const float maxFallSpeed = 9.2f;

public:
  MovementComponent(sf::Sprite &sprite, const float acceleration, const float deceleration, const float maxVelocity);
  ~MovementComponent();

  // Accessors
  const float &getMaxVelocity() const;
  const sf::Vector2f &getVelocity() const;
  const sf::Vector2f &getDirectionVec() const;

  // Functions
  void stopVelocity();
  void stopVelocityX();
  void stopVelocityY();

  void move(const float &dir_x, const float &dir_y, const float &delta_time);
  float handleVelocity(float velocity, float deceleration, float maxVelocity, float delta_time);
  void update(const float &dt);
};
#endif