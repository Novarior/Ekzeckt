#ifndef CORE
#define CORE

#include "../states/State.hpp"
#include "dataCollector/_man_Volume.hpp"
#include "gfx.hpp"

class Core {
private:
  // window <3
  std::shared_ptr<sf::RenderWindow> cr_Window;
  // Clock and timeб
  float cr_deltaTime;
  sf::Clock cr_deltaClock;
  // Data (keyboard, Graph)
  std::shared_ptr<keyboardOSX> cr_Keyboard;
  std::shared_ptr<std::map<std::string, uint32_t>> cr_KeySuppors;
  std::shared_ptr<std::map<std::string, uint32_t>> cr_KeyBinds;
  // VolCollector, sound buffer and sound map
  std::shared_ptr<VolumeCollector> cr_VolumeCollector;
  std::shared_ptr<std::map<std::string, sf::Sound>> cr_SoundMap;
  std::shared_ptr<std::map<std::string, sf::Sound>> cr_SoundBufferMap;
  // fonts
  sf::Font cr_GameFont_basic; // Font used in the game
  sf::Font cr_debugFont;      // Font used for debugging
  // graphics settings
  std::shared_ptr<GraphicsSettings> cr_gfxSettings;
  // just const float (no, actually very important item)))
  const float cr_gridSize = 16.f;
  // states styff
  StateData cr_Statedata;
  std::stack<State *> cr_State;

  // initilization functions
  // 1. init all directories
  void initDirectories();
  // 2. init all root variables
  void initVariabless();
  // 3. init localisations
  void initLocations();
  // 4. init window
  void initWindow();
  // 5. init textures
  void initTextures();
  // 6. init key data
  void initKeyBinds();
  // 7. init state data
  void initStateData();
  // 8. init first state
  void initState();

public:
  Core();
  virtual ~Core();
  void run();

  void updateEventsWindow();
  void updateDeltaTime();
  void updateSound();
  void update();
  void render();
};

#endif /* CORE */
