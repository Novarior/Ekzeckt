#ifndef CPP_STATE_PAUSE_HPP
#define CPP_STATE_PAUSE_HPP

#include "../GUI/components/button.hpp"
#include "../core/header.h"

class PauseMenu {
private:
  // Variables
  sf::Text menuText;
  sf::Font &font;
  sf::RectangleShape background;
  sf::RectangleShape container;

  std::map<std::string, gui::Button *> buttons;

  // Private Functions

public:
  PauseMenu(sf::VideoMode vm, sf::Font &font);
  virtual ~PauseMenu();

  // Accessor
  std::map<std::string, gui::Button *> &getButtons();

  // Functions
  const bool isButtonPressed(const std::string key);
  void addButton(std::string key, float y, float width, float height,
                 unsigned char_size, std::string text);

  void update(const sf::Vector2i &mousePosWindow);
  void render(sf::RenderTarget &target);
};
#endif