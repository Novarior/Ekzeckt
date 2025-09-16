#ifndef GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#define GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#include "../../core/header.h"

namespace gui {
class MiniMap {
private:
    sf::Texture m_texture;
    sf::Image m_image;
    sf::RectangleShape m_background;
    sf::RectangleShape m_view;
    sf::RectangleShape m_player;
    sf::RectangleShape m_entity;
    sf::IntRect m_worldBounds;

public:
    MiniMap(const sf::Vector2f m_position, const sf::Vector2f m_size, sf::IntRect worldSize);
    ~MiniMap();

    void setTexture(sf::Texture texture) { this->m_texture = texture; }
    void setImage(sf::Image image)
    {
        this->m_image = image;

        if (!this->m_texture.loadFromImage(this->m_image))
            Logger::logStatic("Failed to load texture from image", "MiniMap::setImage()");
        this->m_background.setTexture(&this->m_texture);
    }

    void update(sf::Vector2f playerPos, sf::Vector2f entitys);
    void render(sf::RenderTarget& target);
};
}
#endif // !GUI_COMPONENTS_MINIMAP_HPP