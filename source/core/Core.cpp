#include "Core.h"

// инициализация реестра предметов

unsigned int FPS::mFrame = 0;
unsigned int FPS::mFps = 0;
sf::Clock FPS::mClock = sf::Clock();
std::unordered_map<std::string, sf::Texture> TextureManager::m_textures;
std::unordered_map<TextureID, std::string> TextureIDMapping::idToStringMap;
std::filesystem::path AppFn::pResources;
std::filesystem::path AppFn::pDocuments;

// check if app directory exists
void Core::coreInitDirectories() {
	if (AppFn::checkAppDirectoryesExists())
		Logger::logStatic("App directory already exists", "Core::coreInitDirectories()");
	else
		AppFn::createAppDirectories();
}

// coreInitialisations root data, window, fonts and etc
void Core::coreInitVariabless() {
	// coreInit basics shared structs
	// cr_Keyboard = std::make_shared<keyboardOSX>();
	cr_gfxSettings = std::make_shared<gfx::myGFXStruct>();
	cr_VolumeCollector = std::make_shared<gfx::VolumeCollector>();
	cr_KeySuppors = std::make_shared<std::map<std::string, uint16_t>>();

	if (!cr_LoadData()) {
		Logger::logStatic("Failed to load data!", "Core::coreInitVariables()");
	}

	// set supported keys
	// emplace supporded key into map

	// before load data from json file
	//   cr_LoadData2(cr_databuffer, *cr_gfxSettings, *cr_KeyBinds,
	//                *cr_VolumeCollector);
	auto result = cr_LoadData();
	if (!result)
		Logger::logStatic("Failed to load keybinds!", "Core::coreInitVariables()");

	// set zero in dt and restart clock
	cr_deltaTime = 0.0f;
	cr_deltaClock.restart();

	// coreInit fonts
	FontManager::initialise();
	FontManager::loadFont(FontID::FONT_GAMEF_01, AppFn::getPathResourcesDir().append(myConst::fonts::data_gameproces_font_path));
	FontManager::loadFont(FontID::FONT_DEBUG, AppFn::getPathResourcesDir().append(myConst::fonts::data_debugfont_path));

#if __MDEBUG__ == ENABLE
	// print to console/Loggger all data for next debug
	std::stringstream ss;
	ss << "DEBUG LOG\ncurrent resouses used:\n"
		//<< "KeyboardOSX:" << (cr_Keyboard.get() ? "\t allive" : "\t is null")
		<< "GFX_DATA:\t" << (cr_gfxSettings.get() ? "\t allive" : "\t is null")
		<< "Volume_Data:\t"
		<< (cr_VolumeCollector.get() ? "\t allive" : "\t is null")
		<< "KeyboadSupports_data:\t"
		<< (cr_KeySuppors.get() ? "\t allive" : "\t is null");
	for (const auto& [key, value] : *cr_KeySuppors.get())
		ss << "Key: " << key << ", Value: " << value << std::endl;
	for (const auto& [key, value] : *cr_KeySuppors.get())
		ss << "Key: " << key << ", Value: " << value << std::endl;
#endif
}

void Core::coreInitLocations() {
	helperText::ApplicationLangue::setLanguage(helperText::Language::ENG);
}

void Core::coreInitWindow() {
	cr_Window = std::make_shared<sf::RenderWindow>(sf::RenderWindow(sf::VideoMode::getFullscreenModes()[2], cr_gfxSettings->title, sf::State::Windowed));
#ifdef _DEBUG
	std::stringstream s;
	auto& vs = sf::VideoMode::getFullscreenModes();
	for (auto& t : vs)
		s << "\nvm:\t" << t.size.x << " x " << t.size.y;

	Logger::logStatic(s.str(), "CORE");
#endif
	if (cr_gfxSettings->fullscreen && cr_Window->isOpen()) { // init as fullscrean mode with fullwidth reso
		cr_Window->create(sf::VideoMode({cr_gfxSettings->_winResolutions.x, cr_gfxSettings->_winResolutions.y}),
						  cr_gfxSettings->title, sf::State::Fullscreen, cr_gfxSettings->contextSettings);
	}
	cr_gfxSettings->updateResolution(cr_Window->getSize());
	cr_Window->setFramerateLimit(cr_gfxSettings->frameRateLimit);
	cr_Window->setVerticalSyncEnabled(cr_gfxSettings->verticalSync);
	cr_Window->setKeyRepeatEnabled(false);
	cr_Window->setPosition({0,0});

	///  keyboardCocoa::setupCocoaKeyboard(cr_Window->getNativeHandle());
}

// load all textures
void Core::coreInitTextures() {

	TextureManager::initialize();
	TextureManager::loadTexture(TextureID::TEXTURE_DEEP_OCEAN, myConst::textures::texture_DEEP_OCEAN);
	TextureManager::loadTexture(TextureID::TEXTURE_OCEAN, myConst::textures::texture_OCEAN);
	TextureManager::loadTexture(TextureID::TEXTURE_SAND, myConst::textures::texture_SAND);
	TextureManager::loadTexture(TextureID::TEXTURE_GRASS, myConst::textures::texture_GRASS);
	TextureManager::loadTexture(TextureID::TEXTURE_DIRT, myConst::textures::texture_DIRT);
	TextureManager::loadTexture(TextureID::TEXTURE_STONE, myConst::textures::texture_STONE);
	TextureManager::loadTexture(TextureID::TEXTURE_SNOW, myConst::textures::texture_SNOW);
	TextureManager::loadTexture(TextureID::TEXTURE_PLAYER, myConst::sprites::texture_PLAYER);
	TextureManager::loadTexture(TextureID::TEXTURE_SLIME, myConst::sprites::texture_SLIME);
	TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_1, myConst::gui::texture_background_mainmenu_lay_1);
	TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_2, myConst::gui::texture_background_mainmenu_lay_2);
	TextureManager::loadTexture(TextureID::TEXTURE_BACKGROUND_LAY_3, myConst::gui::texture_background_mainmenu_lay_3);
	//TextureManager::loadTexture(TextureID::INVENTORY_CELL_TEXTURE, ItemTextures::inv_cell_back);
	//TextureManager::loadTexture(TextureID::ITEMS_POISON_SMALL_REGENERATION, ItemTextures::poison::item_img_poison_small_regeneration);
	//TextureManager::loadTexture(TextureID::ITEMS_STONE, ItemTextures::items::item_stone);
	//TextureManager::loadTexture(TextureID::ITEMS_WOOD, ItemTextures::items::item_stone2);                                  // Временно используем текстуру камня
	//TextureManager::loadTexture(TextureID::ITEMS_IRON_SWORD, ItemTextures::items::item_claster_crystal);                   // Временно используем текстуру кристалла
	//TextureManager::loadTexture(TextureID::ITEMS_BREAD, ItemTextures::items::item_bread);                                  // Временно используем пустую текстуру
	//TextureManager::loadTexture(TextureID::ITEMS_LEATHER_ARMOR, ItemTextures::item_NULL);                                  // Временно используем пустую текстуру
	//TextureManager::loadTexture(TextureID::ITEMS_HEALTH_POTION, ItemTextures::poison::item_img_poison_small_regeneration); // Временно используем текстуру яда
	//TextureManager::loadTexture(TextureID::ITEMS_GOLD_COIN, ItemTextures::coins::item_img_gold_nugget);
	//TextureManager::loadTexture(TextureID::COINS_GOLD_NUGGET, ItemTextures::coins::item_img_gold_nugget);
	//TextureManager::loadTexture(TextureID::COINS_COPPER_NUGGET, ItemTextures::coins::item_img_copper_nuggen);
	//TextureManager::loadTexture(TextureID::COINS_SILVER_NUGGET, ItemTextures::coins::item_img_silver_nuggen);
}

void Core::coreInitStateData() { // send window state stack and fonts to state data
	cr_Statedata.sd_Window = cr_Window;
	cr_Statedata.sd_States = &cr_State;
	// keyboard and theyr stuff
	// cr_Statedata.sd_keyboard_prt = cr_Keyboard;
	cr_Statedata.sd_KeySupports = cr_KeySuppors;
	// graphics settings
	cr_Statedata.sd_gfxSettings = cr_gfxSettings;
	// volume collector
	cr_Statedata.sd_VolumeCollector = cr_VolumeCollector;
	// character sizes and grid size
	cr_Statedata.sd_gridSize = cr_gridSize;
	auto ws = cr_Window->getSize();
	cr_Statedata.sd_characterSize_debug = mmath::calcCharSize(ws.x, ws.y, 200U);
	cr_Statedata.sd_characterSize_game_big = mmath::calcCharSize(ws.x, ws.y, 60U);
	cr_Statedata.sd_characterSize_game_medium = mmath::calcCharSize(ws.x, ws.y, 85U);
	cr_Statedata.sd_characterSize_game_small = mmath::calcCharSize(ws.x, ws.y, 100U);
	// boolean for gui (make for extra reset)
	cr_Statedata.sd_reserGUI = false;

#if __MDEBUG__ == 1
	// logger moment

	// check if window is not null
	if (!cr_Statedata.sd_Window.lock())
		Logger::logStatic("LERROR::WINDOW::NOT INITED", "Core::coreInitStateData()");

	// check if states is not empty or null idk
	if (!cr_Statedata.sd_States->empty())
		Logger::logStatic("LERROR::STATES::NOT INITED", "Core::coreInitStateData()");
#endif
}

void Core::coreInitState() {
	cr_State.push(new MainMenu(&cr_Statedata));

#if __MDEBUG__ == 1
	// logger moment with states
	Logger::logStatic("State coreInited", "Core::coreInitState()");
	Logger::logStatic("State size: " + std::to_string(cr_State.size()),
					  "Core::coreInitState()");
#endif
}

void Core::coreInitLua() {
	// Инициализация Srcipts Lua VM
	// luaL_dofile(luaVM,myConst::scripts::lua_test);
}

void Core::coreInitKeyBind() {
#ifdef __APPLE__
	// pull all keys
	cr_KeySuppors->emplace(ActionKeyBind::KEY_A, kVK_ANSI_A);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_C, kVK_ANSI_C);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_D, kVK_ANSI_D);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_E, kVK_ANSI_E);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F, kVK_ANSI_F);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_Q, kVK_ANSI_Q);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_R, kVK_ANSI_R);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_S, kVK_ANSI_S);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_W, kVK_ANSI_W);
	// cr_KeySuppors->emplace("X", kHIDUsage_KeyboardX);
	// cr_KeySuppors->emplace("Z", kHIDUsage_KeyboardZ);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_1, kVK_ANSI_1);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_2, kVK_ANSI_2);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_3, kVK_ANSI_3);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_4, kVK_ANSI_4);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_5, kVK_ANSI_5);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_6, kVK_ANSI_6);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_7, kVK_ANSI_7);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_8, kVK_ANSI_8);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_9, kVK_ANSI_9);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_NUM_0, kVK_ANSI_0);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_SPACE, kVK_Space);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_APPLY, kVK_Return);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_CLOSE, kVK_Escape);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_REMOVE, kVK_Delete);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_DEBUG_SWITCH, kVK_ANSI_Slash);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_TAB_MENU, kVK_Tab);
	cr_KeySuppors->emplace(ActionKeyBind::ACTION_INVENTORY, kVK_Tab);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F1, kVK_F1);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F2, kVK_F2);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F3, kVK_F3);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F4, kVK_F4);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F5, kVK_F5);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F6, kVK_F6);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F7, kVK_F7);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F8, kVK_F8);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F9, kVK_F9);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F10, kVK_F10);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F11, kVK_F11);
	cr_KeySuppors->emplace(ActionKeyBind::KEY_F12, kVK_F12);
#endif
}

void Core::coreInitKeyboard() {}

Core::Core() {
	coreInitDirectories();
	coreInitVariabless();
	coreInitLocations();
	coreInitKeyboard();
	coreInitTextures();
	coreInitWindow();
	coreInitLua();
	coreInitKeyBind();

	coreInitStateData();
	coreInitState();

	FPS::reset();

#if __MDEBUG__ == 1
	Logger::logStatic("Core Inited", "Core::Core()");
#endif
}

Core::~Core() {
	cr_SaveData();

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
		Logger::logStatic("State is not empty... mem leaked", "Core::~Core()");

	if (cr_Window == NULL)
		Logger::logStatic("Window is null", "Core::~Core()");
	else
		Logger::logStatic("Window is null... mem leaked", "Core::~Core()");

	Logger::logStatic("Core Deleted", "Core::~Core()");
#endif
}

void Core::run() {
	Logger::logStatic("Start main loop", "Core::run()");

	while (cr_Window->isOpen()) {
		updateDeltaTime();
		update();
		updateSound();
		render();
	}
}

void Core::update() {
	// state update
	updateEventsWindow();

	if (!cr_State.empty()) {
		if (cr_Window->hasFocus()) {
			cr_State.top()->update(cr_deltaTime);

			if (cr_State.top()->getQuit()) {
				delete  cr_State.top();
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
	while (const std::optional event = cr_Window.get()->pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			cr_Window->close();
		}
		if (event->is < sf::Event::Resized>()) {
			if (!cr_State.empty()) cr_State.top()->wasUpdateWindon();
		}
	}
}

void Core::render() {
	cr_Window->clear();
	if (!cr_State.empty()) cr_State.top()->render(*cr_Window.get());
	cr_Window->display();
}

void Core::updateSound() {
	if (!cr_State.empty()) cr_State.top()->updateSounds(cr_deltaTime);
}

void Core::updateDeltaTime() {
	cr_deltaTime = 0;
	cr_deltaTime = cr_deltaClock.restart().asSeconds();
	FPS::update();
}