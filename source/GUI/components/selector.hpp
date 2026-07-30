#ifndef GUI_SIMPLE_SELECTOR_HPP
#define GUI_SIMPLE_SELECTOR_HPP

#include "button.hpp"
namespace gui {
class Selector {
private:
	std::map<std::string, gui::Button*> buttons;
	std::vector<std::string> list;
	sf::Text text;
	unsigned int activeElement;
	sf::RectangleShape box;

	float keytime;
	float keytimeMax;

public:
	Selector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font, unsigned int character_size, std::string list[], unsigned nrOfElements, unsigned default_active_element = 0);
	virtual ~Selector();

	// accessors
	unsigned getActiveElementID() const;
	std::string getActiveElement() const;
	void setActiveElement(unsigned int id);

	void update(const float& delta_time, const sf::Vector2f& mousePos);
	void updateKeyTime(const float& delta_time);
	const bool getKeytime();
	// render
	void render(sf::RenderTarget& target);
};
} // namespace gui
#endif // GUI_SELECTOR_HPP