#ifndef GUI_SIMPLE_BUTTON_HPP
#define GUI_SIMPLE_BUTTON_HPP

#include "../GUI_Component.hpp"
#include <string>

namespace gui {
class Button: public GuiComponent {
private:
public:
	Button(sf::Vector2f position, sf::Vector2f size, std::string _text, std::string style, std::string _type, unsigned id = 0);
	virtual ~Button() {}
};
} // namespace gui
#endif // GUI_BUTTON_HPP