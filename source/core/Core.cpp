#include "Core.h"
#include "../localisation/helperText.hpp"
#include "../states/MainMenu.hpp"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "systemFunctionUNIX.hpp"
#include "tools/LOGGER.hpp"
#include "tools/PARSJSON.hpp"
#include "tools/staticFPSMetter.hpp"
#include <IOKit/hid/IOHIDUsageTables.h>

// check if app directory exists
void Core::initDirectories() {
  if (ApplicationsFunctions::checkAppDirectoryExists()) {
    Logger::logStatic("App directory already exists",
                      "l:13 -> Core::initDirectories()");
  }
}

// initialisations root data and build first frame app
void Core::initVariabless() {
  cr_Window = NULL; // null window
  cr_deltaTime = 0.0f;
  cr_deltaClock.restart();

  cr_GameFont_basic.openFromFile(
      std::string(ApplicationsFunctions::get_resources_dir() +
                  myConst::fonts::data_gameproces_font_path));
  cr_debugFont.openFromFile(
      std::string(ApplicationsFunctions::get_resources_dir() +
                  myConst::fonts::data_debugfont_path));

  // init keysupports and binds

#if __MDEBUG__ == 1
  // logger moment
  Logger::logStatic("Window, dt<->dc inited by def", "Core::initVariabless()");
#endif
  // load graphics settings from file
  // if not loaded, save default settings
  if (!this->cr_gfxSettings->loadFromFile())
    this->cr_gfxSettings->saveToFile();
}

void Core::initStateData() {
  // send window state stack and fonts to state data
  cr_Statedata.sd_Window = cr_Window;
  cr_Statedata.sd_States = &cr_State;
  cr_Statedata.sd_GameFont_basic = cr_GameFont_basic;
  cr_Statedata.sd_debugFont = cr_debugFont;
  // keyboard and theyr stuff
  cr_Statedata.sd_keyboard_prt = cr_Keyboard;
  cr_Statedata.sd_KeySupports = cr_KeySuppors;
  cr_Statedata.sd_KeyBinds = cr_KeyBinds;
  // graphics settings
  cr_Statedata.sd_gfxSettings = cr_gfxSettings;
  // character sizes and grid size
  cr_Statedata.sd_gridSize = cr_gridSize;
  cr_Statedata.sd_characterSize_debug =
      mmath::calcCharSize(cr_Window->getSize(), 150);
  cr_Statedata.sd_characterSize_game_big =
      mmath::calcCharSize(cr_Window->getSize(), 60);
  cr_Statedata.sd_characterSize_game_medium =
      mmath::calcCharSize(cr_Window->getSize(), 85);
  cr_Statedata.sd_characterSize_game_small =
      mmath::calcCharSize(cr_Window->getSize(), 100);
  // boolean for gui (make for extra reset)
  cr_Statedata.sd_reserGUI = false;

#if __MDEBUG__ == 1
  // logger moment

  // check if window is not null
  if (!cr_Statedata.sd_Window.lock())
    Logger::logStatic("ERROR::WINDOW::NOT INITED", "Core::initStateData()",
                      logType::ERROR);

  // check if states is not empty or null idk
  if (!cr_Statedata.sd_States->empty())
    Logger::logStatic("ERROR::STATES::NOT INITED", "Core::initStateData()",
                      logType::ERROR);

#endif
}

void Core::initKeyBinds() { // init default keys
  cr_KeySuppors = std::make_shared<std::map<std::string, uint32_t>>();
  ParserJson::loadKeyBinds(*cr_KeySuppors);
  cr_Keyboard = std::make_shared<keyboardOSX>();
  cr_KeyBinds = std::make_shared<std::map<std::string, uint32_t>>();
  // VolumeCollector, sound and other
  cr_VolumeCollector = std::make_shared<VolumeCollector>();
}

void Core::initState() {
  this->cr_State.push(new MainMenu(&cr_Statedata));

#if __MDEBUG__ == 1
  // logger moment with states
  Logger::logStatic("State inited", "Core::initState()");
  Logger::logStatic("State size: " + std::to_string(cr_State.size()),
                    "Core::initState()");
#endif
}

void Core::initLocations() {
  helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);
}

void Core::initWindow() {
  cr_Window = std::make_shared<sf::RenderWindow>(
      sf::RenderWindow(cr_gfxSettings->_struct.resolution,
                       cr_gfxSettings->_struct.title, sf::State::Windowed));

  if (cr_gfxSettings->_struct.fullscreen && cr_Window->isOpen()) {

    cr_gfxSettings->_struct._winResolutions = cr_Window->getSize();
    cr_Window->create(
        sf::VideoMode({cr_gfxSettings->_struct._winResolutions.x,
                       cr_gfxSettings->_struct._winResolutions.y}),
        cr_gfxSettings->_struct.title, sf::State::Fullscreen,
        cr_gfxSettings->_struct.contextSettings);
  }

  cr_Window->setFramerateLimit(cr_gfxSettings->_struct.frameRateLimit);
  cr_Window->setVerticalSyncEnabled(cr_gfxSettings->_struct.verticalSync);
  cr_Window->setKeyRepeatEnabled(false);
}
void Core::initTextures() {
  // null текстура
  TextureManager::loadTexture(TextureID::TEXTURE_NULL,
                              myConst::textures::texture_NULL);
  // текстуры для карты
  TextureManager::loadTexture(TextureID::TEXTURE_DEEP_OCEAN,
                              myConst::textures::texture_DEEP_OCEAN);
  TextureManager::loadTexture(TextureID::TEXTURE_OCEAN,
                              myConst::textures::texture_OCEAN);
  TextureManager::loadTexture(TextureID::TEXTURE_SAND,
                              myConst::textures::texture_SAND);
  TextureManager::loadTexture(TextureID::TEXTURE_GRASS,
                              myConst::textures::texture_GRASS);
  TextureManager::loadTexture(TextureID::TEXTURE_DIRT,
                              myConst::textures::texture_DIRT);
  TextureManager::loadTexture(TextureID::TEXTURE_STONE,
                              myConst::textures::texture_STONE);
  TextureManager::loadTexture(TextureID::TEXTURE_SNOW,
                              myConst::textures::texture_SNOW);

  // загружаем текстуры сущностей
  TextureManager::loadTexture(TextureID::TEXTURE_PLAYER,
                              myConst::sprites::texture_PLAYER);
  TextureManager::loadTexture(TextureID::TEXTURE_SLIME,
                              myConst::sprites::texture_SLIME);

  // бек в главном меню
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_1,
                              myConst::gui::texture_background_mainmenu_lay_1);
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_2,
                              myConst::gui::texture_background_mainmenu_lay_2);
  TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_3,
                              myConst::gui::texture_background_mainmenu_lay_3);

  // текстуры итемов и тп
  // Загружаем текстуру для ячеек и предметов
  TextureManager::loadTexture(TextureID::ITEMS_NULL, ItemTextures::item_NULL);
  TextureManager::loadTexture(TextureID::INVENTORY_CELL_TEXTURE,
                              ItemTextures::inv_cell_back);
  TextureManager::loadTexture(
      TextureID::ITEMS_POISON_SMALL_REGENERATION,
      ItemTextures::poison::item_img_poison_small_regeneration);
  TextureManager::loadTexture(TextureID::ITEMS_STONE,
                              ItemTextures::items::item_img_stone);

  // Дополнительные текстуры для новых предметов
  // Эти текстуры должны быть добавлены в resources, пока используем
  // существующие
  TextureManager::loadTexture(
      TextureID::ITEMS_WOOD,
      ItemTextures::items::item_img_stone2); // Временно используем текстуру
                                             // камня
  TextureManager::loadTexture(
      TextureID::ITEMS_IRON_SWORD,
      ItemTextures::items::item_img_claster_crystal); // Временно используем
                                                      // текстуру кристалла
  TextureManager::loadTexture(
      TextureID::ITEMS_BREAD,
      ItemTextures::item_NULL); // Временно используем пустую текстуру
  TextureManager::loadTexture(
      TextureID::ITEMS_LEATHER_ARMOR,
      ItemTextures::item_NULL); // Временно используем пустую текстуру
  TextureManager::loadTexture(
      TextureID::ITEMS_HEALTH_POTION,
      ItemTextures::poison::item_img_poison_small_regeneration); // Временно
                                                                 // используем
                                                                 // текстуру
                                                                 // яда

  // текстуры для монет
  TextureManager::loadTexture(TextureID::COINS_GOLD_NUGGET,
                              ItemTextures::coins::item_img_gold_nugget);
  TextureManager::loadTexture(TextureID::COINS_COPPER_NUGGET,
                              ItemTextures::coins::item_img_copper_nuggen);
  TextureManager::loadTexture(TextureID::COINS_SILVER_NUGGET,
                              ItemTextures::coins::item_img_silver_nuggen);
  TextureManager::loadTexture(
      TextureID::ITEMS_GOLD_COIN,
      ItemTextures::coins::item_img_gold_nugget); // Используем текстуру
                                                  // золотой монеты
}

Core::Core() {
  this->initDirectories();
  this->initVariabless();
  this->initLocations();
  this->initWindow();
  this->initTextures();
  this->initKeyBinds();
  this->initStateData();
  this->initState();

  FPS::reset();

#if __MDEBUG__ == 1
  Logger::logStatic("Core Inited", "Core::Core()");
#endif
}

Core::~Core() {
  this->cr_gfxSettings->saveToFile();

  while (!cr_State.empty()) {
    delete cr_State.top();
    cr_State.pop();
  }
  cr_Window.get()->close();
  cr_Window.reset();

#if __MDEBUG__ == 1
  // logger moment
  Logger::logStatic("Core Delete...", "Core::~Core()");

  if (cr_State.empty())
    Logger::logStatic("State is empty", "Core::~Core()");
  else
    Logger::logStatic("State is not empty... mem leaked", "Core::~Core()",
                      logType::ERROR);

  if (cr_Window == NULL)
    Logger::logStatic("Window is null", "Core::~Core()");
  else
    Logger::logStatic("Window is null... mem leaked", "Core::~Core()",
                      logType::ERROR);

  Logger::logStatic("Core Deleted", "Core::~Core()");
#endif
}

void Core::run() {
  Logger::logStatic("Start main loop", "Core::run()");

  while (cr_Window->isOpen()) {
    this->updateDeltaTime();
    this->update();
    this->updateSound();
    this->render();
  }
}

void Core::update() {
  // state update
  this->updateEventsWindow();

  if (!cr_State.empty()) {
    if (cr_Window->hasFocus()) {

      cr_Keyboard.get()->update();
      cr_State.top()->update(cr_deltaTime);

      if (cr_State.top()->getQuit()) {
        delete cr_State.top();
        cr_State.pop();
      }
    }
  }
  // Application end
  else {
    cr_Window->close();
  }
}

void Core::updateEventsWindow() {
  while (const std::optional event = cr_Window.get()->pollEvent())
    if (event->is<sf::Event::Closed>())
      cr_Window->close();
}

void Core::render() {
  cr_Window->clear();

  if (!cr_State.empty())
    cr_State.top()->render(*cr_Window.get());

  cr_Window->display();
}

void Core::updateSound() {
  if (!cr_State.empty())
    cr_State.top()->updateSounds(cr_deltaTime);
}

void Core::updateDeltaTime() {
  cr_deltaTime = 0;
  cr_deltaTime = cr_deltaClock.restart().asSeconds();
  FPS::update();
}