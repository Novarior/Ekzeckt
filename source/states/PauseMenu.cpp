#include "PauseMenu.hpp"
#include "../core/tools/LOGGER.hpp"
#include "../core/math/mymath.hpp"

PauseMenu::PauseMenu(sf::Vector2f resolution, sf::Font& font, std::string& text):menuText(sf::Text(font)) {
	menuText = sf::Text(font, text, mmath::calcCharSize(resolution.x, resolution.y));

	// logger
	Logger::logStatic("PauseMenu constructor", "PauseMenu");
	// Init background

	background.setSize(resolution);
	background.setFillColor(sf::Color(0, 0, 0, 100));

	// Init container
	float constSizeX = resolution.x / 3.f;
	float contPosX = (resolution.x / 2.f) - (constSizeX / 2.f);

	container.setSize({constSizeX,resolution.y});
	container.setFillColor(sf::Color(30, 30, 30, 180));
	container.setPosition({contPosX,0.f});

	// Init text
	menuText.setFillColor(sf::Color(200, 200, 200, 255));
	menuText.setPosition({container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().size.x / 2.f,  container.getPosition().y + mmath::p2pX(4.f, constSizeX)});
}

PauseMenu::~PauseMenu() {
	Logger::logStatic("PauseMenu destructor", "PauseMenu");
	buttons.clear();
}



// Functions
const bool PauseMenu::isButtonPressed(const std::string key) {
	return  buttons[key]->isPressed();
}

void PauseMenu::addButton(float btnPosY, sf::Vector2f btnSize, unsigned char_size, std::string key, std::string text) {
	auto contsize = container.getSize();
	sf::Vector2f Size(mmath::p2pX(btnSize.x, contsize.x), mmath::p2pX(btnSize.y, contsize.y));

	float posx = container.getPosition().x + container.getSize().x / 2.f - Size.x / 2.f;
	sf::Vector2f Pos(posx, mmath::p2pX(btnPosY, contsize.y));


	buttons[key] = std::make_shared<gui::Button>(Pos, Size, text, gui::styles::buttons::btn_pause, gui::type::BUTTON);

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