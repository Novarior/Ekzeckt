#ifndef GFX
#define GFX
#include "../tools/appfn_consts.h"
#include "../header.h"

namespace gfx {
struct myGFXStruct {
	// Variables
	std::string title;
	sf::VideoMode resolution;
	sf::Vector2u _winResolutions;
	bool fullscreen;
	bool verticalSync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	myGFXStruct() {
		title = appfn::path::sfile::app_name;
		verticalSync = false;
		resolution = sf::VideoMode::getDesktopMode();
		videoModes = sf::VideoMode::getFullscreenModes();
		fullscreen = false;
		frameRateLimit = 120;
		contextSettings.antiAliasingLevel = 8;

	}

	void updateResolution(sf::Vector2u _newResolutions) {
		_winResolutions = _newResolutions;
		resolution.size = _newResolutions;
	}
};
}; // namespace gfx
#endif /* GFX */
