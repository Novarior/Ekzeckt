#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

#include "../entity.hpp"
#include "AIAttack.hpp"
#include "AIFollow.hpp"
#include "AIWander.hpp"

class AIComponent {
private:
	Entity* _target;
	Entity* _self;

	std::unique_ptr<AIFollow> _follow;
	std::unique_ptr<AIAttack> _attack;
	std::unique_ptr<AIWander> _wander;

public:
	AIComponent(Entity* self, Entity* target);
	~AIComponent();

	void create_follow(int stopDistance);
	void create_attack();
	void create_wander();

	void update(const float& delta_time);
	void render(sf::RenderTarget& target);
};
#endif