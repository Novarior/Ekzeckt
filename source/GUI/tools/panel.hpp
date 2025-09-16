#ifndef GUI_COMPLEX_PANEL_HPP
#define GUI_COMPLEX_PANEL_HPP

#include "../components/button.hpp"
#include <map>
#include <string>

namespace gui {

class Panel : public sf::Drawable {
private:
  sf::RectangleShape background;
  sf::RectangleShape titleBar;
  sf::Text title;
  sf::Font &font;

  std::map<std::string, gui::Button *> buttons;

  bool draggable;
  bool dragging;
  sf::Vector2f dragStart;
  sf::Vector2f initialPosition;

  bool visible;
  bool closing;
  float fadeAlpha;

  // Анимация появления/исчезновения
  bool animating;
  sf::Clock animationClock;
  float animationDuration;

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override {
    if (this->visible) {
      target.draw(this->background, states);
      target.draw(this->titleBar, states);
      target.draw(this->title, states);

      for (auto &btn : this->buttons) {
        target.draw(*btn.second, states);
      }
    }
  }

public:
  /**
   * @brief Construct a new Panel object
   *
   * @param position - position of panel
   * @param size - size of panel
   * @param font - font for text
   * @param title - title text
   * @param draggable - whether panel can be dragged
   */
  Panel(sf::Vector2f position, sf::Vector2f size, sf::Font &font,
        std::string title = "Panel", bool draggable = true);

  ~Panel();

  // Accessors
  const bool isVisible() const;
  const bool isDraggable() const;
  const bool isDragging() const;
  const sf::Vector2f getPosition() const;
  const sf::Vector2f getSize() const;
  const std::string getTitle() const;

  // Buttons management
  void addButton(const std::string &key, gui::Button *button);
  gui::Button *getButton(const std::string &key);
  void removeButton(const std::string &key);

  // Modifiers
  void setPosition(const sf::Vector2f position);
  void setSize(const sf::Vector2f size);
  void setTitle(const std::string title);
  void setTitleBarColor(const sf::Color color);
  void setBackgroundColor(const sf::Color color);
  void setDraggable(const bool draggable);
  void setVisible(const bool visible);

  // Animations
  void fadeIn(const float duration = 0.3f);
  void fadeOut(const float duration = 0.3f);

  // Update
  void update(const sf::Vector2i &mousePosWindow, const float &dt);
};

} // namespace gui
#endif // GUI_COMPLEX_PANEL_HPP