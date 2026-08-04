#ifndef ITEM_BREAD
#define ITEM_BREAD
#include "../Item.hpp"

namespace Items {
class Bread: public Item {
public:
	Bread(): Item(5, "Bread", true, true, true, 1, 10, 0, 0, {0, 1, 0}, TextureManager::getTexture("items_bread")) {}
	virtual ~Bread() {}

	void useItem() override {
		removeAmount(1);
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};   // namespace Items
#endif /* ITEM_BREAD */
