#ifndef ITEM_LEATHER_ARMOR
#define ITEM_LEATHER_ARMOR
#include "../Item.hpp"

namespace Items {
class LeatherArmor: public Item {
public:
	LeatherArmor(): Item(6, "Leather Armor", true, false, true, 1, 1, 50, 50, {0, 3, 0}, TextureManager::getTexture("items_leather_armor")) {}
	virtual ~LeatherArmor() {}

	void useItem() override {
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};   // namespace Items
#endif /* ITEM_LEATHER_ARMOR */