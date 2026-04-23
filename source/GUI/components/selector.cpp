#include "selector.hpp"
#include "../../math/mymath.hpp"

namespace gui {

Selector::Selector(sf::Vector2f pos, sf::Vector2f size, sf::Font &font,
                   unsigned int character_size, std::string list[],
                   unsigned nrOfElements, unsigned default_active_element)
    : keytime(0.f), keytimeMax(0.3f), text(font, "", character_size) {
  // init box
  this->box.setPosition({pos.x + (mmath::p2pX(10, size.x)), pos.y});
  this->box.setSize(sf::Vector2f(size.x - (mmath::p2pX(20, size.x)), size.y));
  this->box.setFillColor(sf::Color(50, 50, 50, 100));
  this->box.setOutlineThickness(-1.f);
  this->box.setOutlineColor(sf::Color(40, 40, 40, 120));

  // init buttons
  this->buttons["left"] = new gui::Button(
      sf::Vector2f(pos.x, pos.y), sf::Vector2f(mmath::p2pX(15, size.x), size.y),
      "-", gui::styles::buttons::btn_selector, gui::type::BUTTON);

  this->buttons["right"] = new gui::Button(
      sf::Vector2f(this->box.getPosition().x + this->box.getSize().x, pos.y),
      sf::Vector2f(mmath::p2pX(15, size.x), size.y), "+",
      gui::styles::buttons::btn_selector, gui::type::BUTTON);

  // init text
  this->text.setString(list[0]);
  this->text.setPosition(
      {this->box.getPosition().x + (this->box.getSize().x / 2.f -
                                    this->text.getGlobalBounds().size.x / 2.f),
       this->box.getPosition().y + this->text.getGlobalBounds().size.y / 2.f});
  this->text.setFillColor(sf::Color(255, 255, 255, 200));

  // init list
  for (size_t i = 0; i < nrOfElements; i++)
    this->list.push_back(list[i]);

  // init active element
  this->activeElement = default_active_element;
  this->text.setString(this->list[this->activeElement]);
}

Selector::~Selector() {
  for (auto &it : this->buttons)
    delete it.second;
}

unsigned Selector::getActiveElementID() const { return this->activeElement; }

std::string Selector::getActiveElement() const {
  return this->list[this->activeElement];
}

void Selector::setActiveElement(unsigned int id) {
  this->activeElement = id;
  this->text.setString(this->list[id]);
}

void Selector::update(const float &delta_time, const sf::Vector2i &mousePos) {
  for (auto &it : this->buttons)
    it.second->update(mousePos);

  this->updateKeyTime(delta_time);

  if (this->buttons["left"]->isPressed() && this->getKeytime()) {
    if (this->activeElement > 0)
      activeElement--;
    else
      activeElement = this->list.size() - 1;
    this->text.setString(this->list[this->activeElement]);
  } else if (this->buttons["right"]->isPressed() && this->getKeytime()) {
    if (this->activeElement >= this->list.size() - 1)
      activeElement = 0;
    else
      activeElement++;
    this->text.setString(this->list[this->activeElement]);
  }
  this->text.setPosition(
      {this->box.getPosition().x + (this->box.getSize().x / 2.f -
                                    this->text.getGlobalBounds().size.x / 2.f),
       this->box.getPosition().y + -this->text.getGlobalBounds().size.y / 2.f});
}

void Selector::updateKeyTime(const float &delta_time) {
  if (this->keytime < this->keytimeMax)
    this->keytime += delta_time;
}

const bool Selector::getKeytime() {
  if (this->keytime >= this->keytimeMax) {
    this->keytime = 0.f;
    return true;
  }
  return false;
}

void Selector::render(sf::RenderTarget &target) {
  target.draw(this->box);

  for (auto &it : this->buttons)
    target.draw(*it.second);

  target.draw(this->text);
}
} // namespace gui