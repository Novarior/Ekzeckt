#include "minimap.hpp"

namespace gui
{

    MiniMap::MiniMap(const sf::Vector2f m_position, const sf::Vector2f m_size, sf::IntRect worldSize)
        : m_worldBounds(worldSize)
    {
         m_background.setPosition(m_position);
         m_background.setSize(sf::Vector2f(m_size.x, m_size.y));
         m_background.setOutlineThickness(1.f);
         m_background.setOutlineColor(sf::Color::Red);

         m_view.setPosition(m_position);
         m_view.setSize(m_size);
         m_view.setFillColor(sf::Color(0, 0, 0, 0));
         m_view.setOutlineThickness(1.f);
         m_view.setOutlineColor(sf::Color::White);

         m_player.setSize(sf::Vector2f(5.f, 5.f));
         m_player.setFillColor(sf::Color::Red);

         m_entity.setSize(sf::Vector2f(2.f, 2.f));
         m_entity.setFillColor(sf::Color::Red);
    }

    MiniMap::~MiniMap() {}

    void MiniMap::update(sf::Vector2f playerPos, sf::Vector2f entitys)
    {
        // Получите размеры миникарты
        sf::Vector2f miniMapSize =  m_background.getSize();

        // Выполните нормализацию координат точки в диапазоне [0, 1]
        float normalizedX = (playerPos.x -  m_worldBounds.position.x) /  m_worldBounds.size.x;
        float normalizedY = (playerPos.y -  m_worldBounds.position.y) /  m_worldBounds.size.y;

        // Умножьте нормализованные координаты на размеры миникарты
        sf::Vector2f miniMapPos;
        miniMapPos.x = normalizedX * miniMapSize.x;
        miniMapPos.y = normalizedY * miniMapSize.y;

        // Установите позицию игрока на миникарте
         m_player.setPosition(miniMapPos +  m_background.getPosition());
        // Выполните нормализацию координат точки в диапазоне [0, 1]
        normalizedX = (entitys.x -  m_worldBounds.position.x) /  m_worldBounds.size.x;
        normalizedY = (entitys.y -  m_worldBounds.position.y) /  m_worldBounds.size.y;

        // Умножьте нормализованные координаты на размеры миникарты

        miniMapPos.x = normalizedX * miniMapSize.x;
        miniMapPos.y = normalizedY * miniMapSize.y;
         m_entity.setPosition(miniMapPos +  m_background.getPosition());
    }

    void MiniMap::render(sf::RenderTarget &target)
    {
        target.draw( m_background);
        target.draw( m_view);
        target.draw( m_player);
        target.draw( m_entity);
    }
} // namespace gui