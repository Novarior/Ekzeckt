#ifndef GUI_SIMPLE_STATIC_SELECTOR_HPP
#define GUI_SIMPLE_STATIC_SELECTOR_HPP

#include "button.hpp"
namespace gui {
class StaticSelector {
private:
	std::map<std::string, gui::Button*> buttons;
	float valueMax;
	float value;
	float sizeStep;
	sf::Text text;
	std::string additionaText;
	bool addritionalText_flag;
	unsigned int activeElement;
	sf::RectangleShape box;

	float keytime;
	float keytimeMax;

	bool ValueIsChanged;

	void updateKeyTime(const float& delta_time);
	const bool getKeytime();

public:
	StaticSelector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font,
				   unsigned int character_size, float current_value = 0.f, float max_value = 10.f,
				   float change_step = 1.f, bool addritional_text = false, std::string add_text = "");
	virtual ~StaticSelector();

	const bool isValueChanged();
	void closeChangeValue();
	// accessors
	const float getCurrentValue();
	void setCurrentValue(const float value);
	void setSizeStep(const float size_step);

	void update(const float& delta_time, const sf::Vector2i& mousePos);

	// render
	void render(sf::RenderTarget& target);
};
}; // namespace gui
#endif // GUI_STATIC_SELECTOR_HPP