#ifndef CPP_STATE_PAUSE_HPP
#define CPP_STATE_PAUSE_HPP

#include "../GUI/components/button.hpp"
#include "../core/header.h"

class PauseMenu {
private:
	// Variables
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, std::shared_ptr< gui::Button>> buttons;
public:
	PauseMenu(sf::Vector2f resolution, sf::Font& font, std::string& text);
	virtual ~PauseMenu();

	// Accessor
	inline const std::map<std::string, std::shared_ptr<gui::Button>>& getButtons() const { return buttons; }

	// Functions
	const bool isButtonPressed(const std::string key);
	// add button for additionall layout (auto centred by x-axis)
	// pos and size should be 0-100
	void addButton(float btnPosY, sf::Vector2f btnSize, unsigned char_size, std::string key, std::string text);

	void update(const sf::Vector2i& mousePosWindow);
	void render(sf::RenderTarget& target);
};
#endif