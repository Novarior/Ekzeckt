#include "_man_Fonts.hpp"

std::unordered_map<FontID, std::shared_ptr<sf::Font>> FontManager::mFonts;

void FontManager::initialise() {
	mFonts.clear();
}

void FontManager::loadFont(FontID id, std::string path) {
  auto font = std::make_shared<sf::Font>();
  if (font->openFromFile(path)) {
    mFonts[id] = font;
  }
}

void FontManager::loadFont(FontID id, std::filesystem::path path) {
  auto font = std::make_shared<sf::Font>();
  if (font->openFromFile(path)) {
    mFonts[id] = font;
  }
}

std::shared_ptr<sf::Font> FontManager::getFont(FontID id) {
  if (mFonts.find(id) != mFonts.end()) {
    return mFonts[id];
  }
  return nullptr;
}