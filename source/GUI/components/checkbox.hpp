#ifndef GUI_SIMPLE_CHECKBOX_HPP
#define GUI_SIMPLE_CHECKBOX_HPP

#include "../../core/header.h"

#include "../GUI_Component.hpp"


namespace gui {
class CheckBox: public GuiComponent {
private:
	bool _mActive;
	bool _isBlocked = false;

	sf::RectangleShape boxShape, checkShape;
	sf::Text text;

	sf::Color backfill = sf::Color(30, 40, 65);
	sf::Color fill = sf::Color(90, 120, 185);

public:
	CheckBox(sf::Vector2f _pos, float _size, sf::Font& _font, std::string _text, bool _init = false, unsigned _charsize = 20U);
	~CheckBox();

	// Accessors


	// Modifiers 

	// Functions
	void update(const sf::Vector2f& mousePosWindow) override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
} // namespace gui
#endif // GUI_SIMPLE_CHECKBOX_HPP