#include "inventoryGUI.hpp"
#include "../../core/header.h"

// Инициализация фона инвентаря
void GUI::InventoryGUI::initBackground(sf::Vector2f screenSize) {
  // Размер инвентаря - 65% от ширины и 75% от высоты экрана
  sf::Vector2f size(screenSize.x * 0.65f, screenSize.y * 0.75f);

  // Позиция - центр экрана
  sf::Vector2f position((screenSize.x - size.x) / 2.f,
                        (screenSize.y - size.y) / 2.f);

  // Настройка основного фона
  m_background.setSize(size);
  m_background.setPosition(position);
  m_background.setFillColor(
      sf::Color(30, 30, 35, 230)); // Темный полупрозрачный фон
  m_background.setOutlineThickness(1.f);
  m_background.setOutlineColor(sf::Color(100, 100, 100));

  // Настройка фона заголовка
  m_headerBackground.setSize(sf::Vector2f(size.x, 40.f));
  m_headerBackground.setPosition(position);
  m_headerBackground.setFillColor(
      sf::Color(40, 40, 45, 255)); // Чуть светлее основного фона
}

// Инициализация заголовка инвентаря
void GUI::InventoryGUI::initHeader() {
  // Позиция иконки
  sf::Vector2f iconPos =
      m_headerBackground.getPosition() + sf::Vector2f(10.f, 5.f);

  // Загрузка текстуры иконки (мешок с монетами)
  m_iconTexture = TextureManager::getTexture("inventory_icon");
  m_icon.setTexture(m_iconTexture);
  m_icon.setPosition(iconPos);
  m_icon.setScale({0.8f, 0.8f});

  // Создание кнопок управления в заголовке
  float buttonSize = 30.f;
  float buttonY = m_headerBackground.getPosition().y + 5.f;
  float rightEdge =
      m_headerBackground.getPosition().x + m_headerBackground.getSize().x;

  // Кнопка закрытия (X)
  m_closeButton =
      new gui::Button(sf::Vector2f(rightEdge - buttonSize - 5.f, buttonY),
                      sf::Vector2f(buttonSize, buttonSize), "X",
                      gui::styles::buttons::btn_default, gui::type::BUTTON, 0);

  // Кнопка справки (?)
  m_helpButton =
      new gui::Button(sf::Vector2f(rightEdge - buttonSize * 2 - 10.f, buttonY),
                      sf::Vector2f(buttonSize, buttonSize), "?",
                      gui::styles::buttons::btn_default, gui::type::BUTTON, 1);

  // Кнопка минимизации
  m_minimizeButton =
      new gui::Button(sf::Vector2f(rightEdge - buttonSize * 3 - 15.f, buttonY),
                      sf::Vector2f(buttonSize, buttonSize), "_",
                      gui::styles::buttons::btn_default, gui::type::BUTTON, 2);
}

// Инициализация вкладок инвентаря
void GUI::InventoryGUI::initTabs() {
  float tabWidth = 120.f;
  float tabHeight = 40.f;
  float startX = m_background.getPosition().x + 10.f;
  float tabY = m_headerBackground.getPosition().y +
               m_headerBackground.getSize().y + 10.f;

  // Создаем вкладки
  std::string tabNames[TAB_COUNT] = {"Inventory", "Pearl"};

  for (int i = 0; i < TAB_COUNT; ++i) {
    gui::Button *tab =
        new gui::Button(sf::Vector2f(startX + i * (tabWidth + 5.f), tabY),
                        sf::Vector2f(tabWidth, tabHeight), tabNames[i],
                        gui::styles::buttons::btn_tab, gui::type::BUTTON, i);
    m_tabs.push_back(tab);
  }

  // Чекбокс для Auto Arrange
  float checkboxSize = 24.f;
  float checkboxX = m_background.getPosition().x + 90.f;
  float checkboxY = tabY + tabHeight + 20.f;

  m_autoArrangeCheckbox = new gui::CheckBox(
      sf::Vector2f(checkboxX, checkboxY),
      sf::Vector2f(checkboxSize, checkboxSize), m_font,
      "", // Пустой текст, так как у нас отдельно есть m_autoArrangeText
      14,
      false // Начальное состояние - выключено
  );

  // Текст для чекбокса
  m_autoArrangeText.setFont(m_font);
  m_autoArrangeText.setCharacterSize(16);
  m_autoArrangeText.setString("Auto Arrange");
  m_autoArrangeText.setFillColor(sf::Color::White);
  m_autoArrangeText.setPosition(
      sf::Vector2f(checkboxX + checkboxSize + 10.f, checkboxY));
}

// Инициализация ячеек инвентаря
void GUI::InventoryGUI::initSlots(unsigned int rows, unsigned int cols,
                                  float slotSize) {
  float startX = m_background.getPosition().x + 30.f;
  float startY = m_background.getPosition().y + 150.f;
  float spacing = 5.f;

  // Создаем сетку ячеек
  m_slots.resize(rows);
  for (unsigned int row = 0; row < rows; ++row) {
    m_slots[row].resize(cols);
    for (unsigned int col = 0; col < cols; ++col) {
      int slotIndex = row * cols + col;

      // Создаем кнопку для ячейки
      gui::Button *slot = new gui::Button(
          sf::Vector2f(startX + col * (slotSize + spacing),
                       startY + row * (slotSize + spacing)),
          sf::Vector2f(slotSize, slotSize), " ", gui::styles::buttons::btn_slot,
          gui::type::BUTTON, slotIndex);

      m_slots[row][col] = slot;

      // По умолчанию последние два ряда заблокированы
      if (row >= rows - 2) {
        m_slotLocked.push_back(true);
      } else {
        m_slotLocked.push_back(false);
      }
    }
  }
}

// Инициализация информации о вместимости
void GUI::InventoryGUI::initCapacityInfo() {
  // Позиция информации о вместимости - внизу инвентаря
  float baseY = m_background.getPosition().y + m_background.getSize().y - 70.f;
  float startX = m_background.getPosition().x + 30.f;

  // Текст о вместимости
  m_capacityText.setFont(m_font);
  m_capacityText.setCharacterSize(16);
  m_capacityText.setFillColor(sf::Color::White);
  m_capacityText.setPosition(sf::Vector2f(startX, baseY));
  m_capacityText.setString("13/41");

  // Индикатор вместимости
  m_weightBar = new gui::ProgressBar(
      sf::Vector2f(startX + 80.f, baseY), sf::Vector2f(150.f, 18.f),
      sf::Color(180, 140, 30), // Цвет заполнения - золотой
      14, m_font);
  m_weightBar->update(40.1f, 448.f); // Пример значений из референса
}

// Инициализация информации о валюте
void GUI::InventoryGUI::initCurrencyInfo() {
  // Позиция информации о валюте - внизу инвентаря
  float baseY = m_background.getPosition().y + m_background.getSize().y - 40.f;
  float startX = m_background.getPosition().x + 50.f;
  float spacing = 120.f;

  // Загружаем и устанавливаем текстуры для иконок монет
  sf::Texture &goldTexture = TextureManager::getTexture("coins_gold_nugget");
  sf::Texture &silverTexture =
      TextureManager::getTexture("coins_silver_nugget");
  sf::Texture &copperTexture =
      TextureManager::getTexture("coins_copper_nugget");

  m_goldIcon.setTexture(goldTexture);
  m_silverIcon.setTexture(silverTexture);
  m_copperIcon.setTexture(copperTexture);

  // Настройка текста
  m_goldText.setFont(m_font);
  m_silverText.setFont(m_font);
  m_copperText.setFont(m_font);

  m_goldText.setCharacterSize(16);
  m_silverText.setCharacterSize(16);
  m_copperText.setCharacterSize(16);

  m_goldText.setFillColor(sf::Color::White);
  m_silverText.setFillColor(sf::Color::White);
  m_copperText.setFillColor(sf::Color::White);

  m_goldText.setPosition(sf::Vector2f(startX + 30.f, baseY));
  m_silverText.setPosition(sf::Vector2f(startX + spacing + 30.f, baseY));
  m_copperText.setPosition(sf::Vector2f(startX + spacing * 2 + 30.f, baseY));

  m_goldText.setString("17");
  m_silverText.setString("0");
  m_copperText.setString("0");

  // Кнопка удаления предметов (корзина)
  float deleteButtonSize = 60.f;
  float deleteButtonX = m_background.getPosition().x +
                        m_background.getSize().x - deleteButtonSize - 20.f;

  m_deleteButton =
      new gui::Button(sf::Vector2f(deleteButtonX, baseY - 10.f),
                      sf::Vector2f(deleteButtonSize, deleteButtonSize), " ",
                      gui::styles::buttons::btn_default, gui::type::BUTTON,
                      99 // ID кнопки удаления
      );

  // Создание описания предмета
  float descWidth = m_background.getSize().x * 0.3f;
  float descHeight = 120.f;
  float descX = m_background.getPosition().x + m_background.getSize().x -
                descWidth - 20.f;
  float descY = m_background.getPosition().y + 200.f;

  m_itemDescription = new gui::TextBox(
      sf::Vector2f(descX, descY), sf::Vector2f(descWidth, descHeight), m_font,
      "Select an item to see details", // Placeholder
      14,
      0,   // Без ограничения символов
      true // Многострочное
  );

  // По умолчанию не выбран ни один предмет
  m_selectedSlot = -1;
}

// Обновление позиций всех предметов в инвентаре
void GUI::InventoryGUI::updateItemPosGUI() {
  if (auto inventory = m_inventory.lock()) {
    const auto &inventoryArray = inventory->getInventoryArray();
    for (size_t row = 0; row < inventoryArray.size() && row < m_slots.size();
         ++row) {
      for (size_t col = 0;
           col < inventoryArray[row].size() && col < m_slots[row].size();
           ++col) {
        const auto &item = inventoryArray[row][col];
        if (item) {
          // Получаем позицию соответствующего слота
          sf::Vector2f slotPosition = m_slots[row][col]->getPosition();

          // Устанавливаем позицию предмета соответствующую позиции слота
          item->setPosition(slotPosition);

          // Устанавливаем фиксированный размер предмета (размер слота)
          float slotSize = 50.f; // Используем фиксированный размер или
                                 // соответствующее значение
          item->setSize({slotSize, slotSize});
        }
      }
    }
  }
}

// Конструктор с правильными инициализациями SFML объектов
GUI::InventoryGUI::InventoryGUI(std::weak_ptr<Inventory> inventory,
                                sf::Vector2f screenSize, sf::Font &font,
                                float slotSize, unsigned int characterSize)
    : m_inventory(inventory), m_font(font), m_visible(false),
      m_currentTab(TAB_INVENTORY), m_selectedSlot(-1),
      // Инициализация текстовых объектов
      m_autoArrangeText(font, "", characterSize),
      m_capacityText(font, "", characterSize),
      m_goldText(font, "", characterSize),
      m_silverText(font, "", characterSize),
      m_copperText(font, "", characterSize),
      // Инициализация спрайтов с нулевой текстурой из TextureManager
      m_icon(TextureManager::getTexture("texture_null")),
      m_goldIcon(TextureManager::getTexture("texture_null")),
      m_silverIcon(TextureManager::getTexture("texture_null")),
      m_copperIcon(TextureManager::getTexture("texture_null")) {

  // Инициализация всех компонентов
  initBackground(screenSize);
  initHeader();
  initTabs();
  initSlots(8, 8, slotSize); // 8x8 сетка ячеек
  initCapacityInfo();
  initCurrencyInfo();

  // По умолчанию активна первая вкладка
  setActiveTab(TAB_INVENTORY);

  // Комментарий: Для реализации GUI инвентаря нужно добавить следующие текстуры
  // в TextureManager:
  // - "inventory_icon" - иконка инвентаря (мешок)
  // - "gold_icon" - иконка золотых монет
  // - "silver_icon" - иконка серебряных монет
  // - "copper_icon" - иконка медных монет
}

// Деструктор
GUI::InventoryGUI::~InventoryGUI() {
  // Освобождаем память
  delete m_closeButton;
  delete m_helpButton;
  delete m_minimizeButton;
  delete m_autoArrangeCheckbox;
  delete m_weightBar;
  delete m_deleteButton;
  delete m_itemDescription;

  // Очищаем вкладки
  for (auto tab : m_tabs) {
    delete tab;
  }

  // Очищаем слоты
  for (auto &row : m_slots) {
    for (auto slot : row) {
      delete slot;
    }
  }
}

// Получение позиции слота по его индексу
sf::Vector2f GUI::InventoryGUI::getSlotPosition(int slotIndex) const {
  if (slotIndex < 0 || m_slots.empty() || m_slots[0].empty()) {
    // В случае некорректного индекса или пустых слотов возвращаем нулевую
    // позицию
    return sf::Vector2f(0.f, 0.f);
  }

  unsigned int cols = m_slots[0].size();
  unsigned int row = slotIndex / cols;
  unsigned int col = slotIndex % cols;

  // Проверяем, что индексы находятся в пределах размеров сетки
  if (row >= m_slots.size() || col >= m_slots[row].size()) {
    return sf::Vector2f(0.f, 0.f);
  }

  return m_slots[row][col]->getPosition();
}

// Обновление состояния
void GUI::InventoryGUI::update(const float &dt, const sf::Vector2i &mousePos) {
  if (!isVisible())
    return;

  // Обновляем кнопки в заголовке
  m_closeButton->update(mousePos);
  m_helpButton->update(mousePos);
  m_minimizeButton->update(mousePos);

  // Обновляем вкладки
  for (auto tab : m_tabs) {
    tab->update(mousePos);
  }

  // Обновляем чекбокс
  m_autoArrangeCheckbox->update(mousePos);

  // Обновляем ячейки
  for (auto &row : m_slots) {
    for (auto slot : row) {
      int slotIndex = slot->getID();

      // Проверяем, заблокирована ли ячейка
      if (isSlotLocked(slotIndex)) {
        // Для заблокированных ячеек меняем цвет, но не используем setIdleColor
        // Вместо этого меняем цвет самой ячейки
        // slot->setIdleColor(sf::Color(30, 30, 35, 180));
        // Иконка замка может быть добавлена в методе draw
      } else {
        // Обычные ячейки обновляем стандартно
        slot->update(mousePos);
      }
    }
  }

  // Обновляем кнопку удаления
  m_deleteButton->update(mousePos);

  // Обновляем описание предмета
  m_itemDescription->update(mousePos);

  // Обновляем информацию об инвентаре, если есть доступ к объекту инвентаря
  if (auto inventory = m_inventory.lock()) {
    // Обновляем текст с количеством монет
    m_goldText.setString(
        std::to_string(inventory->getCoins().get_GoldCointCount()));
    m_silverText.setString(
        std::to_string(inventory->getCoins().get_SilverCointCount()));
    m_copperText.setString(
        std::to_string(inventory->getCoins().get_CopperCointCount()));

    // Обновляем текст с вместимостью
    int usedSlots = 0;
    int totalSlots = inventory->getTotalSlots();

    for (const auto &row : inventory->getInventoryArray()) {
      for (const auto &item : row) {
        if (item)
          usedSlots++;
      }
    }

    m_capacityText.setString(std::to_string(usedSlots) + "/" +
                             std::to_string(totalSlots));

    // Обновляем индикатор вместимости (пример значений, можно заменить на
    // реальные)
    m_weightBar->update(40.1f, 448.f);
  }
}

// Обработка событий
void GUI::InventoryGUI::handleEvent(const sf::Event &event,
                                    const sf::Vector2i &mousePos) {
  if (!isVisible())
    return;

  if (const auto *ev = event.getIf<sf::Event::MouseButtonPressed>())
    if (ev->button == sf::Mouse::Button::Left) {
      // Обработка нажатий на кнопки заголовка
      if (m_closeButton && !m_closeButton->isDisabled() &&
          m_closeButton->isPressed()) {
        setVisible(false);
        return;
      }

      if (m_helpButton && !m_helpButton->isDisabled() &&
          m_helpButton->isPressed()) {
        // Логика для кнопки справки
        return;
      }

      if (m_minimizeButton && !m_minimizeButton->isDisabled() &&
          m_minimizeButton->isPressed()) {
        // Логика для кнопки минимизации
        return;
      }

      // Обработка нажатий на вкладки - просто проверяем не disabled
      for (size_t i = 0; i < m_tabs.size(); ++i) {
        if (!m_tabs[i]->isDisabled() && m_tabs[i]->isPressed()) {
          handleTabClick(static_cast<InventoryTab>(i));
          return;
        }
      }

      // Обработка нажатий на ячейки с проверкой disabled
      for (auto &row : m_slots) {
        for (auto slot : row) {
          if (!slot->isDisabled() && slot->isPressed()) {
            int slotIndex = slot->getID();
            if (!isSlotLocked(slotIndex)) {
              handleSlotClick(slotIndex);
            }
            return;
          }
        }
      }

      // Обработка нажатия на кнопку удаления, если она не disabled
      if (m_deleteButton && !m_deleteButton->isDisabled() &&
          m_deleteButton->isPressed()) {
        handleDeleteClick();
        return;
      }

      // Обработка нажатия на чекбокс - используем правильные методы
      if (m_autoArrangeCheckbox->isPressed()) {
        handleAutoArrangeToggle(m_autoArrangeCheckbox->isChecked());
        return;
      }
    }

  // Обработка текстового поля
  if (m_itemDescription) {
    m_itemDescription->handleInput(event);
  }
}

// Видимость инвентаря
bool GUI::InventoryGUI::isVisible() const { return m_visible; }

void GUI::InventoryGUI::setVisible(bool visible) {
  m_visible = visible;

  // Также обновляем видимость в объекте инвентаря, если он доступен
  if (auto inventory = m_inventory.lock()) {
    if (visible) {
      inventory->openInventory();
    } else {
      inventory->closeInventory();
    }
  }
}

void GUI::InventoryGUI::toggleVisible() { setVisible(!m_visible); }

// Управление вкладками с использованием disabled вместо просто изменения цветов
void GUI::InventoryGUI::setActiveTab(InventoryTab tab) {
  m_currentTab = tab;

  // Обновляем внешний вид вкладок, используя свойство disabled
  for (size_t i = 0; i < m_tabs.size(); ++i) {
    if (i == static_cast<size_t>(tab))
      // Активная вкладка становится disabled, с подходящими цветами
      m_tabs[i]->changeActivity(true); // Нельзя нажать на активную вкладку
    else
      m_tabs[i]->changeActivity(false);
  }

  // Обновляем содержимое инвентаря в зависимости от выбранной вкладки
  refreshItems();
}

GUI::InventoryTab GUI::InventoryGUI::getActiveTab() const {
  return m_currentTab;
}

// Обновление предметов в инвентаре
void GUI::InventoryGUI::refreshItems() {
  if (auto inventory = m_inventory.lock()) {
    // Здесь должна быть логика для отображения предметов в зависимости от
    // вкладки Это будет зависеть от структуры данных в вашем классе Inventory
  }
}

// Заблокирована ли ячейка
bool GUI::InventoryGUI::isSlotLocked(int slotIndex) const {
  if (slotIndex >= 0 && slotIndex < static_cast<int>(m_slotLocked.size())) {
    return m_slotLocked[slotIndex];
  }
  return false;
}

// При блокировке слота использовать свойство disabled
void GUI::InventoryGUI::lockSlot(int slotIndex, bool locked) {
  if (slotIndex >= 0 && slotIndex < static_cast<int>(m_slotLocked.size())) {
    m_slotLocked[slotIndex] = locked;

    // Найдем кнопку слота и установим ей disabled, если слот заблокирован
    for (auto &row : m_slots)
      for (auto slot : row)
        if (slot->getID() == slotIndex) {
          slot->changeActivity(locked);
          return;
        }
  }
}

// Обработка нажатия на ячейку
void GUI::InventoryGUI::handleSlotClick(int slotIndex) {
  m_selectedSlot = slotIndex;

  // Получаем информацию о предмете и обновляем описание
  if (auto inventory = m_inventory.lock()) {
    auto item = inventory->getItemFromSlot(slotIndex);
    if (item) {
      // Отображаем информацию о предмете
      m_itemDescription->setText(item->getName() + "\n\n" + "Type: Item\n" +
                                 "Quality: Common");
    } else {
      // Ячейка пуста
      m_itemDescription->setText("Empty slot");
    }
  }
}

// Обработка нажатия на кнопку удаления
void GUI::InventoryGUI::handleDeleteClick() {
  if (m_selectedSlot >= 0 && !isSlotLocked(m_selectedSlot)) {
    // Удаляем выбранный предмет, если он есть
    if (auto inventory = m_inventory.lock()) {
      inventory->removeItemByID(m_selectedSlot);
      // Обновляем описание и выбранный слот
      m_itemDescription->setText("Item deleted");
      m_selectedSlot = -1;

      // Обновляем отображение инвентаря
      refreshItems();
    }
  }
}

// Обработка нажатия на вкладку
void GUI::InventoryGUI::handleTabClick(InventoryTab tab) { setActiveTab(tab); }

// Обработка переключения Auto Arrange
void GUI::InventoryGUI::handleAutoArrangeToggle(bool checked) {
  // Здесь должна быть логика для автоматического размещения предметов
  if (checked) {
    auto inventory = m_inventory.lock();
    if (inventory) {
      // Реализация автоматической сортировки предметов
      // ...
      refreshItems();
    }
  }
}

// Отрисовка
void GUI::InventoryGUI::draw(sf::RenderTarget &target,
                             sf::RenderStates states) const {
  if (!isVisible())
    return;

  // Отрисовка фона
  target.draw(m_background, states);
  target.draw(m_headerBackground, states);

  // Отрисовка заголовка
  target.draw(m_icon, states);
  target.draw(*m_closeButton, states);
  target.draw(*m_helpButton, states);
  target.draw(*m_minimizeButton, states);

  // Отрисовка вкладок
  for (const auto tab : m_tabs) {
    target.draw(*tab, states);
  }

  // Отрисовка чекбокса - используем draw вместо render
  target.draw(*m_autoArrangeCheckbox, states);
  target.draw(m_autoArrangeText, states);

  // Отрисовка ячеек инвентаря
  for (const auto &row : m_slots) {
    for (const auto slot : row) {
      target.draw(*slot, states);

      // Для заблокированных ячеек добавляем иконку замка
      int slotIndex = slot->getID();
      if (isSlotLocked(slotIndex)) {
        // Здесь можно добавить отрисовку иконки замка
        // Например, используя спрайт или текст
      }
    }
  }

  // Отрисовка предметов в инвентаре
  if (auto inventory = m_inventory.lock()) {
    const auto &inventoryArray = inventory->getInventoryArray();
    for (size_t row = 0; row < inventoryArray.size() && row < m_slots.size();
         ++row) {
      for (size_t col = 0;
           col < inventoryArray[row].size() && col < m_slots[row].size();
           ++col) {
        const auto &item = inventoryArray[row][col];
        if (item) {
          // Отрисовка предмета (позиция уже установлена в updateItemPosGUI)
          item->render(target);
        }
      }
    }
  }

  // Отрисовка информации о вместимости
  target.draw(m_capacityText, states);
  m_weightBar->render(target);

  // Отрисовка информации о валюте
  target.draw(m_goldIcon, states);
  target.draw(m_silverIcon, states);
  target.draw(m_copperIcon, states);
  target.draw(m_goldText, states);
  target.draw(m_silverText, states);
  target.draw(m_copperText, states);

  // Отрисовка кнопки удаления
  target.draw(*m_deleteButton, states);

  // Отрисовка описания предмета
  target.draw(*m_itemDescription, states);
}