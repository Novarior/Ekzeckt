#include "toolbar.hpp"

gui::ToolBar::ToolBar(sf::Vector2f position, short unsigned orientation,
                      float button_size, float padding, float spacing)
    : orientation(orientation), buttonSize(button_size), padding(padding),
      spacing(spacing), visible(true) {

  // Настройка фона панели инструментов
  this->background.setPosition(position);
  this->background.setFillColor(sf::Color(50, 50, 50, 200));
  this->background.setOutlineThickness(1.f);
  this->background.setOutlineColor(sf::Color(100, 100, 100, 200));

  // Инициализируем размер фона
  if (this->orientation == TOOLBAR_HORIZONTAL) {
    this->background.setSize(
        {this->padding * 2.f, this->padding * 2.f + this->buttonSize});
  } else {
    this->background.setSize(
        {this->padding * 2.f + this->buttonSize, this->padding * 2.f});
  }
}

gui::ToolBar::~ToolBar() {
  // Удаляем все кнопки
  for (auto &pair : this->buttons) {
    delete pair.second;
  }
  this->buttons.clear();
}

// Аксессоры
const bool gui::ToolBar::isVisible() const { return this->visible; }

const sf::Vector2f gui::ToolBar::getPosition() const {
  return this->background.getPosition();
}

const sf::Vector2f gui::ToolBar::getSize() const {
  return this->background.getSize();
}

gui::Button *gui::ToolBar::getButton(const std::string &key) {
  if (this->buttons.find(key) != this->buttons.end()) {
    return this->buttons[key];
  }
  return nullptr;
}

// Модификаторы
void gui::ToolBar::setPosition(const sf::Vector2f position) {
  sf::Vector2f offset = position - this->background.getPosition();
  this->background.setPosition(position);

  // Перемещаем все кнопки
  // Примечание: так как Button не имеет метода setPosition, мы просто
  // пересоздаем кнопки в новых позициях
  this->repositionButtons();
}

void gui::ToolBar::setBackgroundColor(const sf::Color color) {
  this->background.setFillColor(color);
}

void gui::ToolBar::setVisible(const bool visible) { this->visible = visible; }

void gui::ToolBar::setPadding(const float padding) {
  this->padding = padding;
  this->repositionButtons();
}

void gui::ToolBar::setSpacing(const float spacing) {
  this->spacing = spacing;
  this->repositionButtons();
}

void gui::ToolBar::setButtonSize(const float button_size) {
  this->buttonSize = button_size;
  this->repositionButtons();
}

void gui::ToolBar::setOrientation(const short unsigned orientation) {
  this->orientation = orientation;
  this->repositionButtons();
}

// Управление кнопками
void gui::ToolBar::addButton(const std::string &key, const std::string &text,
                             sf::Font &font,
                             const std::function<void()> &callback) {
  // Создаем новую кнопку
  float currentOffset = this->padding;

  if (!this->buttons.empty()) {
    if (this->orientation == TOOLBAR_HORIZONTAL) {
      currentOffset +=
          this->buttons.size() * (this->buttonSize + this->spacing);
    } else {
      currentOffset +=
          this->buttons.size() * (this->buttonSize + this->spacing);
    }
  }

  sf::Vector2f buttonPos;
  if (this->orientation == TOOLBAR_HORIZONTAL) {
    buttonPos = {this->background.getPosition().x + currentOffset,
                 this->background.getPosition().y + this->padding};
  } else {
    buttonPos = {this->background.getPosition().x + this->padding,
                 this->background.getPosition().y + currentOffset};
  }

  // Создаем новую кнопку с базовыми цветами
  gui::Button *button = new gui::Button(
      buttonPos, sf::Vector2f(this->buttonSize, this->buttonSize), text,
      gui::styles::buttons::btn_tools, gui::type::BUTTON);

  this->buttons[key] = button;

  // Обновляем размер фона
  this->repositionButtons();
}

void gui::ToolBar::addButton(const std::string &key, gui::Button *button) {
  this->buttons[key] = button;
  this->repositionButtons();
}

void gui::ToolBar::removeButton(const std::string &key) {
  if (this->buttons.find(key) != this->buttons.end()) {
    delete this->buttons[key];
    this->buttons.erase(key);
    this->repositionButtons();
  }
}

// Обновление
void gui::ToolBar::update(const sf::Vector2i &mousePosWindow) {
  if (!this->visible)
    return;

  // Обновляем все кнопки
  for (auto &pair : this->buttons) {
    pair.second->update(mousePosWindow);
  }
}

// Обработка нажатия
void gui::ToolBar::handleClick(const sf::Vector2i &mousePosWindow) {
  if (!this->visible)
    return;

  // Проверяем, нажата ли какая-либо кнопка
  for (auto &pair : this->buttons) {
    if (pair.second->isPressed()) {
      // Здесь можно добавить вызов callback-функции, если необходимо
    }
  }
}