#ifndef ITEM_POISON_SMALL_REGENERATION
#define ITEM_POISON_SMALL_REGENERATION
#include "../Item.hpp"

namespace Items {
class PoisonSmallRegeneration: public Item {
private:
public:
	PoisonSmallRegeneration():
		Item(2, "Poison of Regeneration", true, true, false, 1, 2, 0, 0, {0, 1, 25}, TextureManager::getTexture("items_potion_small_regeneration")) {}
	virtual ~PoisonSmallRegeneration() {}

	void useItem() override {
		removeAmount(1);
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
} // namespace Items
#endif /* ITEM_POISON_SMALL_REGENERATION */
