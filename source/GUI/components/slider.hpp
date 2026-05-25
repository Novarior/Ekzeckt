#ifndef GUI_SIMPLE_SLIDER_HPP
#define GUI_SIMPLE_SLIDER_HPP

#include "../../core/header.h"

namespace gui {
template <typename T>
class Slider {
private:
	sf::RectangleShape _sliderBox;
	sf::RectangleShape _sliderFillBox;
	sf::CircleShape _sliderCircle;

	sf::Text _nameSlider; // название слайдера
	sf::Text _textValue;  // текстовое значение слайдера
	sf::Font& _font;      // шрифт
	T _value;
	T _newValue;
	T _min;
	T _max;
	T _step;
	bool isChanged = false;

public:
	Slider(sf::Vector2f position, sf::Vector2f size,
		   sf::Font& font, T base_value, T min_val, T max_val, T step,
		   const unsigned character_size = 20, const std::string& name = "FIX ME")
		: _font(font), _value(base_value), _newValue(base_value), _min(min_val), _max(max_val), _step(step),
		_nameSlider(font, name, character_size),
		_textValue(font, "", character_size) {

		_sliderBox.setPosition({position.x, position.y + size.y / 3.f});
		_sliderBox.setSize(sf::Vector2f(size.x, size.y / 3.f));
		_sliderBox.setFillColor(sf::Color(100, 100, 100, 200));

		float ratio = static_cast<float>(_value - _min) / (_max - _min);
		_sliderFillBox.setPosition({position.x, position.y + size.y / 3.f});
		_sliderFillBox.setSize(sf::Vector2f(size.x * ratio, size.y / 6.f));
		_sliderFillBox.setFillColor(sf::Color(200, 200, 200, 200));

		// кружочек которй находится на слайдере
		_sliderCircle.setPosition({position.x + size.x * ratio - size.y / 6.f, position.y + size.y / 3.f});
		_sliderCircle.setRadius(size.y / 6.f);
		_sliderCircle.setFillColor(sf::Color::White);
		_sliderCircle.setOutlineThickness(1.f);
		_sliderCircle.setOutlineColor(sf::Color::Black);

		// параметры для текста (значение слайдера)
		// позиция текста значения слайдера находится слева от самого
		_textValue.setPosition({position.x + size.x + 5.f, position.y + size.y / 3.f - _textValue.getGlobalBounds().size.y / 2.f});
		_textValue.setString(std::to_string(_value));
		_textValue.setFillColor(sf::Color::White);

		_nameSlider.setPosition({position.x + size.x / 2.f - _nameSlider.getGlobalBounds().size.y / 2.f, position.y - _nameSlider.getGlobalBounds().size.y});
	}

	// destructor
	~Slider() {}

	T getValue() const { return _value; }

	// update slider (cricles) position and value using mouse position
	// if mouse is on slider, slider is litle bit bigger and litle bit red
	void update(const sf::Vector2f& mouse_pos_view) {
		if (_sliderBox.getGlobalBounds().contains(mouse_pos_view) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			// Обновляем слайдер если мышь находится гдето внутри рабочей области слайдера
			float new_x = mouse_pos_view.x - _sliderCircle.getRadius();
			new_x = std::fmax(new_x, _sliderBox.getPosition().x);
			new_x = std::fmin(new_x, _sliderBox.getPosition().x + _sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
			_sliderCircle.setPosition({new_x, _sliderCircle.getPosition().y});

			// Обновляем значение слайдера
			float ratio = (new_x - _sliderBox.getPosition().x) / (_sliderBox.getSize().x - 2 * _sliderCircle.getRadius());
			_value = _min + ratio * (_max - _min);

			if (_value != _newValue) {
				isChanged = true;
				_newValue = _value;
			} else
				isChanged = false;

			// Обновляем заполненность слайдера
			_sliderFillBox.setSize({ratio * _sliderBox.getSize().x, _sliderFillBox.getSize().y});

			// Обновляем значение текста
			_textValue.setString(std::to_string(_value));
		} else
			_sliderCircle.setFillColor(sf::Color::White);
	}

	bool isChangedValue() const { return isChanged; }

	// render slider
	void render(sf::RenderTarget& target) {
		target.draw(_sliderBox);
		target.draw(_sliderFillBox);
		target.draw(_sliderCircle);
		target.draw(_textValue);
		target.draw(_nameSlider);
	}
}; // namespace gui

typedef Slider<int> SliderInt;
typedef Slider<unsigned int> SliderUInt;
typedef Slider<float> SliderFloat;

};
#endif // !GUI_SIMPLE_SLIDER_HPP