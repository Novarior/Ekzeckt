#include "selector.hpp"
#include "../../core/math/mymath.hpp"

namespace gui {

Selector::Selector(sf::Vector2f pos, sf::Vector2f size, sf::Font& font,
				   unsigned int character_size, std::string list[],
				   unsigned nrOfElements, unsigned default_active_element)
	: keytime(0.f), keytimeMax(0.3f), text(font, "", character_size) {
	// init box
	 box.setPosition({pos.x + (mmath::p2pX(10.f, size.x)), pos.y});
	 box.setSize(sf::Vector2f(size.x - (mmath::p2pX(20.f, size.x)), size.y));
	 box.setFillColor(sf::Color(50, 50, 50, 100));
	 box.setOutlineThickness(-1.f);
	 box.setOutlineColor(sf::Color(40, 40, 40, 120));

	// init buttons
	 buttons["left"] = new gui::Button(sf::Vector2f(pos.x, pos.y), sf::Vector2f(mmath::p2pX(15.f, size.x), size.y), "-", gui::styles::buttons::btn_selector, gui::type::BUTTON);

	 buttons["right"] = new gui::Button(sf::Vector2f( box.getPosition().x +  box.getSize().x, pos.y), sf::Vector2f(mmath::p2pX(15.f, size.x), size.y), "+", gui::styles::buttons::btn_selector, gui::type::BUTTON);

	// init text
	 text.setString(list[0]);
	 text.setPosition({ box.getPosition().x + ( box.getSize().x / 2.f -  text.getGlobalBounds().size.x / 2.f),  box.getPosition().y +  text.getGlobalBounds().size.y / 2.f});
	 text.setFillColor(sf::Color(255, 255, 255, 200));

	// init list
	for (size_t i = 0; i < nrOfElements; i++)
		this-> list.push_back(list[i]);

	// init active element
	 activeElement = default_active_element;
	 text.setString( list[ activeElement]);
}

Selector::~Selector() {
	for (auto& it :  buttons)
		delete it.second;
}

unsigned Selector::getActiveElementID() const { return  activeElement; }

std::string Selector::getActiveElement() const {
	return  list[ activeElement];
}

void Selector::setActiveElement(unsigned int id) {
	 activeElement = id;
	 text.setString( list[id]);
}

void Selector::update(const float& delta_time, const sf::Vector2i& mousePos) {
	for (auto& it :  buttons)
		it.second->update(mousePos);

	 updateKeyTime(delta_time);

	if ( buttons["left"]->isPressed() &&  getKeytime()) {
		if ( activeElement > 0)
			activeElement--;
		else
			activeElement =  list.size() - 1;
		 text.setString( list[ activeElement]);
	} else if ( buttons["right"]->isPressed() &&  getKeytime()) {
		if ( activeElement >=  list.size() - 1)
			activeElement = 0;
		else
			activeElement++;
		 text.setString( list[ activeElement]);
	}
	 text.setPosition(
		{ box.getPosition().x + ( box.getSize().x / 2.f -  text.getGlobalBounds().size.x / 2.f),
		  box.getPosition().y + - text.getGlobalBounds().size.y / 2.f});
}

void Selector::updateKeyTime(const float& delta_time) {
	if ( keytime <  keytimeMax)
		 keytime += delta_time;
}

const bool Selector::getKeytime() {
	if ( keytime >=  keytimeMax) {
		 keytime = 0.f;
		return true;
	}
	return false;
}

void Selector::render(sf::RenderTarget& target) {
	target.draw( box);

	for (auto& it :  buttons)
		target.draw(*it.second);

	target.draw( text);
}
} // namespace gui