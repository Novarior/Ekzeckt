#ifndef GFX
#define GFX
#include "../_myConst.h"
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
    title = myConst::app_name;
    verticalSync = false;
    resolution = sf::VideoMode::getDesktopMode();
    videoModes = sf::VideoMode::getFullscreenModes();
    fullscreen = false;
    frameRateLimit = 120;
    contextSettings.antiAliasingLevel = 8;
    
  }
};
}; // namespace gfx
#endif /* GFX */
