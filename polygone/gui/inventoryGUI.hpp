#ifndef INVENTORYGUI
#define INVENTORYGUI

#define INVENTORY_SIZE_X 8
#define INVENTORY_SIZE_Y 6
#include "../Header.h"
//#include "../../Content/ItemsStuff/Inventory.hpp"
//#include "../components/button.hpp"
#include "checkbox.hpp"
#include "progressBar.hpp"
//#include "../tools/textbox.hpp"
#include <vector>

namespace gui {
class InventoryGUI: public sf::Drawable {
private:
	struct InventorySlot {
		sf::RectangleShape mBackShape;
		void* mItem;
		bool mBloced;
	} m_slot;

	std::weak_ptr<void> m_inventory;

	// Состояние инвентаря
	bool isOpen;

	// Фон инвентаря
	sf::RectangleShape m_background, m_headerBackground;

	// Ячейки инвентаря (сетка)
	// std::vector<std::vector<gui::Button *>> m_slots;
	//std::vector<sf::RectangleShape> mInventoryShape;
	

	//// Информация о вместимости
	//sf::Text m_capacityText;
	//gui::ProgressBar m_weightBar;

	//// Информация о валюте
	//sf::Text m_goldText;
	//sf::Text m_silverText;
	//sf::Text m_copperText;
	//sf::Sprite m_goldIcon;
	//sf::Sprite m_silverIcon;
	//sf::Sprite m_copperIcon;

	// Кнопка удаления предметов
	//  gui::Button *m_deleteButton;

	  // Выбранный предмет и его описание

	// gui::TextBox *m_itemDescription;

	// Шрифт для текста

	// Инициализация компонентов
	void initBackground(sf::Vector2f screenSize);
	void initHeader();
	//void initTabs();
	//void initSlots(unsigned int rows, unsigned int cols, float slotSize);
	//void initCapacityLINFO();
	//void initCurrencyLINFO();

public:
	InventoryGUI(sf::Vector2f screenSize, sf::Font& font, unsigned int characterSize = 16);
	virtual ~InventoryGUI();

	//// Основные методы
	//void update(const float& dt, const sf::Vector2i& mousePos);
	//void handleEvent(const sf::Event& event, const sf::Vector2i& mousePos);

	// Управление видимостью
	//bool isVisible() const;
	//void setVisible(bool visible);
	//void toggleVisible();

	// Управление вкладками
//	void setActiveTab(InventoryTab tab);
	//InventoryTab getActiveTab() const;

	//// Управление предметами
	//void refreshItems();
	//bool isSlotLocked(int slotIndex) const;
	//void lockSlot(int slotIndex, bool locked);

	// Обновление позиций всех предметов в инвентаре
	//void updateItemPosGUI();

	// Получение информации о слотах
	//const std::vector<std::vector<gui::Button *>> &getSlots() const
	//{
	//    return m_slots;
	//}
	//sf::Vector2f getSlotPosition(int slotIndex) const;
	//sf::Vector2f getSlotSize() const {
	//	return m_slots[0][0]->getSize();
	//} // Возвращаем фиксированный размер слота

	//// Обработка действий
	//void handleSlotClick(int slotIndex);
	//void handleDeleteClick();
	//void handleTabClick(InventoryTab tab);
	//void handleAutoArrangeToggle(bool checked);

	// Отрисовка
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

} // namespace GUI

#endif /* INVENTORYGUI */
