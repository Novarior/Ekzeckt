#ifndef GUI_SIMPLE_TEXTURESELECTOR_HPP
#define GUI_SIMPLE_TEXTURESELECTOR_HPP
#include "../components/button.hpp"

namespace gui {
class TextureSelector {
private:
  float keytime;
  const float keytimeMax;
  float gridSize;
  bool active;
  bool hidden;
  gui::Button *hide_btn;
  sf::RectangleShape bounds;
  sf::Sprite sheet;
  sf::RectangleShape selector;
  sf::Vector2u mousePosGrid;
  sf::IntRect textureRect;

public:
  TextureSelector(float x, float y, float width, float height, float gridSize,
                  const sf::Texture &texture_sheet, sf::Font &font,
                  std::string text);
  ~TextureSelector();

  // Accessors
  const bool &getActive() const;
  const sf::IntRect &getTextureRect() const;

  // Functions
  const bool getKeytime();
  void updateKeytime(const float &dt);
  void update(const sf::Vector2i &mousePosWindow, const float &dt);
  void render(sf::RenderTarget &target);
};
} // namespace gui
#endif // !GUI_TEXTURESELECTOR_HPP