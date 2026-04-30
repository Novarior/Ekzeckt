#include "AIWander.hpp"
#include "AIOption.hpp"

AIWander::AIWander(Entity &self, float radius)
    : AIOption(self, self), _radius(radius)
{
    // Инициализация центра блуждания с корректным использованием случайных значений
    _center = _ai_self.e_getPosition() - sf::Vector2f((std::rand() % 20) - 10, (std::rand() % 20) - 10);

    // Вычисление начального направления
    sf::Vector2f toCenter = _center - _ai_self.e_getPosition();
    float angleToCenter = std::atan2(toCenter.y, toCenter.x);

    // Добавление случайного отклонения в пределах +/- 45 градусов
    float angle = angleToCenter + ((std::rand() % 90) - 45) * M_PI / 180.0f;

    _direction = sf::Vector2f(std::cos(angle), std::sin(angle));
    _distance = static_cast<float>(std::rand() % static_cast<int>(_radius)); // Случайная дистанция в пределах радиуса
}

AIWander::~AIWander() {}

void AIWander::update(const float &delta_time)
{
    this->updateCooldown(delta_time);

    // Если сущность достигла цели или прошёл таймер, выбираем новое направление
    if (isCooldownOver() || _distance <= 0.f)
    {
        sf::Vector2f toCenter = _center - _ai_self.e_getPosition();
        float angleToCenter = std::atan2(toCenter.y, toCenter.x);

        // Добавление случайного отклонения в пределах +/- 45 градусов
        float angle = angleToCenter + ((std::rand() % 90) - 45) * M_PI / 180.0f;

        _direction = sf::Vector2f(std::cos(angle), std::sin(angle));
        _distance = static_cast<float>(std::rand() % static_cast<int>(_radius)); // Случайная дистанция
    }

#if __MDEBUG__
    _line.clear();

    _line.setPrimitiveType(sf::PrimitiveType::Lines);

    sf::Vertex _v1, _v2, _v3, _v4;
    _v1.position = _ai_self.e_getPosition();
    _v1.color = sf::Color::Red;

    _v2.position = _ai_self.e_getPosition() + _direction * 20.f;
    _v2.color = sf::Color::Red;

    _v3.position = _ai_self.e_getPosition();
    _v3.color = sf::Color::Green;

    _v4.position = _center;
    _v4.color = sf::Color::Green;
    // Линия от сущности к центру
    _line.append(_v1);
    _line.append(_v2);

    // Линия от сущности к направлению
    _line.append(_v3);
    _line.append(_v4);
#endif

    // Обновляем позицию объекта на основе направления и времени
    sf::Vector2f moveStep = _direction * delta_time;
    _ai_self.e_move(moveStep.x, moveStep.y, delta_time);

    // Уменьшаем оставшееся расстояние
    _distance -= std::sqrt(moveStep.x * moveStep.x + moveStep.y * moveStep.y);

    // Если объект выходит за пределы радиуса, возвращаем его в область
    sf::Vector2f toCenter = _center - _ai_self.e_getPosition();
    if (std::sqrt(toCenter.x * toCenter.x + toCenter.y * toCenter.y) > _radius)
    {
        float angleToCenter = std::atan2(toCenter.y, toCenter.x);
        _direction = sf::Vector2f(std::cos(angleToCenter), std::sin(angleToCenter));
        _ai_self.e_move(toCenter.x * delta_time, toCenter.y * delta_time, delta_time);
    } // Обновляем позицию объекта на основе направления и времени

    _ai_self.e_move(moveStep.x, moveStep.y, delta_time);

    // Уменьшаем оставшееся расстояние
    _distance -= std::sqrt(moveStep.x * moveStep.x + moveStep.y * moveStep.y);

    // Если объект выходит за пределы радиуса, возвращаем его в область

    if (std::sqrt(toCenter.x * toCenter.x + toCenter.y * toCenter.y) > _radius)
    {
        float angleToCenter = std::atan2(toCenter.y, toCenter.x);
        _direction = sf::Vector2f(std::cos(angleToCenter), std::sin(angleToCenter));
        _ai_self.e_move(toCenter.x * delta_time, toCenter.y * delta_time, delta_time);
    }
}