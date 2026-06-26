// Poligone.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Header.h"
#include "gui/pSlider.hpp"
#include "gui/checkbox.hpp"
#include "gui/inventoryGUI.hpp"

int main() {
	sf::RenderWindow win;
	win.create(sf::VideoMode({800, 450}), "Polygon");
	win.setVerticalSyncEnabled(true);
	win.setFramerateLimit(60);

	sf::Clock cl;
	sf::Font font;

	font.openFromFile("C:\\Users\\Xle6y\\source\\repos\\Poligone\\Blackwood Castle.ttf");

	//Slider s(sf::Vector2f(200.f, 50.f), sf::Vector2f(300.f, 30.f), font, 250, 0, 1000);
	//gui::CheckBox chb(sf::Vector2f(200, 115), 30.f, font, "text");
	gui::InventoryGUI invg(sf::Vector2f(win.getSize()),font);

	while (win.isOpen()) {
		cl.restart();
		while (const std::optional event = win.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				win.close();
			}
			if (event->is < sf::Event::Resized>()) {
			//	if (!cr_State.empty()) cr_State.top()->wasUpdateWindon();
			}
			if(event->is<sf::Event::MouseButtonReleased>())
			{ }
		}
	//	auto mPos = win.mapPixelToCoords(sf::Mouse::getPosition(win));

	//	s.update(mPos);
	//	chb.update(mPos);

		win.clear(sf::Color::Black);

		//win.draw(s);
		//win.draw(chb);
		win.draw(invg);

		win.display();
	}
}
