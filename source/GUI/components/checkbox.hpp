#ifndef GUI_SIMPLE_CHECKBOX_HPP
#define GUI_SIMPLE_CHECKBOX_HPP

#include "../../core/header.h"

namespace gui {

class CheckBox: public sf::Drawable {
private:
	short unsigned checkboxState;
	bool bChecked;
	bool was_pressed = false;

	sf::RectangleShape boxShape;
	sf::RectangleShape checkShape;
	sf::Text text;

	sf::Color textIdleColor;
	sf::Color textHoverColor;
	sf::Color textActiveColor;

	sf::Color uncheckedIdleColor;
	sf::Color uncheckedHoverColor;
	sf::Color uncheckedActiveColor;

	sf::Color checkedIdleColor;
	sf::Color checkedHoverColor;
	sf::Color checkedActiveColor;

	sf::Color outlineIdleColor;
	sf::Color outlineHoverColor;
	sf::Color outlineActiveColor;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(boxShape, states);
		if (bChecked)
			target.draw(checkShape, states);
		target.draw(text, states);
	}

public:

	CheckBox(sf::Vector2f _pos, sf::Vector2f _size, sf::Font& _font, std::string _text, unsigned _charsize, bool _init = false);
	~CheckBox();

	// Accessors
	const bool isChecked() const;
	const bool isPressed() const;
	const bool isHover() const;

	// Modifiers
	void setText(const std::string text);
	void setChecked(const bool checked);
	void toggle();

	// Functions
	void update(const sf::Vector2i& mousePosWindow);
};

} // namespace gui
#endif // GUI_SIMPLE_CHECKBOX_HPP