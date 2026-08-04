#pragma once

#include "../core/header.h"

struct ComponentColors {
	// idle color
	sf::Color shapeIdleColor;
	sf::Color outlineIdleColor;
	sf::Color textIdleColor;
	//hover color
	sf::Color shapeHoverColor;
	sf::Color outlineHoverColor;
	sf::Color textHoverColor;
	// active color (clicked or other activation method)
	sf::Color shapeActiveColor;
	sf::Color outlineActiveColor;
	sf::Color textActiveColor;
	// disabled color
	sf::Color shapeDisableColor;
	sf::Color outlineDisableColor;
	sf::Color textDisableColor;

	sf::Color textOutlineColor = sf::Color::Black; // default value

	// one color for all
	ComponentColors() {
		// idle color (base)
		shapeIdleColor = sf::Color(30, 40, 65);     
		outlineIdleColor = sf::Color(20, 28, 45);    
		textIdleColor = sf::Color(180, 200, 220);    

		// hover color (lighter, more saturated)
		shapeHoverColor = sf::Color(50, 65, 95);    
		outlineHoverColor = sf::Color(30, 40, 65);    
		textHoverColor = sf::Color(210, 230, 255);   

		// active color (most saturated, brightest)
		shapeActiveColor = sf::Color(70, 90, 130);    
		outlineActiveColor = sf::Color(50, 65, 95);    
		textActiveColor = sf::Color(255, 255, 255);   

		// disable color (more gray, less saturated)
		shapeDisableColor = sf::Color(60, 65, 75);    
		outlineDisableColor = sf::Color(40, 45, 55);   
		textDisableColor = sf::Color(100, 110, 125);
	}

	ComponentColors(const std::vector<sf::Color>& colors) {
		if (colors.size() >= 12) {
			// idle color
			shapeIdleColor = colors[0];
			outlineIdleColor = colors[1];
			textIdleColor = colors[2];
			// hover color
			shapeHoverColor = colors[3];
			outlineHoverColor = colors[4];
			textHoverColor = colors[5];
			// active color
			shapeActiveColor = colors[4];
			outlineActiveColor = colors[6];
			textActiveColor = colors[10];
			// disable color
			shapeDisableColor = colors[5];
			outlineDisableColor = colors[7];
			textDisableColor = colors[11];
		} else {
			throw std::invalid_argument("Not enough colors provided!");
		}
	}

};