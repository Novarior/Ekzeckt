#ifndef ITEM_STONE
#define ITEM_STONE
#include "../Item.hpp"

namespace Items {
class Stone : public Item {
public:
  Stone(unsigned int gridSizeI): Item(1, "Stone", true, true, false, 1, 99, 0, 0, {0, 0, 1}) {
    this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
    this->m_item_shape.setTexture(&TextureManager::getTexture(TextureID::ITEMS_STONE));
    // Остальная инициализация конкретных свойств для Stone
  }
  virtual ~Stone() {}

  void useItem() override {
    // print to console that you used this item
    std::cout << this->iINFO.m_name << " is not usable" << std::endl;
  }

  void update(const float &delta_time, sf::Vector2i mouse_pos) {}
};
};     // namespace Items
#endif /* ITEM_STONE */
