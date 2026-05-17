#ifndef ITEM_TEST
#define ITEM_TEST
#include "../Item.hpp"

namespace Items {
class TestItem: public Item {
public:
	TestItem(unsigned int gridSizeI): Item(99, "Test Item", true, true, false, 1, 64, 0, 0, {0, 0, 5}) {
		this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
		// Используем для теста любую доступную текстуру
		this->m_item_shape.setTexture(&TextureManager::getTexture(TextureID::TEXTURE_NULL));

		// Устанавливаем цвет для отличия от обычного камня
		this->m_item_shape.setFillColor(sf::Color(255, 200, 200, 255)); // Светло-розовый
	}

	virtual ~TestItem() {}

	// Пустая реализация использования предмета
	void useItem() override {
	  // Ничего не делаем
	}

	// Пустая реализация обновления
	void update(const float& delta_time, sf::Vector2i mouse_pos) {}
};
}; // namespace Items
#endif /* ITEM_TEST */
