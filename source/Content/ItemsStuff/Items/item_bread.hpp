#ifndef ITEM_BREAD
#define ITEM_BREAD
#include "../Item.hpp"

namespace Items {
	class Bread : public Item {
	public:
		Bread(unsigned int gridSizeI) : Item(5, "Bread", true, true, true, 1, 10, 0, 0, { 0, 1, 0 }) {
			this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
			this->m_item_shape.setTexture(&TextureManager::getTexture("items_bread"));
		}
		virtual ~Bread() {}

		void useItem() override {
			std::cout << "You ate " << this->iINFO.m_name << std::endl;
			Logger::logStatic("You ate " + this->iINFO.m_name + " and restored some health", "CORE->ITEM", logType::LINFO);

			// Remove one bread from stack
			removeAmount(1);
		}

		void update(const float& delta_time, sf::Vector2i mouse_pos) {}
	};
};     // namespace Items
#endif /* ITEM_BREAD */
