#ifndef AI_ATTACK_HPP
#define AI_ATTACK_HPP

#include "AIOption.hpp"

class AIAttack: public AIOption {
private:
	unsigned short attackTarget;

public:
	AIAttack(Entity* self, Entity* entity);
	~AIAttack();

	void update(const float& delta_time);
};

#endif
