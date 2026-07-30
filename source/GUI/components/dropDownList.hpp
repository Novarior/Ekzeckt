#ifndef GUI_SIMPLE_DROPDOWNLIST_HPP
#define GUI_SIMPLE_DROPDOWNLIST_HPP

#include "button.hpp"

namespace gui {
class DropDownList: sf::Drawable {
private:
	float keytime;
	float keytimeMax;

	sf::Font font;
	gui::Button* activeElement;
	std::vector<gui::Button*> list;
	bool showList;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		target.draw(*this->activeElement, states);

		if (this->showList)
			for (auto& btn : this->list)
				target.draw(*btn, states);
	};

public:
	DropDownList(sf::Vector2f _pos, sf::Vector2f _size, sf::Font& _font, unsigned _charsize, std::string _list[], unsigned _nrOfElements, unsigned _default_index = 0);
	~DropDownList();

	// Accessors
	const unsigned short getActiveElementId() const;

	// Functions
	const bool getKeytime();
	void updateKeytime(const float& dt);
	void update(const sf::Vector2f& mousePosWindow, const float& dt);

}; // namespace gui
} // namespace gui
#endif // !GUI_DROPDOWNLIST_HPP