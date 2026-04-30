#ifndef AI_WANDER_HPP
#define AI_WANDER_HPP

#include "AIOption.hpp"

class AIWander : public AIOption
{
private:
    sf::Vector2f _direction;
    sf::Vector2f _center;
    float _distance;
    float _radius;

    // debuging

    sf::VertexArray _line;

public:
    AIWander(Entity &self, float radius);
    ~AIWander();

    void update(const float &delta_time);

    void render(sf::RenderTarget &target) { target.draw(_line); }
};
#endif