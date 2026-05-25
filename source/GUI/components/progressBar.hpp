#ifndef GUI_SIMPLE_PROGRESSBAR_HPP
#define GUI_SIMPLE_PROGRESSBAR_HPP
#include "../../core/header.h"

namespace gui {
class ProgressBar {
private:
	std::string barString;
	sf::Text text;
	float maxWidth;
	sf::RectangleShape background;
	sf::RectangleShape inner;

public:
	ProgressBar(sf::Vector2f pos, sf::Vector2f size, sf::Color inner_color, unsigned character_size, sf::Font& font);
	~ProgressBar();

	// Accessors

	// Modifiers

	// Functions
	void update(const float current_value, const float max_value);
	void render(sf::RenderTarget& target);
};
} // namespace gui
#endif // !GUI_PROGRESSBAR_HPP