#ifndef item_iron_sword_hpp
#define item_iron_sword_hpp
#include "../Item.hpp"

namespace Items {
class IronSword : public Item {
public:
  IronSword(unsigned int gridSizeI)
      : Item(4, "Iron Sword", true, false, true, 1, 1, 100, 100, {0, 5, 0}) {
    this->m_item_shape.setSize(sf::Vector2f(gridSizeI, gridSizeI));
    this->m_item_shape.setTexture(
        &TextureManager::getTexture(TextureID::ITEMS_IRON_SWORD));
  }
  virtual ~IronSword() {}

  void useItem() override {
    std::cout << "You swing your " << this->iInfo.m_name << std::endl;
    // Reduce durability by 1
    iData.durability = std::max(0, iData.durability - 1);
    Logger::logStatic("You used " + this->iInfo.m_name, "CORE->ITEM",
                      logType::INFO);
  }

  void update(const float &delta_time, sf::Vector2i mouse_pos) {}
};
} // namespace Items
#endif /* item_iron_sword_hpp */