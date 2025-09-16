#include "textbox.hpp"

gui::TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font &font,
                      std::string placeholder, unsigned character_size,
                      unsigned character_limit, bool multiline)
    : text(font, "", character_size),
      placeholderText(font, placeholder, character_size) {

  this->textboxState = TEXTBOX_IDLE;
  this->selected = false;
  this->showCursor = false;
  this->limit = character_limit;
  this->multiline = multiline;

  // Настройка основного поля ввода
  this->shape.setPosition(position);
  this->shape.setSize(size);
  this->shape.setFillColor(sf::Color(50, 50, 50, 200));
  this->shape.setOutlineThickness(1.f);
  this->shape.setOutlineColor(sf::Color(150, 150, 150, 200));

  // Настройка текста
  this->text.setFillColor(sf::Color(255, 255, 255, 255));
  this->text.setPosition({position.x + 5.f, position.y + 5.f});

  // Настройка текста-плейсхолдера
  this->placeholderText.setFillColor(sf::Color(180, 180, 180, 200));
  this->placeholderText.setPosition({position.x + 5.f, position.y + 5.f});

  // Настройка курсора
  this->cursor.setSize({2.f, static_cast<float>(character_size)});
  this->cursor.setFillColor(sf::Color(255, 255, 255, 200));
  this->cursor.setPosition({position.x + 5.f, position.y + 5.f});

  // Настройка цветов для различных состояний
  this->textIdleColor = sf::Color(255, 255, 255, 200);
  this->textHoverColor = sf::Color(255, 255, 255, 255);
  this->textActiveColor = sf::Color(255, 255, 255, 255);

  this->idleColor = sf::Color(50, 50, 50, 200);
  this->hoverColor = sf::Color(60, 60, 60, 200);
  this->activeColor = sf::Color(70, 70, 70, 200);

  this->outlineIdleColor = sf::Color(150, 150, 150, 200);
  this->outlineHoverColor = sf::Color(200, 200, 200, 255);
  this->outlineActiveColor = sf::Color(255, 255, 255, 255);

  this->placeholderColor = sf::Color(180, 180, 180, 200);
}

gui::TextBox::~TextBox() {
  // Деструктор
}

// Аксессоры
const std::string gui::TextBox::getText() const {
  return this->text.getString();
}

const bool gui::TextBox::isSelected() const { return this->selected; }

const bool gui::TextBox::isHover() const {
  return this->textboxState == TEXTBOX_HOVER;
}

// Модификаторы
void gui::TextBox::setLimit(unsigned limit) { this->limit = limit; }

void gui::TextBox::setMultiline(bool multiline) { this->multiline = multiline; }

void gui::TextBox::setSelected(bool selected) {
  this->selected = selected;
  // При выборе текстового поля сбрасываем таймер курсора
  if (selected) {
    this->cursorBlinkTimer.restart();
  }
}

void gui::TextBox::setText(const std::string text) {
  this->text.setString(text);
  this->updateCursorPosition();
}

void gui::TextBox::setPlaceholder(const std::string placeholder) {
  this->placeholderText.setString(placeholder);
}

// Функции
void gui::TextBox::update(const sf::Vector2i &mousePosWindow) {
  // Сброс состояния
  this->textboxState = TEXTBOX_IDLE;

  // Проверка наведения мыши
  if (this->shape.getGlobalBounds().contains(
          static_cast<sf::Vector2f>(mousePosWindow))) {
    this->textboxState = TEXTBOX_HOVER;

    // Если нажата левая кнопка мыши, выбираем поле
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      this->textboxState = TEXTBOX_ACTIVE;
      this->selected = true;
      this->cursorBlinkTimer.restart();
    }
  }
  // Если нажата левая кнопка мыши вне поля, снимаем выделение
  else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    this->selected = false;
  }

  // Обновление визуального состояния
  switch (this->textboxState) {
  case TEXTBOX_IDLE:
    this->shape.setFillColor(this->idleColor);
    this->shape.setOutlineColor(this->outlineIdleColor);
    this->text.setFillColor(this->textIdleColor);
    break;

  case TEXTBOX_HOVER:
    this->shape.setFillColor(this->hoverColor);
    this->shape.setOutlineColor(this->outlineHoverColor);
    this->text.setFillColor(this->textHoverColor);
    break;

  case TEXTBOX_ACTIVE:
    this->shape.setFillColor(this->activeColor);
    this->shape.setOutlineColor(this->outlineActiveColor);
    this->text.setFillColor(this->textActiveColor);
    break;

  default:
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setOutlineColor(sf::Color::Green);
    this->text.setFillColor(sf::Color::Blue);
    break;
  }

  // Мигание курсора каждые 0.5 секунды
  if (this->selected) {
    if (this->cursorBlinkTimer.getElapsedTime().asSeconds() >= 0.5f) {
      this->showCursor = !this->showCursor;
      this->cursorBlinkTimer.restart();
    }
  }
}

void gui::TextBox::handleInput(const sf::Event &event) {
  if (this->selected) {
    if (auto textEvent = event.getIf<sf::Event::TextEntered>()) {
      this->inputLogic(textEvent->unicode);
    }
  }
}