#include "movement.hpp"

MovementComponent::MovementComponent(sf::Sprite &sprite, const float acceleration, const float deceleration, const float maxVelocity)
  : sprite(sprite), acceleration(acceleration), deceleration(deceleration), maxVelocity(maxVelocity), directons(0.f, 0.f), velocity(0.f, 0.f), onGround(false), mov_state(MovamentState::Idle)
{
}

MovementComponent::~MovementComponent() {}

// Accessors
const float &MovementComponent::getMaxVelocity() const { return this->maxVelocity; }

const sf::Vector2f &MovementComponent::getVelocity() const { return this->velocity; }

// Functions
void MovementComponent::stopVelocity()
{ /* Resets the velocity to 0.*/
  this->velocity.x = 0.f;
  this->velocity.y = 0.f;
}

void MovementComponent::stopVelocityX() { this->velocity.x = 0.f; }

void MovementComponent::stopVelocityY() { this->velocity.y = 0.f; }

void MovementComponent::move(const float &dir_x, const float &dir_y, const float &delta_time)
{
  /* Accelerating a sprite until it reaches the max velocity. */
  /* Accelerating a sprite until it reaches the max velocity. */
  float scaled_dir_x = dir_x;
  float scaled_dir_y = dir_y;

  if (dir_x != 0 && dir_y != 0)
  {
    if (scaled_dir_x > 0.1f)
      scaled_dir_x = 1.f;
    else if (scaled_dir_x < -0.1f)
      scaled_dir_x = -1.f;

    if (scaled_dir_y > 0.1f)
      scaled_dir_y = 1.f;
    else if (scaled_dir_y < -0.1f)
      scaled_dir_y = -1.f;
  }

  this->velocity.x += this->acceleration * delta_time * scaled_dir_x;
  this->velocity.y += this->acceleration * delta_time * scaled_dir_y;

  this->directons.x = scaled_dir_x;
  this->directons.y = scaled_dir_y;
}

void MovementComponent::update(const float &delta_time)
{
  // Decelerates the sprite and controls the maximum velocity.
  this->velocity.x = this->handleVelocity(this->velocity.x, this->deceleration, this->maxVelocity, delta_time);
  this->velocity.y = this->handleVelocity(this->velocity.y, this->deceleration, this->maxVelocity, delta_time);
  // Final move
  this->sprite.move({this->velocity.x, this->velocity.y}); // Uses velocity
}

const sf::Vector2f &MovementComponent::getDirectionVec() const { return this->directons; }

float MovementComponent::handleVelocity(float velocity, float deceleration, float maxVelocity, float delta_time)
{ // BUG FIX: velocity is stop if they are not in the range of maxVelocity (-1.f, 1.f)
  // if velocity is less than 1.f, it will be set to 0.f
  // if velocity is greater than -1.f, it will be set to 0.f
  // fix, write logic for working with different ranges of velocity (0.231f & 0.521f)

  if (velocity > 0.f)
  { // positive range velocity
    velocity -= deceleration * delta_time;
    if (velocity < 0.f)
      velocity = 0.f;
    if (velocity > maxVelocity)
      velocity = maxVelocity;
  }
  else if (velocity < 0.f)
  { // negative range velocity
    velocity += deceleration * delta_time;
    if (velocity > 0.f)
      velocity = 0.f;
    if (velocity < -maxVelocity)
      velocity = -maxVelocity;
  }
  return velocity;
}