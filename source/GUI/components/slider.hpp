#ifndef GUI_SIMPLE_SLIDER_HPP
#define GUI_SIMPLE_SLIDER_HPP

#include "../GUI_Component.hpp"

#include "../../core/header.h"

namespace gui {
template <typename T>
class Slider:public GuiComponent {
private:
	sf::RectangleShape _sliderBox, _sliderFillBox;
	sf::CircleShape  _leftCircleShape, _rightCircleShape, _sliderFillCircle;

	sf::Text _nameSlider; // название слайдера
	sf::Text _textValue;  // текстовое значение слайдера
	sf::Font& _font;      // шрифт
	T _value;
	T _newValue;
	T _min;
	T _max;

	bool isChanged = false;
	bool valueWasChanged = false;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		// background
		target.draw(_leftCircleShape);
		target.draw(_rightCircleShape);
		target.draw(_sliderBox);
		// fill shape
		target.draw(_sliderFillBox);
		target.draw(_sliderFillCircle);
		// text
		target.draw(_textValue);
		target.draw(_nameSlider);
	}
public:
	Slider(sf::Vector2f position, sf::Vector2f size,
		   sf::Font& font, const unsigned character_size = 20U,
		   T base_value = 0, T  min_val = 0, T  max_val = 0, const std::string& name = "FIX ME")
		: _font(font), _value(base_value), _newValue(base_value), _min(min_val), _max(max_val),
		_nameSlider(font, name, character_size), _textValue(font, std::to_string(base_value), character_size) {

		float size2X = float(size.x) / 2.f;
		float size3Y = float(size.y) / 3.f;
		float size10Y = float(size.y) / 10.f;
		sf::Color backfill = sf::Color(30, 40, 65);
		sf::Color fill = sf::Color(90, 120, 185);

		// init background shapes
		_leftCircleShape.setPosition(position);
		_leftCircleShape.setRadius(size3Y);
		_leftCircleShape.setFillColor(backfill);

		_rightCircleShape.setPosition({position.x + size.x - size3Y * 2.f , position.y});
		_rightCircleShape.setRadius(size3Y);
		_rightCircleShape.setFillColor(backfill);

		_sliderBox.setPosition({position.x + size3Y,position.y});
		_sliderBox.setSize({size.x - size3Y * 2,size3Y * 2.f});
		_sliderBox.setFillColor(backfill);

		//int fill shapes
		float ratio = static_cast<float>(_value - _min) / _max;
		_sliderFillBox.setSize({size.x * ratio, (size3Y - size10Y) * 2.f});
		_sliderFillBox.setPosition({position.x + size3Y,position.y + size10Y});
		_sliderFillBox.setFillColor(fill);

		_sliderFillCircle.setRadius(size3Y - size10Y);
		_sliderFillCircle.setPosition({position.x + size10Y + size.x * ratio,position.y + size10Y});
		_sliderFillCircle.setFillColor(fill);
		_sliderFillCircle.setOutlineThickness(-1.f);
		_sliderFillCircle.setOutlineColor(sf::Color::Black);

		// text fields
		_textValue.setString(std::to_string((T)(base_value)));
		_textValue.setPosition({position.x + size.x - size3Y / 2.f, position.y + size.y - size3Y - character_size / 4.f});
		_textValue.setFillColor(sf::Color::White);
		_textValue.setLineAlignment(sf::Text::LineAlignment::Right);

		_nameSlider.setPosition({position.x + size3Y / 2.f, position.y + size.y - size3Y - character_size / 4.f});
	}

	// destructor
	~Slider() {}

	const T getValue() const { return _value; }
	void setCurrentValue(T _val) {
		if (_min < _val < _max) {
			_value = _val;
			valueWasChanged = true;
		}
	}
	const bool isValueChanged() const { return valueWasChanged; }
	void closeChangeValue() { valueWasChanged = false; }

	// update slider (cricles) position and value using mouse position
	// if mouse is on slider, slider is litle bit bigger and litle bit red
	void update(const sf::Vector2f& mousePosView) {
		if (_sliderBox.getGlobalBounds().contains(mousePosView) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {



			float radius = _sliderFillCircle.getRadius();
			float minX = _sliderBox.getPosition().x - radius;
			float maxX = minX + _sliderBox.getSize().x;

			float new_x = mousePosView.x - radius;
			new_x = std::fmax(new_x, minX);
			new_x = std::fmin(new_x, maxX);


			float centerX = new_x;
			_sliderFillCircle.setPosition({centerX , _sliderFillCircle.getPosition().y});

			float ratio = (centerX - minX) / _sliderBox.getSize().x;
			ratio = std::fmax(0.f, std::fmin(1.f, ratio));
			ratio = std::round(ratio * 1000.0f) / 1000.0f;


			_value = T(_min) + ratio * (T(_max) - T(_min));
			_value= std::round(_value * 1000.0f) / 1000.0f;

			if (_value != _newValue) {
				isChanged = true;
				_newValue = _value;
			} else {
				isChanged = false;
			}

			_sliderFillBox.setSize({ratio * _sliderBox.getSize().x, _sliderFillBox.getSize().y});
			_textValue.setString(std::to_string((T)(_value)));
			valueWasChanged = true;
		}
	}

	bool isChangedValue() const { return isChanged; }


}; // namespace gui
typedef Slider<int> SliderInt;
typedef Slider<unsigned int> SliderUInt;
typedef Slider<float> SliderFloat;
};
#endif // !GUI_SIMPLE_SLIDER_HPP