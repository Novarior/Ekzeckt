#include "scrollbar.hpp"
#include <algorithm>

gui::ScrollBar::ScrollBar(sf::Vector2f position, sf::Vector2f size,
                          short unsigned type, float visible_size,
                          float content_size)
    : sbType(type), thumbRatio(1.f), position(0.f), visibleSize(visible_size),
      contentSize(content_size), dragging(false) {

  // Настройка дорожки полосы прокрутки
  this->track.setPosition(position);
  this->track.setSize(size);
  this->trackColor = sf::Color(50, 50, 50, 200);
  this->track.setFillColor(this->trackColor);

  // Настройка ползунка
  this->thumbColor = sf::Color(120, 120, 120, 200);
  this->thumbHoverColor = sf::Color(150, 150, 150, 200);
  this->thumbActiveColor = sf::Color(170, 170, 170, 200);
  this->thumb.setFillColor(this->thumbColor);

  // Инициализация размера и положения ползунка
  this->updateThumbSize();
  this->updateThumbPosition();
}

gui::ScrollBar::~ScrollBar() {
  // Деструктор
}

// Аксессоры
const float gui::ScrollBar::getPosition() const { return this->position; }

const float gui::ScrollBar::getVisibleSize() const { return this->visibleSize; }

const float gui::ScrollBar::getContentSize() const { return this->contentSize; }

const sf::Vector2f gui::ScrollBar::getScrollBarPosition() const {
  return this->track.getPosition();
}

const sf::Vector2f gui::ScrollBar::getScrollBarSize() const {
  return this->track.getSize();
}

// Модификаторы
void gui::ScrollBar::setPosition(const float position) {
  this->position = position;
  this->updateThumbPosition();
}

void gui::ScrollBar::setVisibleSize(const float visible_size) {
  this->visibleSize = visible_size;
  this->updateThumbSize();
  this->updateThumbPosition();
}

void gui::ScrollBar::setContentSize(const float content_size) {
  this->contentSize = content_size;
  this->updateThumbSize();
  this->updateThumbPosition();
}

void gui::ScrollBar::setScrollBarPosition(const sf::Vector2f position) {
  this->track.setPosition(position);
  this->updateThumbPosition();
}

void gui::ScrollBar::setScrollBarSize(const sf::Vector2f size) {
  this->track.setSize(size);
  this->updateThumbSize();
  this->updateThumbPosition();
}

void gui::ScrollBar::setTrackColor(const sf::Color color) {
  this->trackColor = color;
  this->track.setFillColor(color);
}

void gui::ScrollBar::setThumbColor(const sf::Color color) {
  this->thumbColor = color;
  if (!this->dragging) {
    this->thumb.setFillColor(color);
  }
}

void gui::ScrollBar::setThumbHoverColor(const sf::Color color) {
  this->thumbHoverColor = color;
}

void gui::ScrollBar::setThumbActiveColor(const sf::Color color) {
  this->thumbActiveColor = color;
}

// Обновление
void gui::ScrollBar::update(const sf::Vector2i &mousePosWindow) {
  sf::Vector2f mousePos = static_cast<sf::Vector2f>(mousePosWindow);

  if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
    // Если мы перетаскиваем ползунок
    if (this->dragging) {
      float trackLength = this->sbType == SCROLLBAR_VERTICAL
                              ? this->track.getSize().y
                              : this->track.getSize().x;

      float thumbLength = this->sbType == SCROLLBAR_VERTICAL
                              ? this->thumb.getSize().y
                              : this->thumb.getSize().x;

      float trackSpace = trackLength - thumbLength;

      if (trackSpace > 0.f) {
        float newPosition;

        if (this->sbType == SCROLLBAR_VERTICAL) {
          float mouseOffset =
              mousePos.y - this->track.getPosition().y - this->dragOffset.y;
          float positionRatio = mouseOffset / trackSpace;
          newPosition = positionRatio * (this->contentSize - this->visibleSize);
        } else {
          float mouseOffset =
              mousePos.x - this->track.getPosition().x - this->dragOffset.x;
          float positionRatio = mouseOffset / trackSpace;
          newPosition = positionRatio * (this->contentSize - this->visibleSize);
        }

        this->position =
            std::clamp(newPosition, 0.f, this->contentSize - this->visibleSize);
        this->updateThumbPosition();
      }
    }
    // Проверяем, начинаем ли перетаскивание
    else if (this->thumb.getGlobalBounds().contains(mousePos)) {
      this->dragging = true;

      // Запоминаем смещение от начала ползунка к точке нажатия
      if (this->sbType == SCROLLBAR_VERTICAL) {
        this->dragOffset.y = mousePos.y - this->thumb.getPosition().y;
      } else {
        this->dragOffset.x = mousePos.x - this->thumb.getPosition().x;
      }

      this->thumb.setFillColor(this->thumbActiveColor);
    }
    // Если нажали на дорожку, прокручиваем к этой позиции
    else if (this->track.getGlobalBounds().contains(mousePos)) {
      float trackLength = this->sbType == SCROLLBAR_VERTICAL
                              ? this->track.getSize().y
                              : this->track.getSize().x;

      float thumbLength = this->sbType == SCROLLBAR_VERTICAL
                              ? this->thumb.getSize().y
                              : this->thumb.getSize().x;

      float trackSpace = trackLength - thumbLength;

      if (trackSpace > 0.f) {
        float clickOffset;

        if (this->sbType == SCROLLBAR_VERTICAL) {
          clickOffset =
              mousePos.y - this->track.getPosition().y - thumbLength / 2.f;
        } else {
          clickOffset =
              mousePos.x - this->track.getPosition().x - thumbLength / 2.f;
        }

        clickOffset = std::clamp(clickOffset, 0.f, trackSpace);
        float positionRatio = clickOffset / trackSpace;
        float newPosition =
            positionRatio * (this->contentSize - this->visibleSize);

        this->position =
            std::clamp(newPosition, 0.f, this->contentSize - this->visibleSize);
        this->updateThumbPosition();
      }
    }
  } else {
    this->dragging = false;

    // Обновляем цвет ползунка при наведении
    if (this->thumb.getGlobalBounds().contains(mousePos)) {
      this->thumb.setFillColor(this->thumbHoverColor);
    } else {
      this->thumb.setFillColor(this->thumbColor);
    }
  }
}

// Действия с полосой прокрутки
void gui::ScrollBar::scroll(float amount) {
  this->position += amount;
  this->updateThumbPosition();
}

void gui::ScrollBar::scrollToPosition(float position) {
  this->position = position;
  this->updateThumbPosition();
}

void gui::ScrollBar::scrollToBeginning() {
  this->position = 0.f;
  this->updateThumbPosition();
}

void gui::ScrollBar::scrollToEnd() {
  this->position = this->contentSize - this->visibleSize;
  this->updateThumbPosition();
}