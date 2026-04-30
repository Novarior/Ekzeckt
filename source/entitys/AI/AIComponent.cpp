#include "AIComponent.hpp"
#include "AIWander.hpp"

AIComponent::AIComponent(Entity &self, Entity &target)
    : _self(self), _target(target)
{
    _follow = nullptr;
    _attack = nullptr;
    _wander = nullptr;
}

AIComponent::~AIComponent() {}

void AIComponent::update(const float &delta_time)
{
    // if (_follow != nullptr)
    //     _follow->update(delta_time);
    if (_attack != nullptr)
        _attack->update(delta_time);
    if (_wander != nullptr)
        _wander->update(delta_time);
}

void AIComponent::create_follow(int stopDistance) { _follow = std::make_unique<AIFollow>(_self, _target, stopDistance); }
void AIComponent::create_attack() { _attack = std::make_unique<AIAttack>(_self, _target); }
void AIComponent::create_wander() { _wander = std::make_unique<AIWander>(_self, 20); }

void AIComponent::render(sf::RenderTarget &target)
{
    if (_wander != nullptr)
        _wander->render(target);
}