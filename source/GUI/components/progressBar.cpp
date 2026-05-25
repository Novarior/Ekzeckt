#include "progressBar.hpp"
#include "../../core/math/mymath.hpp"

gui::ProgressBar::ProgressBar(sf::Vector2f pos, sf::Vector2f size, sf::Color inner_color, unsigned character_size, sf::Font& font)
	: text(font, "", character_size) {
	this->background.setSize(size);
	this->background.setFillColor(sf::Color(50, 50, 50, 200));
	this->background.setPosition(pos);

	this->inner.setSize(size);
	this->inner.setFillColor(inner_color);
	this->inner.setPosition(this->background.getPosition());

	this->text.setOutlineThickness(-3.f);
	this->text.setPosition({this->background.getPosition().x + (this->background.getSize().x * 0.5f) - (this->text.getGlobalBounds().size.x * 0.5f),
							this->background.getPosition().y + (this->background.getSize().y * 0.5f) - (this->text.getGlobalBounds().size.y * 0.5f)});
}

gui::ProgressBar::~ProgressBar() {}

// Functions
void gui::ProgressBar::update(const float current_value, const float max_value) {
	// calculate percentage and update inner bar
	float percent = (current_value / max_value);
	this->inner.setSize(sf::Vector2f(static_cast<float>(std::floor(this->background.getSize().x * percent)), this->inner.getSize().y));

	// update text string
	// cut to 1 decimal places from current_value and max_value
	std::string current_value_str = std::to_string(current_value);
	std::string max_value_str = std::to_string(max_value);
	current_value_str = current_value_str.substr(0, current_value_str.find(".") + 2);
	max_value_str = max_value_str.substr(0, max_value_str.find(".") + 2);

	this->barString = current_value_str + " / " + max_value_str;
	this->text.setString(this->barString);
	this->text.setPosition({this->background.getPosition().x + (this->background.getSize().x * 0.5f) - (this->text.getGlobalBounds().size.x * 0.5f),
							this->background.getPosition().y + (this->background.getSize().y * 0.5f) -
						   (this->text.getGlobalBounds().size.y) + mmath::p2pX(20.f, this->background.getSize().y)});
}

void gui::ProgressBar::render(sf::RenderTarget& target) {
	target.draw(this->background);
	target.draw(this->inner);
	target.draw(this->text);
}