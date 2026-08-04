#pragma once

#include "../core/header.h"

struct ComponentData {
	std::shared_ptr<sf::Font> font;
	std::string textString;
	sf::Vector2f position;
	sf::Vector2f size;
	unsigned characterSize;
	bool isActive;

	ComponentData(sf::Vector2f _position, sf::Vector2f _size,
				 std::shared_ptr<sf::Font> _font,
				 unsigned _characterSize, bool _isActive)
		: position(_position), size(_size), font(_font),
		characterSize(_characterSize), isActive(_isActive) {}

	ComponentData& operator=(const ComponentData& right) {
		if (this == &right)
			return *this;
		textString = right.textString;
		position = right.position;
		size = right.size;
		characterSize = right.characterSize;
		isActive = right.isActive;
	}
};