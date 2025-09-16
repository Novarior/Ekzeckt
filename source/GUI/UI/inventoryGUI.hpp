#ifndef INVENTORYGUI
#define INVENTORYGUI

#include "../../Content/ItemsStuff/Inventory.hpp"
#include "../components/button.hpp"
#include "../components/checkbox.hpp"
#include "../components/progressBar.hpp"
#include "../tools/textbox.hpp"
#include <vector>

namespace GUI {

enum InventoryTab { TAB_INVENTORY = 0, TAB_PEARL, TAB_COUNT };

class InventoryGUI : public sf::Drawable {
private:
  // Указатель на инвентарь
  std::weak_ptr<Inventory> m_inventory;

  // Состояние инвентаря
  bool m_visible;
  InventoryTab m_currentTab;

  // Фон инвентаря
  sf::RectangleShape m_background;
  sf::RectangleShape m_headerBackground;

  // Иконка инвентаря
  sf::Texture m_iconTexture;
  sf::Sprite m_icon;

  // Кнопки управления
  gui::Button *m_closeButton;
  gui::Button *m_helpButton;
  gui::Button *m_minimizeButton;

  // Вкладки инвентаря
  std::vector<gui::Button *> m_tabs;

  // Опция автоматического размещения
  gui::CheckBox *m_autoArrangeCheckbox;
  sf::Text m_autoArrangeText;

  // Ячейки инвентаря (сетка)
  std::vector<std::vector<gui::Button *>> m_slots;
  std::vector<bool> m_slotLocked; // Заблокированы ли ячейки

  // Информация о вместимости
  sf::Text m_capacityText;
  gui::ProgressBar *m_weightBar;

  // Информация о валюте
  sf::Text m_goldText;
  sf::Text m_silverText;
  sf::Text m_copperText;
  sf::Sprite m_goldIcon;
  sf::Sprite m_silverIcon;
  sf::Sprite m_copperIcon;

  // Кнопка удаления предметов
  gui::Button *m_deleteButton;

  // Выбранный предмет и его описание
  int m_selectedSlot;
  gui::TextBox *m_itemDescription;

  // Шрифт для текста
  sf::Font &m_font;

  // Инициализация компонентов
  void initBackground(sf::Vector2f screenSize);
  void initHeader();
  void initTabs();
  void initSlots(unsigned int rows, unsigned int cols, float slotSize);
  void initCapacityInfo();
  void initCurrencyInfo();

public:
  InventoryGUI(std::weak_ptr<Inventory> inventory, sf::Vector2f screenSize,
               sf::Font &font, float slotSize = 50.f,
               unsigned int characterSize = 16);
  ~InventoryGUI();

  // Основные методы
  void update(const float &dt, const sf::Vector2i &mousePos);
  void handleEvent(const sf::Event &event, const sf::Vector2i &mousePos);

  // Управление видимостью
  bool isVisible() const;
  void setVisible(bool visible);
  void toggleVisible();

  // Управление вкладками
  void setActiveTab(InventoryTab tab);
  InventoryTab getActiveTab() const;

  // Управление предметами
  void refreshItems();
  bool isSlotLocked(int slotIndex) const;
  void lockSlot(int slotIndex, bool locked);

  // Обновление позиций всех предметов в инвентаре
  void updateItemPosGUI();

  // Получение информации о слотах
  const std::vector<std::vector<gui::Button *>> &getSlots() const {
    return m_slots;
  }
  sf::Vector2f getSlotPosition(int slotIndex) const;
  sf::Vector2f getSlotSize() const {
    return m_slots[0][0]->getSize();
  } // Возвращаем фиксированный размер слота

  // Обработка действий
  void handleSlotClick(int slotIndex);
  void handleDeleteClick();
  void handleTabClick(InventoryTab tab);
  void handleAutoArrangeToggle(bool checked);

  // Отрисовка
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
};

} // namespace GUI

#endif /* INVENTORYGUI */
