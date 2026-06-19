#ifndef GUI_SIMPLE_CHECKBOX_HPP
#define GUI_SIMPLE_CHECKBOX_HPP

#include "../../core/header.h"

namespace gui {
class CheckBox: public sf::Drawable {
private:
	enum checkbox_states {
		CBX_IDLE = 0,
		CBX_HOVER,
		CBX_ACTIVE
	} _mState;

	bool _mActive;
	bool _isBlocked = false;


	sf::RectangleShape boxShape, checkShape;
	sf::Text text;

	sf::Color backfill = sf::Color(30, 40, 65);
	sf::Color fill = sf::Color(90, 120, 185);


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(boxShape, states);
		if (_mActive)
			target.draw(checkShape, states);
	//	target.draw(text, states);
	}

public:

	CheckBox(sf::Vector2f _pos, float _size, sf::Font& _font, std::string _text, bool _init = false, unsigned _charsize = 20U)
		: text(_font, _text, _charsize), _mState(CBX_IDLE), _mActive(_init) {

	   // Основной квадрат чекбокса
		boxShape.setPosition(_pos);
		boxShape.setSize({_size,_size});
		boxShape.setFillColor(backfill);
		boxShape.setOutlineThickness(-1.f);
		boxShape.setOutlineColor(sf::Color::Black);

	   // Внутренний квадрат-галочка
		float offset = std::roundf(_size * 0.15f);
		checkShape.setPosition({_pos.x + offset, _pos.y + offset});
		checkShape.setSize({_size - offset * 2.f , _size - offset * 2.f});
		checkShape.setFillColor(fill);

	   // Текст рядом с чекбоксом
		text.setFillColor(sf::Color(255, 255, 255, 200));
		text.setPosition({_pos.x + _size + 10.f, _pos.y + _size / 2.f - text.getGlobalBounds().size.y / 2.f});
	}
	~CheckBox() {}

   // Accessors
	const bool isActive() const { return  _mActive; }
	const bool isPressed() const {
		return  _mState == checkbox_states::CBX_ACTIVE && _isBlocked == false;
	}


// Modifiers 
	void toggle() { _mActive = !_mActive; }

	// Functions
	void update(const sf::Vector2f& mousePosWindow) {
		_mState = CBX_IDLE;

		sf::Color offset(20, 20, 20);
		if (boxShape.getGlobalBounds().contains(mousePosWindow)) {
			_mState = CBX_HOVER;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				_mState = CBX_ACTIVE;
		}

		switch (_mState) {
		case CBX_IDLE:
			checkShape.setFillColor(fill);
			//text.setFillColor(textIdleColor);
			break;
		case CBX_HOVER:
			checkShape.setFillColor(fill + offset);
			//text.setFillColor(textHoverColor);
			_isBlocked = false;
			break;
		case CBX_ACTIVE:
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _isBlocked == false) {
				checkShape.setFillColor(fill - offset);
				//text.setFillColor(textActiveColor);

				toggle();
				_isBlocked = true;
			}
			break;
		}
	}
};
} // namespace gui
#endif // GUI_SIMPLE_CHECKBOX_HPP