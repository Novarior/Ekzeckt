#ifndef GUI_COMPLEX_TOOLBAR_HPP
#define GUI_COMPLEX_TOOLBAR_HPP

#include "../components/button.hpp"
#include <functional>
#include <map>
#include <string>

namespace gui {

enum toolbar_orientation { TOOLBAR_HORIZONTAL = 0, TOOLBAR_VERTICAL };

class ToolBar : public sf::Drawable {
private:
  short unsigned orientation;
  sf::RectangleShape background;
  std::map<std::string, gui::Button *> buttons;

  float padding;
  float buttonSize;
  float spacing;

  bool visible;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    if (this->visible) {
      target.draw(this->background, states);

      for (const auto &pair : this->buttons) {
        target.draw(*pair.second, states);
      }
    }
  }

  void repositionButtons() {
    float currentOffset = this->padding;

    for (auto &pair : this->buttons) {
      gui::Button *btn = pair.second;

      if (this->orientation == TOOLBAR_HORIZONTAL) {
        sf::Vector2f pos = this->background.getPosition();
        pos.x += currentOffset;
        pos.y += this->padding;
        btn->setPosition(pos);
        currentOffset += this->buttonSize + this->spacing;
      } else {
        sf::Vector2f pos = this->background.getPosition();
        pos.x += this->padding;
        pos.y += currentOffset;
        btn->setPosition(pos);
        currentOffset += this->buttonSize + this->spacing;
      }
    }

    // Обновляем размер панели инструментов
    if (this->orientation == TOOLBAR_HORIZONTAL) {
      float width = this->padding * 2.f +
                    this->buttons.size() * this->buttonSize +
                    (this->buttons.size() - 1) * this->spacing;
      float height = this->padding * 2.f + this->buttonSize;
      this->background.setSize({width, height});
    } else {
      float width = this->padding * 2.f + this->buttonSize;
      float height = this->padding * 2.f +
                     this->buttons.size() * this->buttonSize +
                     (this->buttons.size() - 1) * this->spacing;
      this->background.setSize({width, height});
    }
  }

public:
  /**
   * @brief Construct a new Tool Bar object
   *
   * @param position - position of toolbar
   * @param orientation - horizontal or vertical
   * @param button_size - size of buttons
   * @param padding - padding around buttons
   * @param spacing - spacing between buttons
   */
  ToolBar(sf::Vector2f position,
          short unsigned orientation = TOOLBAR_HORIZONTAL,
          float button_size = 30.f, float padding = 5.f, float spacing = 5.f);

  ~ToolBar();

  // Accessors
  const bool isVisible() const;
  const sf::Vector2f getPosition() const;
  const sf::Vector2f getSize() const;
  gui::Button *getButton(const std::string &key);

  // Modifiers
  void setPosition(const sf::Vector2f position);
  void setBackgroundColor(const sf::Color color);
  void setVisible(const bool visible);
  void setPadding(const float padding);
  void setSpacing(const float spacing);
  void setButtonSize(const float button_size);
  void setOrientation(const short unsigned orientation);

  // Button Management
  void addButton(const std::string &key, const std::string &text,
                 sf::Font &font,
                 const std::function<void()> &callback = nullptr);
  void addButton(const std::string &key, gui::Button *button);
  void removeButton(const std::string &key);

  // Update
  void update(const sf::Vector2i &mousePosWindow);

  // Event handling
  void handleClick(const sf::Vector2i &mousePosWindow);
};

} // namespace gui
#endif // GUI_COMPLEX_TOOLBAR_HPP