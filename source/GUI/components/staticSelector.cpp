#include "staticSelector.hpp"
#include "../../math/mymath.hpp"

namespace gui {
// private functions
void StaticSelector::updateKeyTime(const float &delta_time) {
  if (this->keytime < this->keytimeMax)
    this->keytime += delta_time;
}

const bool StaticSelector::getKeytime() {
  if (this->keytime >= this->keytimeMax) {
    this->keytime = 0.f;
    return true;
  }
  return false;
}

/**
 * @brief Constructs a new StaticSelector object.
 *
 * @param pos The position of the selector.
 * @param size The size of the selector.
 * @param font The font used for the text in the selector.
 * @param character_size The size of the characters in the text.
 * @param current_value The initial value of the selector.
 * @param max_value The maximum value the selector can have.
 * @param change_step The step size for changing the value.
 * @param addritional_text Flag indicating whether additional text should be
 * displayed.
 * @param add_text The additional text to be displayed if addritional_text is
 * true.
 *
 * @details Initializes the selector's box, text, and buttons. The box is
 * positioned and sized according to the given parameters. The text is set with
 * the given font and character size, and positioned in the center of the box.
 * Two buttons are created for incrementing and decrementing the value,
 * positioned on the left and right of the box respectively. If additional text
 * is to be displayed, it is set according to the add_text parameter.
 */
StaticSelector::StaticSelector(sf::Vector2f pos, sf::Vector2f size,
                               sf::Font &font, unsigned int character_size,
                               float current_value, float max_value,
                               float change_step, bool addritional_text,
                               std::string add_text)
    : valueMax(max_value), keytimeMax(0.1f), keytime(0.f), value(current_value),
      sizeStep(change_step), text(font, "", character_size) {
  // init box
  this->box.setPosition({pos.x + (mmath::p2pX(10, size.x)), pos.y});
  this->box.setSize(sf::Vector2f(size.x - (mmath::p2pX(20, size.x)), size.y));
  this->box.setFillColor(sf::Color(50, 50, 50, 100));
  this->box.setOutlineThickness(-1.f);
  this->box.setOutlineColor(sf::Color(40, 40, 40, 120));
  // init text
  this->text.setFillColor(sf::Color(255, 255, 255, 200));
  this->text.setPosition(
      {this->box.getPosition().x + this->box.getSize().x / 2.f -
           this->text.getGlobalBounds().size.x / 2.f,
       this->box.getPosition().y + this->box.getSize().y / 2.f -
           this->text.getGlobalBounds().size.y / 2.f});
  // init value's

  // init buttons
  this->buttons["left"] = new gui::Button(
      sf::Vector2f(pos.x, pos.y), sf::Vector2f(mmath::p2pX(10, size.x), size.y),
      "-", gui::styles::buttons::btn_selector, gui::type::BUTTON);

  this->buttons["right"] = new gui::Button(
      sf::Vector2f(this->box.getPosition().x + this->box.getSize().x, pos.y),
      sf::Vector2f(mmath::p2pX(10, size.x), size.y), "+",
      gui::styles::buttons::btn_selector, gui::type::BUTTON);

  this->addritionalText_flag = addritional_text;
  if (this->addritionalText_flag)
    this->additionaText = add_text;
}

StaticSelector::~StaticSelector() {
  for (auto &it : this->buttons)
    delete it.second;
}

// accessors
const float StaticSelector::getCurrentValue() { return this->value; }
void StaticSelector::setCurrentValue(const float value) { this->value = value; }
void StaticSelector::setSizeStep(const float size_step) {
  this->sizeStep = size_step;
}

const bool StaticSelector::isValueChanged() { return this->ValueIsChanged; }

void StaticSelector::closeChangeValue() { this->ValueIsChanged = false; }

void StaticSelector::update(const float &delta_time,
                            const sf::Vector2i &mousePos) {
  this->updateKeyTime(delta_time);

  for (auto &it : this->buttons)
    it.second->update(mousePos);

  if (this->buttons["left"]->isPressed() && this->getKeytime()) {
    if (this->value > -this->valueMax)
      this->value -= this->sizeStep;
    else
      this->value = this->valueMax;

    this->ValueIsChanged = true;
  }

  if (this->buttons["right"]->isPressed() && this->getKeytime()) {
    if (this->value < this->valueMax)
      this->value += this->sizeStep;
    else
      this->value = -this->valueMax;

    this->ValueIsChanged = true;
  }
  std::stringstream ss;
  if (this->addritionalText_flag && this->additionaText != "")
    ss << this->additionaText;
  ss << std::fixed << std::setprecision(1) << this->value;

  this->text.setString(ss.str());
  this->text.setPosition(
      {this->box.getPosition().x + this->box.getSize().x / 2.f -
           this->text.getGlobalBounds().size.x / 2.f,
       this->box.getPosition().y + this->box.getSize().y / 2.f -
           this->text.getGlobalBounds().size.y / 2.f});
}

// render
void StaticSelector::render(sf::RenderTarget &target) {
  target.draw(this->box);
  for (auto &it : this->buttons)
    target.draw(*it.second);

  target.draw(this->text);
}
} // namespace gui
  // namespace gui