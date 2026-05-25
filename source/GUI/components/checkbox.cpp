#include "checkbox.hpp"

gui::CheckBox::CheckBox(sf::Vector2f _pos, sf::Vector2f _size, sf::Font& _font, std::string _text, unsigned _charsize, bool _init)
	: text(_font, _text, _charsize) {

	enum checkbox_states {
		CBX_IDLE = 0,
		CBX_HOVER,
		CBX_ACTIVE
	};
	checkboxState = CBX_IDLE;
	bChecked = _init;

   // Основной квадрат чекбокса
	boxShape.setPosition(_pos);
	boxShape.setSize(_size);
	boxShape.setFillColor(sf::Color(70, 70, 70, 200));
	boxShape.setOutlineThickness(1.f);
	boxShape.setOutlineColor(sf::Color(150, 150, 150, 200));

   // Внутренний квадрат-галочка
	float offset = _size.x * 0.15f;
	checkShape.setPosition({_pos.x + offset, _pos.y + offset});
	checkShape.setSize({_size.x - 2.f * offset, _size.y - 2.f * offset});
	checkShape.setFillColor(sf::Color(100, 250, 100, 200));

   // Текст рядом с чекбоксом
	text.setFillColor(sf::Color(255, 255, 255, 200));
	text.setPosition({_pos.x + _size.x + 10.f, _pos.y + _size.y / 2.f - text.getGlobalBounds().size.y / 2.f});

   // Цвета для различных состояний
	textIdleColor = sf::Color(255, 255, 255, 200);
	textHoverColor = sf::Color(255, 255, 255, 255);
	textActiveColor = sf::Color(255, 255, 255, 200);

	uncheckedIdleColor = sf::Color(70, 70, 70, 200);
	uncheckedHoverColor = sf::Color(90, 90, 90, 200);
	uncheckedActiveColor = sf::Color(100, 100, 100, 200);

	checkedIdleColor = sf::Color(70, 70, 70, 200);
	checkedHoverColor = sf::Color(90, 90, 90, 200);
	checkedActiveColor = sf::Color(100, 100, 100, 200);

	outlineIdleColor = sf::Color(150, 150, 150, 200);
	outlineHoverColor = sf::Color(200, 200, 200, 255);
	outlineActiveColor = sf::Color(100, 100, 100, 200);
}

gui::CheckBox::~CheckBox() {
	// Деструктор
}

// Аксессоры
const bool gui::CheckBox::isChecked() const { return  bChecked; }

const bool gui::CheckBox::isPressed() const { return  checkboxState == 2; }

const bool gui::CheckBox::isHover() const { return  checkboxState == 1; }

// Модификаторы
void gui::CheckBox::setText(const std::string _text) { text.setString(_text); }

void gui::CheckBox::setChecked(const bool checked) { bChecked = checked; }

void gui::CheckBox::toggle() { bChecked = !bChecked; }

// Функции
void gui::CheckBox::update(const sf::Vector2i& mousePosWindow) {
	enum checkbox_states {
		CBX_IDLE = 0,
		CBX_HOVER,
		CBX_ACTIVE
	};

	// Сброс состояния
	checkboxState = CBX_IDLE;

   // Проверка наведения
	if (boxShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
		checkboxState = CBX_HOVER;
	   // Проверка нажатия
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			checkboxState = CBX_ACTIVE;
	}

	// Обновление визуального состояния
	switch (checkboxState) {
	case CBX_IDLE:
		boxShape.setFillColor(bChecked ? checkedIdleColor : uncheckedIdleColor);
		boxShape.setOutlineColor(outlineIdleColor);
		text.setFillColor(textIdleColor);
		break;
	case CBX_HOVER:
		boxShape.setFillColor(bChecked ? checkedHoverColor : uncheckedHoverColor);
		boxShape.setOutlineColor(outlineHoverColor);
		text.setFillColor(textHoverColor);
		break;
	case CBX_ACTIVE:
		boxShape.setFillColor(bChecked ? checkedActiveColor : uncheckedActiveColor);
		boxShape.setOutlineColor(outlineActiveColor);
		text.setFillColor(textActiveColor);

	   // Переключение состояния при отпускании кнопки мыши

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			was_pressed = true;
		else if (was_pressed) {
			was_pressed = false;
			toggle();
		}
		break;

	default:
		boxShape.setFillColor(sf::Color::Red);
		boxShape.setOutlineColor(sf::Color::Green);
		text.setFillColor(sf::Color::Blue);
		was_pressed = false;
		break;
	}
}