#include "button.hpp"

gui::Button::Button(sf::Vector2f position, sf::Vector2f size, std::string _text, std::string style, std::string _type, unsigned id) {

	mData.state = ComponentState::IDLE;
	mData.isActive = true;
	mData.id = id;
	mData.textString = _text;
	mData.position = position;
	mData.size = size;

	loadStyle(style, _type);

	mDraw.shape.setPosition(sf::Vector2f(position.x, position.y));
	mDraw.shape.setSize(sf::Vector2f(size.x, size.y));
	mDraw.shape.setFillColor(mColors.shapeIdleColor);
	mDraw.shape.setOutlineThickness(-1.f);
	mDraw.shape.setOutlineColor(mColors.outlineIdleColor);

	mDraw.text.setFont(mData.font);
	mDraw.text.setFillColor(mColors.textIdleColor);
	mDraw.text.setCharacterSize(mData.characterSize);
	mDraw.text.setPosition({mData.position.x + (mData.size.x / 2.f) - mDraw.text.getGlobalBounds().size.x / 2.f,
							mData.position.y + mData.size.y / 2 + mDraw.text.getGlobalBounds().size.y / 2.f});
	mDraw.text.setString(mData.textString);
}


// Accessors

// Modifiers

// Functions
