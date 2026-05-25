#include "dropDownList.hpp"

gui::DropDownList::DropDownList(sf::Vector2f _pos, sf::Vector2f _size, sf::Font& _font, unsigned _charsize, std::string _list[], unsigned _nrOfElements, unsigned _default_index)
	: font(_font), showList(false), keytimeMax(1.f), keytime(0.f) {
	this->activeElement = new gui::Button(_pos, _size, _list[_default_index], gui::styles::buttons::btn_dropdown, gui::type::BUTTON);

	for (unsigned i = 0; i < _nrOfElements; i++)
		this->list.push_back(new gui::Button(sf::Vector2f(_pos.x, _pos.y + ((i + 1) * _size.y)), _size, _list[i], gui::styles::buttons::btn_dropdown, gui::type::BUTTON, i));
}

gui::DropDownList::~DropDownList() {
	delete this->activeElement;
	for (size_t i = 0; i < this->list.size(); i++)
		delete this->list[i];
}

// Accessors
const bool gui::DropDownList::getKeytime() {
	if (this->keytime >= this->keytimeMax) {
		this->keytime = 0.f;
		return true;
	}
	return false;
}

const unsigned short gui::DropDownList::getActiveElementId() const {
	return this->activeElement->getID();
}

// Functions
void gui::DropDownList::updateKeytime(const float& dt) {
	if (this->keytime < this->keytimeMax)
		this->keytime += dt;
}

void gui::DropDownList::update(const sf::Vector2i& mousePosWindow,
							   const float& dt) {
	this->updateKeytime(dt);

	this->activeElement->update(mousePosWindow);

	// Show and hide the list
	if (this->activeElement->isPressed() && this->getKeytime()) {

		if (this->showList)
			this->showList = false;
		else
			this->showList = true;
	}

	if (this->showList)
		for (auto& i : this->list) {
			i->update(mousePosWindow);

			if (i->isPressed() && this->getKeytime()) {
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setID(i->getID());
			}
		}
}
