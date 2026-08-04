#ifndef GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#define GUI_SIMPLE_COMPONENTS_MINIMAP_HPP
#include "../../core/header.h"
#include "../../core/tools/appfn_logger.hpp"
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

	void setTexture(sf::Texture texture) { m_texture = texture; }
	void setImage(sf::Image image) {
		m_image = image;
		if (!m_texture.loadFromImage(m_image)) {
			appfn::Logger::logStatic("Failed to load texture from image", "MiniMap::setImage()");
			m_texture = sf::Texture();
		}
		m_background.setTexture(&m_texture);
	}

	void update(sf::Vector2f playerPos, sf::Vector2f entitys);
	void render(sf::RenderTarget& target);
};
} // namespace gui
#endif // !GUI_COMPONENTS_MINIMAP_HPP