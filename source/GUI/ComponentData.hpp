#pragma once

#include "../core/header.h"

struct ComponentData {
	ComponentData(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<sf::Font> _font,
				  unsigned _characterSize, bool _isActive)
		: position(_position), size(_size), font(_font),
		characterSize(_characterSize), isActive(_isActive) {
		
	}

	std::shared_ptr<sf::Font> font;
	std::string textString;
	sf::Vector2f position;
	sf::Vector2f size;
	unsigned characterSize;
	bool isActive;
};