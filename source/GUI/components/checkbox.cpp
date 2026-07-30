#include "checkbox.hpp"

gui::CheckBox::CheckBox(sf::Vector2f _pos, float _size, sf::Font& _font, std::string _text, bool _init, unsigned _charsize)
	: text(_font, _text, _charsize), _mActive(_init) {
	mState = ComponentState::CS_IDLE;

	// basic shape CHeckBox
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
	text.setFillColor(sf::Color(220, 220, 220));
	text.setPosition({_pos.x + _size + offset, _pos.y + text.getGlobalBounds().size.y / 4.f});
}

gui::CheckBox::~CheckBox() {}

void gui::CheckBox::update(const sf::Vector2f& mousePosWindow) {
	if (!mData.isActive) {
		mState = ComponentState::CS_DISABLED;
		return;
	}

	mState = ComponentState::CS_IDLE;

	sf::Color offset(20, 20, 20);
	if (boxShape.getGlobalBounds().contains(mousePosWindow)) {
		mState = ComponentState::CS_HOVER;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			mState = ComponentState::CS_ACTIVE;
		mState = ComponentState::CS_ACTIVE;
	}

	switch (mState) {
	case ComponentState::CS_IDLE:
		checkShape.setFillColor(fill);
		break;
	case ComponentState::CS_HOVER:
		checkShape.setFillColor(fill + offset);
		_isBlocked = false;
		break;
	case ComponentState::CS_ACTIVE:
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && _isBlocked == false) {
			checkShape.setFillColor(fill - offset);

			togleActive();
			_isBlocked = true;
		}
		break;
	}
}

void gui::CheckBox::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(boxShape, states);
	if (_mActive)
		target.draw(checkShape, states);
	target.draw(text, states);
}