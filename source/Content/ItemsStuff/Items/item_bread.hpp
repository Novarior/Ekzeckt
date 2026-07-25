#ifndef ITEM_BREAD
#define ITEM_BREAD
#include "../Item.hpp"

namespace Items {
class Bread: public Item {
public:
	Bread(): Item(5, "Bread", true, true, true, 1, 10, 0, 0, {0, 1, 0}, TextureManager::getTexture("items_bread")) {}
	virtual ~Bread() {}

	void useItem() override {
		std::cout << "You eat " << iData.m_name << std::endl;
		Logger::logStatic("You ate " + iData.m_name + " and restored some health", "CORE->ITEM", logType::LINFO);

		// Remove one bread from stack
		removeAmount(1);
	}

	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
};     // namespace Items
#endif /* ITEM_BREAD */
