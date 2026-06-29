#ifndef ITEM_POISON_SMALL_REGENERATION
#define ITEM_POISON_SMALL_REGENERATION
#include "../Item.hpp"

namespace Items {
class PoisonSmallRegeneration: public Item {
private:
public:
	PoisonSmallRegeneration(unsigned int gridSizeI):
		Item(2, "Poison of Regeneration", true, true, false, 1, 2, 0, 0, {0, 1, 25}, TextureManager::getTexture("items_potion_small_regeneration")) {}
	virtual ~PoisonSmallRegeneration() {}

	void useItem() override {
		// print to console that you used this item
		std::cout << "You used " << iData.m_name << std::endl;
		// add regeneration to player
		// remove item from inventory
		// if quantity == 0 remove item from inventory

		removeAmount(1);
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
} // namespace Items
#endif /* ITEM_POISON_SMALL_REGENERATION */
