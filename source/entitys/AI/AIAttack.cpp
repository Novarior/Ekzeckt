#include "AIAttack.hpp"

AIAttack::AIAttack(Entity &self, Entity &target)
    : AIOption(self, target)
{
}

AIAttack::~AIAttack() {}

void AIAttack::update(const float &delta_time)
{
    updateCooldown(delta_time);

    _ai_rad.setPosition(_ai_self.e_getPosition());
    if (isCooldownOver())
        if (_ai_rad.getGlobalBounds().findIntersection(_ai_target.getGlobalBounds()))
            _ai_target.e_takeDamage(_ai_self.getAttributes()->getAttributes().damage);
}