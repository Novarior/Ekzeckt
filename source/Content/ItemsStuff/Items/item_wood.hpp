#ifndef ITEM_WOOD
#define ITEM_WOOD
#include "../Item.hpp"

namespace Items {
class Wood: public Item {
public:
	Wood(unsigned int gridSizeI): Item(3, "Wood", true, true, false, 1, 99, 0, 0, {0, 0, 1}) {
		this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
		this->m_item_shape.setTexture(&TextureManager::getTexture(TextureID::ITEMS_WOOD));
	}
	virtual ~Wood() {}

	void useItem() override {
		std::cout << this->iINFO.m_name << " is not usable" << std::endl;
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};     // namespace Items
#endif /* ITEM_WOOD */
