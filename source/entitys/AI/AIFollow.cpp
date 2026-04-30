#include "AIFollow.hpp"

AIFollow::AIFollow(Entity &self, Entity &target, int stopDistance)
    : AIOption(self, target)
{
}

AIFollow::~AIFollow()
{
}

void AIFollow::update(const float &delta_time)
{
    sf::Vector2f moveVec;
    moveVec.x = _ai_target.e_getPosition().x - _ai_self.e_getPosition().x;
    moveVec.y = _ai_target.e_getPosition().y - _ai_self.e_getPosition().y;

    float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

    if (moveVec.x != 0 && moveVec.y != 0)
        moveVec /= vecLength;

    if (vecLength > 0 && vecLength < 500.f)
        _ai_self.e_move(moveVec.x, moveVec.y, delta_time);
}

bool AIFollow::isCloseEnough()
{
    float distanceSquared = pow(_ai_target.e_getPosition().x - _ai_self.e_getPosition().x, 2) + pow(_ai_target.e_getPosition().y - _ai_self.e_getPosition().y, 2);
    return distanceSquared <= pow(_ai_stopDistance, 2);
}