#ifndef CORE
#define CORE

#include "../states/State.hpp"
#include "dataCollector/_man_Volume.hpp"
#include "dataCollector/_man_graphics.hpp"
#include "header.h"

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
  std::shared_ptr<gfx::VolumeCollector> cr_VolumeCollector;
  std::shared_ptr<std::map<std::string, sf::Sound>> cr_SoundMap;
  std::shared_ptr<std::map<std::string, sf::Sound>> cr_SoundBufferMap;
  // fonts
  sf::Font cr_GameFont_basic; // Font used in the game
  sf::Font cr_debugFont;      // Font used for debugging
  // graphics settings
  std::shared_ptr<gfx::myGFXStruct> cr_gfxSettings;
  // just const float (no, actually very important item)))
  const float cr_gridSize = 16.f;
  // states styff
  StateData cr_Statedata;
  std::stack<State *> cr_State;

  nlohmann::json cr_databuffer;
  bool is_data_loaded = false;
  bool is_data_corrupted = false;

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

  // 6. init state data
  void initStateData();
  // 7. init first state
  void initState();

protected:
  // core functions
  bool cr_LoadData(nlohmann::json &_json_object, gfx::myGFXStruct &_gfx_object,
                   std::map<std::string, uint32_t> &_keys_object,
                   gfx::VolumeCollector &_vol_object);
  bool cr_LoadData2(nlohmann::json &_json_object, gfx::myGFXStruct &_gfx_object,
                    std::map<std::string, uint32_t> &_keys_object,
                    gfx::VolumeCollector &_vol_object);
  bool cr_SaveData(gfx::myGFXStruct &_gfx_object,
                   std::map<std::string, uint32_t> &_keys_object,
                   gfx::VolumeCollector &_vol_object);

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
