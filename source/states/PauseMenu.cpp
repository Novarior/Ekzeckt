#include "PauseMenu.hpp"

PauseMenu::PauseMenu(sf::VideoMode vm, sf::Font &font)
    : font(font), menuText(font, "PAUSED", mmath::calcCharSize(vm)) {
  // logger
  Logger::logStatic("PauseMenu constructor", "PauseMenu");
  // Init background
  this->background.setSize(sf::Vector2f(static_cast<float>(vm.size.x),
                                        static_cast<float>(vm.size.y)));
  this->background.setFillColor(sf::Color(30, 30, 30, 100));

  // Init container
  this->container.setSize(
      sf::Vector2f(static_cast<float>(vm.size.x) / 2.5f,
                   static_cast<float>(vm.size.y) - mmath::p2pX(9.3f, vm)));

  this->container.setFillColor(sf::Color(30, 30, 30, 180));
  this->container.setPosition(
      {static_cast<float>(vm.size.x) / 2.f - this->container.getSize().x / 2.f,
       30.f});

  // Init text
  this->menuText.setFillColor(sf::Color(200, 200, 200, 255));
  this->menuText.setPosition(
      {this->container.getPosition().x + this->container.getSize().x / 2.f -
           this->menuText.getGlobalBounds().size.x / 2.f,
       this->container.getPosition().y + mmath::p2pX(4.f, vm)});
}

PauseMenu::~PauseMenu() {
  // logger
  Logger::logStatic("PauseMenu destructor", "PauseMenu");

  auto it = this->buttons.begin();
  for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
    delete it->second;
  }
}

std::map<std::string, gui::Button *> &PauseMenu::getButtons() {
  return this->buttons;
}

// Functions
const bool PauseMenu::isButtonPressed(const std::string key) {
  return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(std::string key, float y, float width, float height,
                          unsigned char_size, std::string text) {
  float x = this->container.getPosition().x +
            this->container.getSize().x / 2.f - width / 2.f;

  this->buttons[key] =
      new gui::Button(sf::Vector2f(x, y), sf::Vector2f(width, height), text,
                      gui::styles::buttons::btn_pause, gui::type::BUTTON);

#ifdef __MDEBUG__ == 1
  Logger::logStatic("PauseMenu::addButton: " + key, "PauseMenu");

#endif
}

void PauseMenu::update(const sf::Vector2i &mousePosWindow) {
  for (auto &i : this->buttons) {
    i.second->update(mousePosWindow);
  }
}

void PauseMenu::render(sf::RenderTarget &target) {
  target.draw(this->background);
  target.draw(this->container);

  for (auto &i : this->buttons) {
    target.draw(*i.second);
  }
  target.draw(this->menuText);
}