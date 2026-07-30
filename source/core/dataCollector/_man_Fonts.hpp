#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>

enum class FontID{
FONT_GAMEF_01,
FONT_DEBUG
};

class FontManager {
private:
	static std::unordered_map<FontID, std::shared_ptr<sf::Font>> mFonts;

public:
	static void initialise();
	static void loadFont(FontID id, std::string path);
	static void loadFont(FontID id, std::filesystem::path path);
	static std::shared_ptr<sf::Font> getFont(FontID id);
};