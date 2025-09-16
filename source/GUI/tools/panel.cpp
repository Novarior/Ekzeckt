#include "panel.hpp"

gui::Panel::Panel(sf::Vector2f position, sf::Vector2f size, sf::Font &font,
                  std::string title, bool draggable)
    : font(font), title(font, title, 18), draggable(draggable), dragging(false),
      visible(true), closing(false), fadeAlpha(255.f), animating(false),
      animationDuration(0.3f) {

  // Настройка фона панели
  this->background.setPosition(position);
  this->background.setSize(size);
  this->background.setFillColor(sf::Color(50, 50, 50, this->fadeAlpha));
  this->background.setOutlineThickness(1.f);
  this->background.setOutlineColor(sf::Color(100, 100, 100, this->fadeAlpha));

  // Настройка заголовка панели
  this->titleBar.setPosition(position);
  this->titleBar.setSize({size.x, 30.f});
  this->titleBar.setFillColor(sf::Color(70, 70, 70, this->fadeAlpha));

  // Настройка текста заголовка
  this->title.setFillColor(sf::Color(255, 255, 255, this->fadeAlpha));
  this->title.setPosition({position.x + 10.f, position.y + 5.f});

  // Запоминаем начальное положение
  this->initialPosition = position;
}

gui::Panel::~Panel() {
  // Удаляем все кнопки
  for (auto &btn : this->buttons) {
    delete btn.second;
  }
  this->buttons.clear();
}

// Аксессоры
const bool gui::Panel::isVisible() const { return this->visible; }

const bool gui::Panel::isDraggable() const { return this->draggable; }

const bool gui::Panel::isDragging() const { return this->dragging; }

const sf::Vector2f gui::Panel::getPosition() const {
  return this->background.getPosition();
}

const sf::Vector2f gui::Panel::getSize() const {
  return this->background.getSize();
}

const std::string gui::Panel::getTitle() const {
  return this->title.getString();
}

// Управление кнопками
void gui::Panel::addButton(const std::string &key, gui::Button *button) {
  this->buttons[key] = button;
}

gui::Button *gui::Panel::getButton(const std::string &key) {
  if (this->buttons.find(key) != this->buttons.end()) {
    return this->buttons[key];
  }
  return nullptr;
}

void gui::Panel::removeButton(const std::string &key) {
  if (this->buttons.find(key) != this->buttons.end()) {
    delete this->buttons[key];
    this->buttons.erase(key);
  }
}

// Модификаторы
void gui::Panel::setPosition(const sf::Vector2f position) {
  // Перемещаем все элементы панели на новую позицию
  sf::Vector2f offset = position - this->background.getPosition();

  this->background.setPosition(position);
  this->titleBar.setPosition(position);
  this->title.setPosition({position.x + 10.f, position.y + 5.f});

  // Перемещаем все кнопки
  for (auto &btn : this->buttons) {
    sf::Vector2f btnPos = btn.second->getPosition();
    btn.second->setPosition(btnPos + offset);
  }
}

void gui::Panel::setSize(const sf::Vector2f size) {
  this->background.setSize(size);
  this->titleBar.setSize({size.x, 30.f});
}

void gui::Panel::setTitle(const std::string title) {
  this->title.setString(title);
}

void gui::Panel::setTitleBarColor(const sf::Color color) {
  this->titleBar.setFillColor(color);
}

void gui::Panel::setBackgroundColor(const sf::Color color) {
  this->background.setFillColor(color);
}

void gui::Panel::setDraggable(const bool draggable) {
  this->draggable = draggable;
}

void gui::Panel::setVisible(const bool visible) { this->visible = visible; }

// Анимации
void gui::Panel::fadeIn(const float duration) {
  if (!this->visible) {
    this->visible = true;
    this->closing = false;
    this->animating = true;
    this->fadeAlpha = 0.f;
    this->animationDuration = duration;
    this->animationClock.restart();
  }
}

void gui::Panel::fadeOut(const float duration) {
  if (this->visible) {
    this->closing = true;
    this->animating = true;
    this->fadeAlpha = 255.f;
    this->animationDuration = duration;
    this->animationClock.restart();
  }
}

// Обновление
void gui::Panel::update(const sf::Vector2i &mousePosWindow, const float &dt) {
  if (!this->visible && !this->animating)
    return;

  // Обновление анимации
  if (this->animating) {
    float elapsed = this->animationClock.getElapsedTime().asSeconds();
    float progress = elapsed / this->animationDuration;

    if (progress >= 1.f) {
      this->animating = false;
      if (this->closing) {
        this->visible = false;
        this->fadeAlpha = 0.f;
      } else {
        this->fadeAlpha = 255.f;
      }
    } else {
      this->fadeAlpha =
          this->closing ? 255.f * (1.f - progress) : 255.f * progress;
    }

    // Обновляем альфа-канал для всех элементов
    sf::Color bgColor = this->background.getFillColor();
    sf::Color titleBarColor = this->titleBar.getFillColor();
    sf::Color textColor = this->title.getFillColor();
    sf::Color outlineColor = this->background.getOutlineColor();

    bgColor.a = static_cast<std::uint8_t>(this->fadeAlpha);
    titleBarColor.a = static_cast<std::uint8_t>(this->fadeAlpha);
    textColor.a = static_cast<std::uint8_t>(this->fadeAlpha);
    outlineColor.a = static_cast<std::uint8_t>(this->fadeAlpha);

    this->background.setFillColor(bgColor);
    this->titleBar.setFillColor(titleBarColor);
    this->title.setFillColor(textColor);
    this->background.setOutlineColor(outlineColor);
  }

  // Обновление кнопок
  for (auto &btn : this->buttons) {
    btn.second->update(mousePosWindow);
  }

  // Обработка перетаскивания
  if (this->draggable) {
    sf::Vector2f mousePos = static_cast<sf::Vector2f>(mousePosWindow);

    // Если не перетаскиваем и нажата кнопка мыши в заголовке
    if (!this->dragging &&
        sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) &&
        this->titleBar.getGlobalBounds().contains(mousePos)) {

      this->dragging = true;
      this->dragStart = mousePos;
      this->initialPosition = this->background.getPosition();
    }

    // Если перетаскиваем и кнопка мыши нажата
    if (this->dragging) {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        // Вычисляем смещение мыши относительно начальной точки
        sf::Vector2f offset = mousePos - this->dragStart;

        // Устанавливаем новую позицию панели
        this->setPosition(this->initialPosition + offset);
      } else {
        this->dragging = false;
      }
    }
  }
}