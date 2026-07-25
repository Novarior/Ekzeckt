#include "PauseMenu.hpp"
#include "../core/tools/LOGGER.hpp"
#include "../core/math/mymath.hpp"

PauseMenu::PauseMenu(sf::Vector2f resolution, sf::Font& font, std::string& text):menuText(sf::Text(font)) {
	menuText = sf::Text(font, text, mmath::calcCharSize(resolution.x, resolution.y));

	// logger
	Logger::logStatic("PauseMenu constructor", "PauseMenu");
	// Init background
	sf::Vector2f offset = resolution / 6.f;

	background.setSize(resolution);
	background.setFillColor(sf::Color(0, 0, 0, 100));

	// Init container
	container.setSize(offset);

	container.setFillColor(sf::Color(30, 30, 30, 180));
	container.setPosition(offset);

	// Init text
	menuText.setFillColor(sf::Color(200, 200, 200, 255));
	menuText.setPosition({container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().size.x / 2.f,  container.getPosition().y + mmath::p2pX(4.f, offset.x)});
}

PauseMenu::~PauseMenu() {
	Logger::logStatic("PauseMenu destructor", "PauseMenu");
	buttons.clear();
}



// Functions
const bool PauseMenu::isButtonPressed(const std::string key) {
	return  buttons[key]->isPressed();
}

void PauseMenu::addButton(std::string key, float y, float width, float height, unsigned char_size, std::string text) {
	auto x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;

	buttons[key] = std::make_shared<gui::Button>(sf::Vector2f(x, y), sf::Vector2f(width, height), text, gui::styles::buttons::btn_pause, gui::type::BUTTON);

#ifdef __MDEBUG__
	Logger::logStatic("PauseMenu::addButton: " + key, "PauseMenu");
#endif
}

void PauseMenu::update(const sf::Vector2i& mousePosWindow) {
	for (auto& i : buttons)
		i.second->update(mousePosWindow);
}

void PauseMenu::render(sf::RenderTarget& target) {
	target.draw(background);
	target.draw(container);

	for (auto& i : buttons)
		target.draw(*i.second);

	target.draw(menuText);
}