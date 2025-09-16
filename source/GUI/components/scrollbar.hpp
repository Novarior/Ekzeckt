#ifndef SCROLLBAR
#define SCROLLBAR

#include "../../core/header.h"

namespace gui {

enum scrollbar_types { SCROLLBAR_VERTICAL = 0, SCROLLBAR_HORIZONTAL };

class ScrollBar : public sf::Drawable {
private:
  short unsigned sbType;

  sf::RectangleShape track;
  sf::RectangleShape thumb;

  float thumbRatio;
  float position;
  float visibleSize;
  float contentSize;

  bool dragging;
  sf::Vector2f dragOffset;

  sf::Color trackColor;
  sf::Color thumbColor;
  sf::Color thumbHoverColor;
  sf::Color thumbActiveColor;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    target.draw(this->track, states);
    target.draw(this->thumb, states);
  }

  void updateThumbSize() {
    this->thumbRatio = this->visibleSize / this->contentSize;

    if (this->thumbRatio > 1.0f) {
      this->thumbRatio = 1.0f;
    }

    if (this->sbType == SCROLLBAR_VERTICAL) {
      this->thumb.setSize({this->track.getSize().x - 4.f,
                           this->track.getSize().y * this->thumbRatio - 4.f});
    } else {
      this->thumb.setSize({this->track.getSize().x * this->thumbRatio - 4.f,
                           this->track.getSize().y - 4.f});
    }
  }

  void updateThumbPosition() {
    float maxPos = this->contentSize - this->visibleSize;
    if (maxPos <= 0.f) {
      this->position = 0.f;
    } else {
      this->position = std::clamp(this->position, 0.f, maxPos);
    }

    float trackLength = this->sbType == SCROLLBAR_VERTICAL
                            ? this->track.getSize().y
                            : this->track.getSize().x;

    float thumbLength = this->sbType == SCROLLBAR_VERTICAL
                            ? this->thumb.getSize().y
                            : this->thumb.getSize().x;

    float trackSpace = trackLength - thumbLength - 4.f;

    if (trackSpace > 0.f && this->contentSize > 0.f) {
      float ratio = this->position / (this->contentSize - this->visibleSize);
      float offset = trackSpace * ratio;

      if (this->sbType == SCROLLBAR_VERTICAL) {
        this->thumb.setPosition({this->track.getPosition().x + 2.f,
                                 this->track.getPosition().y + 2.f + offset});
      } else {
        this->thumb.setPosition({this->track.getPosition().x + 2.f + offset,
                                 this->track.getPosition().y + 2.f});
      }
    } else {
      if (this->sbType == SCROLLBAR_VERTICAL) {
        this->thumb.setPosition({this->track.getPosition().x + 2.f,
                                 this->track.getPosition().y + 2.f});
      } else {
        this->thumb.setPosition({this->track.getPosition().x + 2.f,
                                 this->track.getPosition().y + 2.f});
      }
    }
  }

public:
  /**
   * @brief Construct a new Scroll Bar object
   *
   * @param position - position of scrollbar
   * @param size - size of scrollbar
   * @param type - vertical or horizontal
   * @param visible_size - visible area size
   * @param content_size - total content size
   */
  ScrollBar(sf::Vector2f position, sf::Vector2f size,
            short unsigned type = SCROLLBAR_VERTICAL,
            float visible_size = 100.f, float content_size = 100.f);

  ~ScrollBar();

  // Accessors
  const float getPosition() const;
  const float getVisibleSize() const;
  const float getContentSize() const;
  const sf::Vector2f getScrollBarPosition() const;
  const sf::Vector2f getScrollBarSize() const;

  // Modifiers
  void setPosition(const float position);
  void setVisibleSize(const float visible_size);
  void setContentSize(const float content_size);
  void setScrollBarPosition(const sf::Vector2f position);
  void setScrollBarSize(const sf::Vector2f size);
  void setTrackColor(const sf::Color color);
  void setThumbColor(const sf::Color color);
  void setThumbHoverColor(const sf::Color color);
  void setThumbActiveColor(const sf::Color color);

  // Update
  void update(const sf::Vector2i &mousePosWindow);

  // Actions
  void scroll(float amount);
  void scrollToPosition(float position);
  void scrollToBeginning();
  void scrollToEnd();
};

} // namespace gui
#endif /* SCROLLBAR */
