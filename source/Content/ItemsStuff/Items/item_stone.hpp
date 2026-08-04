#ifndef ITEM_STONE
#define ITEM_STONE
#include "../Item.hpp"

namespace Items {
class Stone: public Item {
public:
	Stone(): Item(1, "Stone", true, true, false, 1, 99, 0, 0, {0, 0, 1}, TextureManager::getTexture(TextureID::ITEMS_STONE)) {}
	virtual ~Stone() {}

	void useItem() override {
	
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};   // namespace Items
#endif /* ITEM_STONE */
