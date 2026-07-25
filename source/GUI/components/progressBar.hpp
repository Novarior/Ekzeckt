#ifndef GUI_SIMPLE_PROGRESSBAR_HPP
#define GUI_SIMPLE_PROGRESSBAR_HPP
#include "../../core/header.h"

namespace gui {
class ProgressBar:public sf::Drawable {
private:
	sf::Text text;
	
	sf::RectangleShape background, inner;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(this->background);
		target.draw(this->inner);
		target.draw(this->text);
	}
public:
	ProgressBar(sf::Vector2f pos, sf::Vector2f size, unsigned character_size, sf::Font& font, std::string& _str)
		: text(font, _str, character_size) {
		this->background.setSize(size);
		this->background.setFillColor(sf::Color(30, 40, 65));
		this->background.setPosition(pos);

		this->inner.setSize(size);
		this->inner.setFillColor(sf::Color(90, 120, 185));
		this->inner.setPosition(pos);

		this->text.setOutlineThickness(-1.f);
		this->text.setPosition({pos.x + (size.x * 0.5f) - (this->text.getGlobalBounds().size.x * 0.5f),
								pos.y + (size.y * 0.5f) - (this->text.getGlobalBounds().size.y * 0.5f)});
	}
	~ProgressBar() {}

	// Accessors

	// Modifiers

	// Functions
	void update(const float current_value, const float max_value) {// calculate percentage and update inner bar
		float percent = (current_value / max_value);
		this->inner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->background.getSize().x * percent)), this->inner.getSize().y));

		this->text.setString(std::to_string(int(current_value)).append(" / ").append(std::to_string(int(max_value))));
	}
};
} // namespace gui
#endif // !GUI_PROGRESSBAR_HPP