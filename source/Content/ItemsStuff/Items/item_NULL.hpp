#ifndef ITEM_NULL
#define ITEM_NULL
#include "../Item.hpp"

namespace Items {
class Item_NULL: public Item {
public:
	Item_NULL(): Item(0, "NULL", false, false, false, 0, 0, 0, 0, {0, 0, 0}, TextureManager::getTexture()) {}
	virtual ~Item_NULL() {}

	void useItem() override {}
	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
} // namespace Items
#endif /* ITEM_NULL */
