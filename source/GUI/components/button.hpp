#ifndef GUI_SIMPLE_BUTTON_HPP
#define GUI_SIMPLE_BUTTON_HPP

#include "../GUI_Component.hpp"

namespace gui {
class Button: public GuiComponent {
private:
	sf::RectangleShape mShape;
	sf::Text mText;
	unsigned int mID;
public:
	//Button() {}
	Button(sf::Vector2f position, sf::Vector2f size, std::string text, unsigned int id = 0U);
	~Button() {}

	const unsigned int getID() const;
	void setID(const unsigned int val);

	void setText(const std::string val);
	const std::string getText() const;


	void setPosition(const sf::Vector2f pos) override;
	void update(const sf::Vector2f& mousePos) override;
	void updateColor() override;
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
} // namespace gui
#endif // GUI_BUTTON_HPP