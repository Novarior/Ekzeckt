#ifndef ITEM_WOOD
#define ITEM_WOOD
#include "../Item.hpp"

namespace Items {
class Wood: public Item {
public:
	Wood(): Item(3, "Wood", true, true, false, 1, 99, 0, 0, {0, 0, 1}, TextureManager::getTexture(TextureID::ITEMS_WOOD)) {}
	virtual ~Wood() {}

	void useItem() override {
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};   // namespace Items
#endif /* ITEM_WOOD */
