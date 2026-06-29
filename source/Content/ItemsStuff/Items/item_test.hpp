#ifndef ITEM_TEST
#define ITEM_TEST
#include "../Item.hpp"

namespace Items {
class TestItem: public Item {
public:
	TestItem(unsigned int gridSizeI): Item(99, "Test Item", true, true, false, 1, 64, 0, 0, {0, 0, 5}, TextureManager::getTexture()) {}
	virtual ~TestItem() {}

	// empty todo
	void useItem() override {
		// nothing
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
}; // namespace Items
#endif /* ITEM_TEST */
