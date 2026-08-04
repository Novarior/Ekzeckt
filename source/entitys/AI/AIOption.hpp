#ifndef AI_OPTIONS_HPP
#define AI_OPTIONS_HPP

#include "../entity.hpp"
#include "../../core/math/mymath.hpp"

enum class FollowTargetEnum {
	Point, // Следовать за точкой
	Target, // Следовать за объектом
	COUNT
};

enum class StateTODO {
	Idle,  // Ничего не делать
	Wait,  // Ожидание следующего действия
	Moving, // Движение к цели или точке
	Patrol, // Патрулирование
	Attack, // Атака цели
	COUNT
};

class AIOption {
protected:
	Entity* _ai_self;
	Entity* _ai_target;

	FollowTargetEnum _ai_follow_target;
	StateTODO _ai_state;

	sf::CircleShape _ai_rad;
	float _ai_cooldown_attack = 0.f;
	float _ai_cooldown_attack_max = 1.f;

	float _ai_time_for_action = 0.f;
	float _ai_time_for_action_max = 2.5f;

public:
	AIOption(Entity* self, Entity* target, float rad_radius = 25.f)
		: _ai_self(self), _ai_target(target), _ai_follow_target(FollowTargetEnum::Point), _ai_state(StateTODO::Idle) {
		_ai_rad = sf::CircleShape(rad_radius);
		_ai_rad.setOrigin({rad_radius, rad_radius});
	}

	virtual ~AIOption() {}

	// Универсальный метод обновления таймера
	inline void updateTimer(float& timer, float max_value, const float& delta_time) {
		if (timer < max_value)
			timer += delta_time;
	}

	// Проверка, истёк ли таймер
	inline bool isTimerReady(float& timer, float max_value) {
		if (timer >= max_value) {
			timer = 0.f;
			return true;
		}
		return false;
	}

	// Обновление времени для действия
	inline void updateTimeForAction(const float& delta_time) {
		updateTimer(_ai_time_for_action, _ai_time_for_action_max, delta_time);
	}

	// Проверка готовности к следующему действию
	inline bool isReadyForAction() const {
		return _ai_time_for_action >= _ai_time_for_action_max;
	}

	// Сброс времени для действия
	inline void resetTimeForAction() {
		_ai_time_for_action = 0.f;
	}

	// Обновление кулдауна атаки
	inline void updateCooldown(const float& delta_time) {
		updateTimer(_ai_cooldown_attack, _ai_cooldown_attack_max, delta_time);
	}

	// Проверка, истёк ли кулдаун
	inline bool isCooldownOver() const {
		return _ai_cooldown_attack >= _ai_cooldown_attack_max;
	}

	// Сброс кулдауна атаки
	inline void resetCooldown() {
		_ai_cooldown_attack = 0.f;
	}

	// Чисто виртуальный метод для реализации в дочерних классах
	virtual void update(const float& delta_time) = 0;
};

#endif