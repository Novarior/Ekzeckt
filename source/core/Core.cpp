#include "Core.h"

#include "../localisation/helperText.hpp"
#include "../states/MainMenu.hpp"
#include "_myConst.h"
#include "dataCollector/_man_Texture.hpp"
#include "systemFunctionUNIX.hpp"
#include "tools/LOGGER.hpp"
#include "tools/staticFPSMetter.hpp"
#include <cstddef>
#include <strstream>

// инициализация реестра предметов
std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};
// Инициализация статичного счетчика сущностей
unsigned int Entity::count_entitys = 0;
// Инициализация статичного счетчика для смены текстуры
unsigned BrickBlock::currentFrame = 0;
// Инициализация статичного счетчика кадра
unsigned int FPS::mFrame = 0;
// Инициализация статичного счетчика кадров
unsigned int FPS::mFps = 0;
// инициализаия часов для подсчета фпс
sf::Clock FPS::mClock = sf::Clock();
// Инициализация статического контейнера
std::unordered_map<std::string, sf::Texture> TextureManager::m_textures;
// Инициализация словаря для маппинга TextureID к строкам
std::unordered_map<TextureID, std::string> TextureIDMapping::idToStringMap;

// check if app directory exists
void Core::initDirectories() {
  if (ApplicationsFunctions::checkAppDirectoryExists()) {
    Logger::logStatic("App directory already exists",
                      "Core::initDirectories()");
  } else {
    ApplicationsFunctions::createAppDirectories();
  }
}

// initialisations root data, window, fonts and etc
void Core::initVariabless() {
  // make path to config file, and create json object with fstream object

  // fstream obj
  std::ifstream ifs(ApplicationsFunctions::getAppConfigFolder() +
                    AppFiles::config_window);
  if (!ifs.is_open()) {
    Logger::logStatic("CANNOT OPEN FILE", "Core::initVariables()",
                      logType::ERROR);
  } else {
    try {
      ifs >> cr_databuffer;
      is_data_loaded = true;
      Logger::logStatic("Config file loaded successfully",
                        "Core::initVariables()");
    } catch (json::parse_error &e) {
      Logger::logStatic("JSON::PARSE_ERROR: " + std::string(e.what()),
                        "Core::initVariables()", logType::ERROR);
      is_data_corrupted = true;
    }
    ifs.close();
  }

  // init basics shared structs
  cr_Keyboard = std::make_shared<keyboardOSX>();
  cr_gfxSettings = std::make_shared<gfx::myGFXStruct>();
  cr_VolumeCollector = std::make_shared<gfx::VolumeCollector>();
  cr_KeyBinds = std::make_shared<std::map<std::string, uint32_t>>();
  cr_KeySuppors = std::make_shared<std::map<std::string, uint32_t>>();

  // set supported keys
  // emplace supporded key into map
  cr_KeySuppors->emplace("A", kHIDUsage_KeyboardA);
  cr_KeySuppors->emplace("C", kHIDUsage_KeyboardC);
  cr_KeySuppors->emplace("D", kHIDUsage_KeyboardD);
  cr_KeySuppors->emplace("E", kHIDUsage_KeyboardE);
  cr_KeySuppors->emplace("F", kHIDUsage_KeyboardF);
  cr_KeySuppors->emplace("Q", kHIDUsage_KeyboardQ);
  cr_KeySuppors->emplace("R", kHIDUsage_KeyboardR);
  cr_KeySuppors->emplace("S", kHIDUsage_KeyboardS);
  cr_KeySuppors->emplace("W", kHIDUsage_KeyboardW);
  cr_KeySuppors->emplace("X", kHIDUsage_KeyboardX);
  cr_KeySuppors->emplace("Z", kHIDUsage_KeyboardZ);
  cr_KeySuppors->emplace("1", kHIDUsage_Keyboard1);
  cr_KeySuppors->emplace("2", kHIDUsage_Keyboard2);
  cr_KeySuppors->emplace("3", kHIDUsage_Keyboard3);
  cr_KeySuppors->emplace("4", kHIDUsage_Keyboard4);
  cr_KeySuppors->emplace("5", kHIDUsage_Keyboard5);
  cr_KeySuppors->emplace("6", kHIDUsage_Keyboard6);
  cr_KeySuppors->emplace("7", kHIDUsage_Keyboard7);
  cr_KeySuppors->emplace("8", kHIDUsage_Keyboard8);
  cr_KeySuppors->emplace("9", kHIDUsage_Keyboard9);
  cr_KeySuppors->emplace("0", kHIDUsage_Keyboard0);
  cr_KeySuppors->emplace("Escape", kHIDUsage_KeyboardEscape);
  cr_KeySuppors->emplace("Space", kHIDUsage_KeyboardSpacebar);
  cr_KeySuppors->emplace("Enter", kHIDUsage_KeyboardReturnOrEnter);
  cr_KeySuppors->emplace("BackSpace", kHIDUsage_KeyboardDeleteOrBackspace);
  cr_KeySuppors->emplace("Slash", kHIDUsage_KeyboardSlash);
  cr_KeySuppors->emplace("Tab", kHIDUsage_KeyboardTab);
  cr_KeySuppors->emplace("F1", kHIDUsage_KeyboardF1);
  cr_KeySuppors->emplace("F2", kHIDUsage_KeyboardF2);
  cr_KeySuppors->emplace("F3", kHIDUsage_KeyboardF3);

  // before load data from json file
  //   cr_LoadData2(cr_databuffer, *cr_gfxSettings, *cr_KeyBinds,
  //                *cr_VolumeCollector);
  auto result = cr_LoadData(cr_databuffer, *cr_gfxSettings, *cr_KeyBinds,
                            *cr_VolumeCollector);
  if (!result) {
    Logger::logStatic("Failed to load keybinds!", "Core::initVariables()",
                      logType::ERROR);
  }

  // set zero in dt and restart clock
  cr_deltaTime = 0.0f;
  cr_deltaClock.restart();

  // init fonts
  cr_GameFont_basic.openFromFile(
      std::string(ApplicationsFunctions::get_resources_dir() +
                  myConst::fonts::data_gameproces_font_path));
  cr_debugFont.openFromFile(
      std::string(ApplicationsFunctions::get_resources_dir() +
                  myConst::fonts::data_debugfont_path));

#if __MDEBUG__ == ENABLE
  // print to console/Loggger all data for next debug
  std::stringstream ss;
  ss << "DEBUG LOG\ncurrent resouses used:\n"
     << "KeyboardOSX:" << (cr_Keyboard.get() ? "\t allive" : "\t is null")
     << "GFX_DATA:\t" << (cr_gfxSettings.get() ? "\t allive" : "\t is null")
     << "Volume_Data:\t"
     << (cr_VolumeCollector.get() ? "\t allive" : "\t is null")
     << "KeyBinds_Data:\t" << (cr_KeyBinds.get() ? "\t allive" : "\t is null")
     << "KeyboadSupports_data:\t"
     << (cr_KeySuppors.get() ? "\t allive" : "\t is null");
  for (const auto [key, value] : *cr_KeySuppors.get())
    ss << "Key: " << key << ", Value: " << value << std::endl;
  for (const auto [key, value] : *cr_KeySuppors.get())
    ss << "Key: " << key << ", Value: " << value << std::endl;

#endif
}

void Core::initLocations() {
  helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);
}

void Core::initWindow() {
  cr_Window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(
      cr_gfxSettings->resolution, cr_gfxSettings->title, sf::State::Windowed));

  if (cr_gfxSettings->fullscreen && cr_Window->isOpen()) {

    cr_gfxSettings->_winResolutions = cr_Window->getSize();
    cr_Window->create(sf::VideoMode({cr_gfxSettings->_winResolutions.x,
                                     cr_gfxSettings->_winResolutions.y}),
                      cr_gfxSettings->title, sf::State::Fullscreen,
                      cr_gfxSettings->contextSettings);
  }

  cr_Window->setFramerateLimit(cr_gfxSettings->frameRateLimit);
  cr_Window->setVerticalSyncEnabled(cr_gfxSettings->verticalSync);
  cr_Window->setKeyRepeatEnabled(false);
}

// load all textures
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
  // volume collector
  cr_Statedata.sd_VolumeCollector = cr_VolumeCollector;
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

void Core::initState() {
  this->cr_State.push(new MainMenu(&cr_Statedata));

#if __MDEBUG__ == 1
  // logger moment with states
  Logger::logStatic("State inited", "Core::initState()");
  Logger::logStatic("State size: " + std::to_string(cr_State.size()),
                    "Core::initState()");
#endif
}

Core::Core() {
  this->initDirectories();
  this->initVariabless();
  this->initLocations();
  this->initWindow();
  this->initTextures();
  this->initStateData();
  this->initState();

  FPS::reset();

#if __MDEBUG__ == 1
  Logger::logStatic("Core Inited", "Core::Core()");
#endif
}

Core::~Core() {
  cr_SaveData(*cr_gfxSettings, *cr_KeyBinds, *cr_VolumeCollector);

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