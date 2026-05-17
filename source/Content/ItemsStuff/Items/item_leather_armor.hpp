#ifndef ITEM_LEATHER_ARMOR
#define ITEM_LEATHER_ARMOR
#include "../Item.hpp"

namespace Items{
class LeatherArmor: public Item{
public:
	LeatherArmor(unsigned int gridSizeI): Item(6, "Leather Armor", true, false, true, 1, 1, 50, 50, {0, 3, 0}){
		this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
		this->m_item_shape.setTexture(&TextureManager::getTexture("items_leather_armor"));
	}
	virtual ~LeatherArmor(){}

	void useItem() override{
		std::cout << "You equipped " << this->iINFO.m_name << std::endl;
		Logger::logStatic("You equipped " + this->iINFO.m_name, "CORE->ITEM", logType::LINFO);
		// Here would be logic to equip armor and provide defense
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos){}
};
};     // namespace Items
#endif /* ITEM_LEATHER_ARMOR */