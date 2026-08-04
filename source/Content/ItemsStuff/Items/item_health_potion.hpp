#ifndef ITEM_HEALTH_POTION
#define ITEM_HEALTH_POTION
#include "../Item.hpp"

namespace Items {
class HealthPotion: public Item {
public:
	HealthPotion(): Item(7, "Health Potion", true, true, true, 1, 5, 0, 0, {0, 2, 0}, TextureManager::getTexture("items_health_potion")) {}
	virtual ~HealthPotion() {}

	void useItem() override {

		removeAmount(1);
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
} // namespace Items
#endif /* ITEM_HEALTH_POTION */