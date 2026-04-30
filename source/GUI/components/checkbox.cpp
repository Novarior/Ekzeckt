#include "checkbox.hpp"

gui::CheckBox::CheckBox(sf::Vector2f position, sf::Vector2f size,
                        sf::Font &font, std::string text,
                        unsigned character_size, bool initial_state)
    : text(font, text, character_size)
{

    enum checkbox_states
    {
        CBX_IDLE = 0,
        CBX_HOVER,
        CBX_ACTIVE
    };
    this->checkboxState = CBX_IDLE;
    this->checked = initial_state;

    // Основной квадрат чекбокса
    this->boxShape.setPosition(position);
    this->boxShape.setSize(size);
    this->boxShape.setFillColor(sf::Color(70, 70, 70, 200));
    this->boxShape.setOutlineThickness(1.f);
    this->boxShape.setOutlineColor(sf::Color(150, 150, 150, 200));

    // Внутренний квадрат-галочка
    float offset = size.x * 0.15f;
    this->checkShape.setPosition({position.x + offset, position.y + offset});
    this->checkShape.setSize({size.x - 2.f * offset, size.y - 2.f * offset});
    this->checkShape.setFillColor(sf::Color(100, 250, 100, 200));

    // Текст рядом с чекбоксом
    this->text.setFillColor(sf::Color(255, 255, 255, 200));
    this->text.setPosition({position.x + size.x + 10.f, position.y + size.y / 2.f - this->text.getGlobalBounds().size.y / 2.f});

    // Цвета для различных состояний
    this->textIdleColor = sf::Color(255, 255, 255, 200);
    this->textHoverColor = sf::Color(255, 255, 255, 255);
    this->textActiveColor = sf::Color(255, 255, 255, 200);

    this->uncheckedIdleColor = sf::Color(70, 70, 70, 200);
    this->uncheckedHoverColor = sf::Color(90, 90, 90, 200);
    this->uncheckedActiveColor = sf::Color(100, 100, 100, 200);

    this->checkedIdleColor = sf::Color(70, 70, 70, 200);
    this->checkedHoverColor = sf::Color(90, 90, 90, 200);
    this->checkedActiveColor = sf::Color(100, 100, 100, 200);

    this->outlineIdleColor = sf::Color(150, 150, 150, 200);
    this->outlineHoverColor = sf::Color(200, 200, 200, 255);
    this->outlineActiveColor = sf::Color(100, 100, 100, 200);
}

gui::CheckBox::~CheckBox()
{
    // Деструктор
}

// Аксессоры
const bool gui::CheckBox::isChecked() const { return this->checked; }

const bool gui::CheckBox::isPressed() const { return this->checkboxState == 2; }

const bool gui::CheckBox::isHover() const { return this->checkboxState == 1; }

// Модификаторы
void gui::CheckBox::setText(const std::string text) { this->text.setString(text); }

void gui::CheckBox::setChecked(const bool checked) { this->checked = checked; }

void gui::CheckBox::toggle() { this->checked = !this->checked; }

// Функции
void gui::CheckBox::update(const sf::Vector2i &mousePosWindow)
{
    enum checkbox_states
    {
        CBX_IDLE = 0,
        CBX_HOVER,
        CBX_ACTIVE
    };

    // Сброс состояния
    this->checkboxState = CBX_IDLE;

    // Проверка наведения
    if (this->boxShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
    {
        this->checkboxState = CBX_HOVER;
        // Проверка нажатия
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            this->checkboxState = CBX_ACTIVE;
    }

    // Обновление визуального состояния
    switch (this->checkboxState)
    {
    case CBX_IDLE:
        this->boxShape.setFillColor(this->checked ? this->checkedIdleColor : this->uncheckedIdleColor);
        this->boxShape.setOutlineColor(this->outlineIdleColor);
        this->text.setFillColor(this->textIdleColor);
        break;
    case CBX_HOVER:
        this->boxShape.setFillColor(this->checked ? this->checkedHoverColor : this->uncheckedHoverColor);
        this->boxShape.setOutlineColor(this->outlineHoverColor);
        this->text.setFillColor(this->textHoverColor);
        break;
    case CBX_ACTIVE:
        this->boxShape.setFillColor(this->checked ? this->checkedActiveColor : this->uncheckedActiveColor);
        this->boxShape.setOutlineColor(this->outlineActiveColor);
        this->text.setFillColor(this->textActiveColor);

        // Переключение состояния при отпускании кнопки мыши
        static bool was_pressed = false;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            was_pressed = true;
        else if (was_pressed)
        {
            was_pressed = false;
            this->toggle();
        }
        break;

    default:
        this->boxShape.setFillColor(sf::Color::Red);
        this->boxShape.setOutlineColor(sf::Color::Green);
        this->text.setFillColor(sf::Color::Blue);
        break;
    }
}