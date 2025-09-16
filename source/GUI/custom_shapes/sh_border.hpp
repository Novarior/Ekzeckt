#ifndef BORDER_HPP
#define BORDER_HPP

#include <SFML/Graphics.hpp>

namespace Nova {

class Border : public sf::Drawable {
private:
  sf::VertexArray mVertex;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    target.draw(mVertex);
  }

public:
  Border() { mVertex = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 0); }
  Border(sf::Vector2f pos, sf::Vector2f size, float outline_thickness) {
    mVertex = sf::VertexArray(sf::PrimitiveType::TriangleStrip, 10);

    mVertex[0].position = pos;
    mVertex[1].position =
        sf::Vector2f(pos.x + outline_thickness, pos.y + outline_thickness);
    mVertex[2].position = sf::Vector2f(pos.x + size.x, pos.y);
    mVertex[3].position = sf::Vector2f(pos.x + size.x - outline_thickness,
                                       pos.y + outline_thickness);
    mVertex[4].position = sf::Vector2f(pos.x + size.x, pos.y + size.y);
    mVertex[5].position = sf::Vector2f(pos.x + size.x - outline_thickness,
                                       pos.y + size.y - outline_thickness);
    mVertex[6].position = sf::Vector2f(pos.x, pos.y + size.y);
    mVertex[7].position = sf::Vector2f(pos.x + outline_thickness,
                                       pos.y + size.y - outline_thickness);
    mVertex[8].position = pos;
    mVertex[9].position =
        sf::Vector2f(pos.x + outline_thickness, pos.y + outline_thickness);
  }
  virtual ~Border() {}

  void setColor(sf::Color color) {
    for (int i = 0; i < mVertex.getVertexCount(); i++)
      mVertex[i].color = color;
  }
  void setPosition(sf::Vector2f position) {
    for (int i = 0; i < mVertex.getVertexCount(); i++)
      mVertex[i].position += position;
  }
};

} // namespace Nova

#endif /* BORDER_HPP */
