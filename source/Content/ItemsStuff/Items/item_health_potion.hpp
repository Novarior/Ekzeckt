#ifndef ITEM_HEALTH_POTION
#define ITEM_HEALTH_POTION
#include "../Item.hpp"

namespace Items {
	class HealthPotion : public Item {
	public:
		HealthPotion(unsigned int gridSizeI) : Item(7, "Health Potion", true, true, true, 1, 5, 0, 0, { 0, 2, 0 }) {
			this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
			this->m_item_shape.setTexture(&TextureManager::getTexture("items_health_potion"));
		}
		virtual ~HealthPotion() {}

		void useItem() override {
			std::cout << "You drank a " << this->iINFO.m_name << std::endl;
			Logger::logStatic("You drank a " + this->iINFO.m_name + " and restored 50 health", "CORE->ITEM", logType::LINFO);

			// Remove one potion from stack
			removeAmount(1);
		}

		void update(const float& delta_time, sf::Vector2i mouse_pos) {}
	};
} // namespace Items
#endif /* ITEM_HEALTH_POTION */