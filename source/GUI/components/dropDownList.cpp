#include "dropDownList.hpp"

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font &font, unsigned char_size, std::string list[], unsigned nrOfElements, unsigned default_index)
    : font(font), showList(false), keytimeMax(1.f), keytime(0.f) {
  this->activeElement = new gui::Button(sf::Vector2f(x, y), sf::Vector2f(width, height), list[default_index], gui::styles::buttons::btn_dropdown, gui::type::BUTTON);

  for (unsigned i = 0; i < nrOfElements; i++)
    this->list.push_back(new gui::Button(sf::Vector2f(x, y + ((i + 1) * height)), sf::Vector2f(width, height), list[i], gui::styles::buttons::btn_dropdown, gui::type::BUTTON, i));
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
void gui::DropDownList::updateKeytime(const float &dt) {
  if (this->keytime < this->keytimeMax)
    this->keytime += dt;
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow,
                               const float &dt) {
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
    for (auto &i : this->list) {
      i->update(mousePosWindow);

      if (i->isPressed() && this->getKeytime()) {
        this->showList = false;
        this->activeElement->setText(i->getText());
        this->activeElement->setID(i->getID());
      }
    }
}
