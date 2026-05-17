#ifndef ITEM_GOLD_COIN
#define ITEM_GOLD_COIN
#include "../Item.hpp"

namespace Items {
	class GoldCoin : public Item {
	public:
		GoldCoin(unsigned int gridSizeI) : Item(8, "Gold Coin", true, true, false, 1, 999, 0, 0, { 1, 0, 0 }) {
			this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
			this->m_item_shape.setTexture(&TextureManager::getTexture("items_gold_coin"));
		}
		virtual ~GoldCoin() {}

		void useItem() override {
			std::cout << this->iINFO.m_name << " is not usable directly" << std::endl;
			Logger::logStatic("You can use " + this->iINFO.m_name + " for trading", "CORE->ITEM", logType::LINFO);
		}

		void update(const float& delta_time, sf::Vector2i mouse_pos) {}
	};
} // namespace Items
#endif /* ITEM_GOLD_COIN */