#include "minimap.hpp"

namespace gui {

MiniMap::MiniMap(const sf::Vector2f m_position, const sf::Vector2f m_size, sf::IntRect worldSize)
    : m_worldBounds(worldSize)
{
    this->m_background.setPosition(m_position);
    this->m_background.setSize(sf::Vector2f(m_size.x, m_size.y));
    this->m_background.setOutlineThickness(1.f);
    this->m_background.setOutlineColor(sf::Color::Red);

    this->m_view.setPosition(m_position);
    this->m_view.setSize(m_size);
    this->m_view.setFillColor(sf::Color(0, 0, 0, 0));
    this->m_view.setOutlineThickness(1.f);
    this->m_view.setOutlineColor(sf::Color::White);

    this->m_player.setSize(sf::Vector2f(5.f, 5.f));
    this->m_player.setFillColor(sf::Color::Red);

    this->m_entity.setSize(sf::Vector2f(2.f, 2.f));
    this->m_entity.setFillColor(sf::Color::Red);
}

MiniMap::~MiniMap() { }

void MiniMap::update(sf::Vector2f playerPos, sf::Vector2f entitys)
{
    // Получите размеры миникарты
    sf::Vector2f miniMapSize = this->m_background.getSize();

    // Выполните нормализацию координат точки в диапазоне [0, 1]
    float normalizedX = (playerPos.x - this->m_worldBounds.position.x) / this->m_worldBounds.size.x;
    float normalizedY = (playerPos.y - this->m_worldBounds.position.y) / this->m_worldBounds.size.y;

    // Умножьте нормализованные координаты на размеры миникарты
    sf::Vector2f miniMapPos;
    miniMapPos.x = normalizedX * miniMapSize.x;
    miniMapPos.y = normalizedY * miniMapSize.y;

    // Установите позицию игрока на миникарте
    this->m_player.setPosition(miniMapPos + this->m_background.getPosition());
    // Выполните нормализацию координат точки в диапазоне [0, 1]
    normalizedX = (entitys.x - this->m_worldBounds.position.x) / this->m_worldBounds.size.x;
    normalizedY = (entitys.y - this->m_worldBounds.position.y) / this->m_worldBounds.size.y;

    // Умножьте нормализованные координаты на размеры миникарты

    miniMapPos.x = normalizedX * miniMapSize.x;
    miniMapPos.y = normalizedY * miniMapSize.y;
    this->m_entity.setPosition(miniMapPos + this->m_background.getPosition());
}

void MiniMap::render(sf::RenderTarget& target)
{
    target.draw(this->m_background);
    target.draw(this->m_view);
    target.draw(this->m_player);
    target.draw(this->m_entity);
}

} // namespace gui