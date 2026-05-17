#ifndef CORE
#define CORE

#include "header.h"
#include "_myConst.h"

#include "dataCollector/_keybind_enum.h"
#include "dataCollector/_man_Volume.hpp"
#include "dataCollector/_man_graphics.hpp"
#include "dataCollector/_man_Texture.hpp"
#include "../localisation/helperText.hpp"

#include "../states/State.hpp"
#include "../states/MainMenu.hpp"

#include "systemFunctionUNIX.hpp"
#include "tools/LOGGER.hpp"
#include "tools/staticFPSMetter.hpp"

// class LuaVM{
//     public:
//     lua_State* L;

//     LuaVM() {
//         L = luaL_newstate();
//         luaL_openlibs(L);
//     };
//     ~LuaVM(){ if (L) { lua_close(L); }}

//     operator lua_State*() const { return L; }

//     lua_State* operator->() const { return L;}
// };
///
/// @brief The "Core" class is responsible for managing the main game loop, handling events, updating game state, and rendering. It also manages resources such as textures, sounds, and fonts, and handles the loading and saving of game data. The Core class serves as the central hub for the game's functionality, coordinating various subsystems and ensuring smooth gameplay.
///
class Core {
private:
  // window <3
  std::shared_ptr<sf::RenderWindow> cr_Window;

  // Clock and time
  float cr_deltaTime;
  sf::Clock cr_deltaClock;

  // Data (keyboard, Graph)
  // std::shared_ptr<keyboardOSX> cr_Keyboard;
  std::shared_ptr<std::map<std::string, uint16_t>> cr_KeySuppors;

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

  // json data buffer
  nlohmann::json jsonBuffer;

  bool is_data_loaded = false;
  bool is_data_corrupted = false;
  // lua state
  // LuaVM luaVM;

  // initilization functions
  void coreInitDirectories();
  void coreInitVariabless();
  void coreInitLocations();
  void coreInitKeyboard();
  void coreInitTextures();
  void coreInitWindow();
  void coreInitLua();
  void coreInitKeyBind();

  void coreInitStateData();
  void coreInitState();

protected:
  // core functions
  bool cr_LoadData();
  bool cr_SaveData();

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
