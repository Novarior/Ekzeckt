#include "Inventory.hpp"
#include "../../GUI/UI/inventoryGUI.hpp"
#include "Items/ItemRegister.hpp"
#include "itemtextures.hpp"
#include <memory>

// Очистка инвентаря
void Inventory::clearInventory() {
  // if not nullptr
  if (InventoryArray[0][0] == nullptr)
    return; // Если инвентарь пуст, ничего не делаем

  for (auto &row : InventoryArray)
    for (auto &item : row) {
      item.reset(); // Умное указание освободит память
    }
}

// Конструктор инвентаря
Inventory::Inventory(unsigned int rows, unsigned int cols)
    : isOpened(false), m_Coins(0, 0, 0), m_gui() {
  InventoryArray.resize(rows,
                        std::vector<std::shared_ptr<Item>>(cols, nullptr));
}

/// Получаем ID текущей ячейки по позиции мыши
/// @param mouse_pos Позиция мыши в окне
/// @return ID ячейки или -1, если мышь не в пределах инвентаря
/// @note ID ячейки - это номер ячейки в инвентаре, начиная с 0
/// @note Если мышь не в пределах инвентаря, возвращаем -1
unsigned int Inventory::getCurrentCellID(sf::Vector2i mouse_pos) const {
  // // Получаем размеры ячеек
  // // Предполагаем, что все ячейки одного размера
  // float cell_size = CellsInventory[0][0].getSize().x;

  // // Проверяем, что позиция мыши находится в пределах инвентаря
  // if (mouse_pos.x < inventoryPosition.x || mouse_pos.y < inventoryPosition.y
  // ||
  //     mouse_pos.x > inventoryPosition.x + inventoryPosition.x ||
  //     mouse_pos.y > inventoryPosition.y + inventoryPosition.y) {
  //   return -1; // Если мышь не внутри инвентаря
  // }

  // // Рассчитываем индексы строки и столбца в сетке инвентаря
  // unsigned int row = (mouse_pos.x - inventoryPosition.x) / cell_size;
  // unsigned int col = (mouse_pos.y - inventoryPosition.y) / cell_size;

  // // Проверяем, что индексы находятся в пределах размеров инвентаря
  // if (row >= CellsInventory.size() || col >= CellsInventory[0].size()) {
  //   return -1; // Если координаты вне допустимого диапазона
  // }

  // // Возвращаем идентификатор ячейки
  // return CellsInventory[row][col].getIDCell();
  return 0;
}

// Деструктор инвентаря
Inventory::~Inventory() { clearInventory(); }

bool Inventory::addItem(std::shared_ptr<Item> item) {
  if (!item)
    return false;

  // Если предмет можно складывать
  if (item->isStackable())
    for (auto &row : InventoryArray)
      for (auto &slot : row)
        if (slot && slot->getID() == item->getID() &&
            slot->getAmount() < slot->getMaxAmount()) {
          slot->addAmount(item->getAmount());

          // Обновляем позиции всех предметов через GUI
          if (auto gui = m_gui.lock()) {
            gui->updateItemPosGUI();
          }

          return true;
        }

  // Если предмет не складывается, ищем пустой слот
  for (size_t row = 0; row < InventoryArray.size(); ++row)
    for (size_t col = 0; col < InventoryArray[row].size(); ++col)
      if (!InventoryArray[row][col]) {
        InventoryArray[row][col] = item;

        // Обновляем позиции всех предметов через GUI
        if (auto gui = m_gui.lock()) {
          gui->updateItemPosGUI();
        }

        return true;
      }

  return false; // Инвентарь заполнен
}

bool Inventory::removeItemByID(unsigned int ID) {
  for (auto &row : InventoryArray) {
    auto it =
        std::find_if(row.begin(), row.end(), [ID](std::shared_ptr<Item> slot) {
          return slot && slot->getID() == ID;
        });

    if (it != row.end()) {
      *it = nullptr; // Освобождение слота

      // Обновляем позиции всех предметов через GUI
      if (auto gui = m_gui.lock()) {
        gui->updateItemPosGUI();
      }

      return true;
    }
  }
  return false; // Предмет с таким ID не найден
}

/// Получаем предмет по ID предмета
std::shared_ptr<Item> Inventory::getItem(unsigned int ID) const {
  for (const auto &row : InventoryArray)
    for (const auto &item : row)
      if (item && item->getID() == ID)
        return item;
  // Предмет не найден
  // Возвращаем предмет затычку
  return ItemRegistry::getItem(0); // Предмет не найден
}

std::shared_ptr<Item> Inventory::getItemFromSlot(unsigned int slot) const {
  // Проверяем, что инвентарь не пуст
  if (InventoryArray.empty() || InventoryArray[0].empty()) {
    Logger::logStatic("ERROR::INVENTORY::GET_ITEM_FROM_SLOT::EMPTY_INVENTORY",
                      "Inventory", logType::ERROR);
    return ItemRegistry::getItem(0); // Возвращаем предмет-затычку
  }

  unsigned int rows = InventoryArray.size();
  unsigned int cols = InventoryArray[0].size();

  // Проверяем, что слот находится в пределах инвентаря
  if (slot >= rows * cols) {
    Logger::logStatic(
        "ERROR::INVENTORY::GET_ITEM_FROM_SLOT::OUT_OF_BOUNDS_SLOT: " +
            std::to_string(slot),
        "Inventory", logType::WARNING);
    return ItemRegistry::getItem(0); // Возвращаем предмет-затычку
  }

  // Возвращаем предмет из указанного слота или предмет-затычку, если слот пуст
  auto item = InventoryArray[slot / cols][slot % cols];
  return item ? item : ItemRegistry::getItem(0);
}

int Inventory::getTotalSlots() const {
  return static_cast<int>(InventoryArray.size() * InventoryArray[0].size());
}

// Обновление инвентаря
void Inventory::update(sf::Vector2i mouse_pos) {}
