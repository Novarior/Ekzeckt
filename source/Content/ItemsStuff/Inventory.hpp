#ifndef INVENTORY
#define INVENTORY

#include "Coins.hpp"
#include "Items/ItemRegister.hpp"

namespace GUI {
class InventoryGUI;
}

class Inventory {
public:
	Inventory(unsigned int rows, unsigned int cols);
	virtual ~Inventory();

	// Основные функции
	unsigned int getCurrentCellID(sf::Vector2i mouse_pos) const;
	void update(sf::Vector2i mouse_pos);

	// Функции для работы с предметами
	bool addItem(std::shared_ptr<Item> _item);
	//  bool removeItem(std::shared_ptr<Item> _item);
	bool removeItemByID(unsigned int _id);
	void clearInventory();

	std::shared_ptr<Item> getItem(unsigned int _id) const;
	std::shared_ptr<Item> getItemFromSlot(unsigned int slot) const;

	// get cells

	// get inventory array
	const std::vector<std::vector<std::shared_ptr<Item>>>&
		getInventoryArray() const {
		return InventoryArray;
	}

	// Управление открытием/закрытием инвентаря
	void openInventory() { isOpened = true; }
	void closeInventory() { isOpened = false; }
	void toggleInventory() { isOpened = !isOpened; }
	const bool isInventoryOpened() const { return isOpened; }

	// Получение состояния
	int getTotalSlots() const;
	inline const Coins& getCoins() { return m_Coins; }

	// Ссылка на GUI инвентаря для позиционирования предметов
	void setGUI(std::shared_ptr<GUI::InventoryGUI> gui) { m_gui = gui; }
	std::weak_ptr<GUI::InventoryGUI> getGUI() const { return m_gui; }

private:
  // Открыт ли инвентарь
	bool isOpened;
	// Слоты для предметов
	std::vector<std::vector<std::shared_ptr<Item>>> InventoryArray;
	// Монеты
	Coins m_Coins;
	// Ссылка на GUI инвентаря
	std::weak_ptr<GUI::InventoryGUI> m_gui;
};

#endif /* INVENTORY */
