#include "settings.hpp"


void SettingsState::initVariables() { // init variables
  // init video modes like all supported modes
	_video_modes = sf::VideoMode::getFullscreenModes();
	// init framerates list
	_gfxResource["GFX_FPS"] = std::vector<int>{30, 60, 90, 120};
	_gfxResource["GFX_ALL"] = std::vector<int>{0, 2, 4, 8, 16};
	_gfxResource["GFX_VSYNC"] = std::vector<int>{0, 1};
	_gfxResource["GFX_FULLSCREEN"] = std::vector<int>{0, 1};
}

void SettingsState::initFonts() { // init sd_font
	 font =  IstateData->sd_GameFont_basic;
}

void SettingsState::initGui() { // init gui with next call functions

	sf::Vector2u window_size =  Iwindow.lock()->getSize();
	sf::Vector2f wsf = {(float)(window_size.x), (float)(window_size.y)};

	// init background
	 background.setSize(wsf);
	// darkest blue color
	 background.setFillColor(sf::Color(20, 25, 40, 200));

	// init page background, size of page background
	_pageBackground.setSize({mmath::p2pX(70.f, wsf.x), mmath::p2pX(66.f, wsf.y)});

		// position of page background
	_pageBackground.setPosition({mmath::p2pX(50.f, wsf.x) - _pageBackground.getSize().x / 2.f,
								mmath::p2pX(50.f, wsf.y) - _pageBackground.getSize().y / 2.f});
	_pageBackground.setFillColor(sf::Color(110, 130, 140, 200));

	sf::Vector2f button_size = {mmath::p2pX(16.f, wsf.x),mmath::p2pX(5.f, wsf.y)};

	 initButtons();
	 initGraphicsPage();
	 initSounsPage();
	 initGameplayPage();
	 initKeyboardPage();
	 initEctPage();
}

void SettingsState::initButtons() { // Navigaton buttons in settings
	sf::Vector2u window_size =  Iwindow.lock()->getSize();
	sf::Vector2f wsf = {(float)(window_size.x), (float)(window_size.y)};

	sf::Vector2f background_layer_pos = {
		mmath::p2pX(50.f, wsf.x) - _pageBackground.getSize().x / 2.f,
		mmath::p2pX(50.f, wsf.y) - _pageBackground.getSize().y / 2.f};

	sf::Vector2f button_size = {mmath::p2pX(10.f, wsf.x), mmath::p2pX(5.f, wsf.y)};
	// exit gui button
	_pageButtons["BACK_BTN"] = std::make_unique<gui::Button>(
		sf::Vector2f{wsf.x - 120.f, 0.f}, sf::Vector2f{120.f, 50.f},
		helperText::Button::BUTTON_BACK, gui::styles::buttons::btn_default,
		gui::type::BUTTON);
	// apply gui button
	// set "apply" button position litle bit left from "back" button
	_pageButtons["APPLY_BTN"] = std::make_unique<gui::Button>(
		sf::Vector2f(wsf.x - 240, 0.f), sf::Vector2f(120.f, 50.f),
		helperText::Button::BUTTON_APPLY, gui::styles::buttons::btn_default,
		gui::type::BUTTON);

	//============================================================================
	//==========================    PAGE BUTTONS    ==============================
	//============================================================================

	// init page buttons
	// five buttons for five pages in one row
	// have to be in the same order as settingPage enum

	_pageButtons["PGB_AUDIO"] = std::make_unique<gui::Button>(
		sf::Vector2f(background_layer_pos.x, background_layer_pos.y - button_size.y),
		button_size, helperText::SettingsTexts::TEXT_AUDIO,
		gui::styles::buttons::btn_default, gui::type::BUTTON);

	_pageButtons["PGB_GRAPHICS"] = std::make_unique<gui::Button>(
		sf::Vector2f(background_layer_pos.x + button_size.x, background_layer_pos.y - button_size.y),
		button_size, helperText::SettingsTexts::TEXT_GRAPHICS,
		gui::styles::buttons::btn_default, gui::type::BUTTON);

	_pageButtons["PGB_CONTROLS"] = std::make_unique<gui::Button>(
		sf::Vector2f(background_layer_pos.x + button_size.x * 2, background_layer_pos.y - button_size.y),
		button_size, helperText::SettingsTexts::TEXT_CONTROLS,
		gui::styles::buttons::btn_default, gui::type::BUTTON);

	_pageButtons["PGB_GAMEPLAY"] = std::make_unique<gui::Button>(
		sf::Vector2f(background_layer_pos.x + button_size.x * 3, background_layer_pos.y - button_size.y),
		button_size, helperText::SettingsTexts::TEXT_GAMEPLAY,
		gui::styles::buttons::btn_default, gui::type::BUTTON);
}

void SettingsState::initGraphicsPage() {
  //=======================================   GRAPHICS
  //===============================================
	sf::Vector2u window_size =  Iwindow.lock()->getSize();
	sf::Vector2f wsf = {(float)(window_size.x), (float)(window_size.y)};
	sf::Vector2f background_layer_pos = {mmath::p2pX(50.f, wsf.x) - _pageBackground.getSize().x / 2.f,	mmath::p2pX(50.f, wsf.y) - _pageBackground.getSize().y / 2.f};
	sf::Vector2f background_layer_size = {mmath::p2pX(70.f, wsf.x), mmath::p2pX(66.f, wsf.y)};
	sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(20.f, background_layer_size.x), mmath::p2pX(5.f, background_layer_size.y));

	// init shapes for textbox
	std::vector<std::string> settingsNames = {
		helperText::SettingsTexts::TEXT_RESOLUTION,
		helperText::SettingsTexts::TEXT_FULLSCREEN,
		helperText::SettingsTexts::TEXT_VSYNC,
		helperText::SettingsTexts::TEXT_ANTIALIASING,
		helperText::SettingsTexts::TEXT_FRAMERATE_LIMIT};

	for (int i = 0; i < 5; i++) {
		sf::RectangleShape shape;
		shape.setFillColor(sf::Color::Transparent);
		shape.setOutlineColor(sf::Color::Transparent);
		shape.setOutlineThickness(-1);
		shape.setPosition(sf::Vector2f(
			background_layer_pos.x + mmath::p2pX(5.f, background_layer_size.x),
			background_layer_pos.y + mmath::p2pX(5.f, background_layer_size.y) +
			i * mmath::p2pX(10.f, background_layer_size.y)));
		shape.setSize(sf::Vector2f(mmath::p2pX(20.f, background_layer_size.x), mmath::p2pX(5.f, background_layer_size.y)));
		sf::Text text( font, settingsNames[i],  IstateData->sd_characterSize_game_medium);

		text.setPosition(sf::Vector2f(shape.getPosition().x, shape.getPosition().y + (shape.getGlobalBounds().position.y / 2) - (text.getGlobalBounds().position.y / 2)));

		_graphic_list.push_back(std::make_pair(text, shape));
	}

	//=====================================   RESOLUTION
	//===============================================
	// init dropdown list with video modes
	std::vector<std::string> modes_str;
	int index = 0;
	for (auto& i : _video_modes) {
		modes_str.push_back(std::to_string(i.size.x) + " x " + std::to_string(i.size.y));
		if (i.size.x == IstateData->sd_gfxSettings.lock()->resolution.size.x && i.size.y == IstateData->sd_gfxSettings.lock()->resolution.size.y)
			index = modes_str.size() - 1;
	}

	// init selector with video modes
	_selectors["SELEC_VMODE"] = std::make_unique<gui::Selector>(
		sf::Vector2f(
		background_layer_pos.x + mmath::p2pX(55.f, background_layer_size.x),
		background_layer_pos.y + mmath::p2pX(5.f, background_layer_size.y)),
		button_size, font,  IstateData->sd_characterSize_game_medium,
		modes_str.data(), modes_str.size(), index);

	////===================================   FULLSCREEN
	////=================================================
	// init fullscreen list
	std::vector<std::string> fullscreen_list;
	fullscreen_list.push_back("Windowed");
	fullscreen_list.push_back("Fullscreen");

	// check current fullscreen and set it to selector like active element
	unsigned fs = 0;
	for (; fs < fullscreen_list.size(); fs++)
		if (fullscreen_list[fs] == (IstateData->sd_gfxSettings.lock()->fullscreen ? "Fullscreen" : "Windowed"))
			break;

		// init selector fullscreen
	_selectors["SELEC_FULLSCREEN"] = std::make_unique<gui::Selector>(
		sf::Vector2f(
		background_layer_pos.x + mmath::p2pX(55.f, background_layer_size.x),
		background_layer_pos.y + mmath::p2pX(15.f, background_layer_size.y)),
		button_size, font,  IstateData->sd_characterSize_game_medium,
		fullscreen_list.data(), fullscreen_list.size(), fs);

	////=======================================   VSYNC
	////==================================================
	// init vsync list
	std::vector<std::string> vsync_list;
	vsync_list.push_back(helperText::SettingsTexts::TEXT_OFF);
	vsync_list.push_back(helperText::SettingsTexts::TEXT_ON);

	// check current vsync and set it to selector like active element
	unsigned vs = 0;
	for (; vs < vsync_list.size(); vs++)
		if (vsync_list[vs] == (IstateData->sd_gfxSettings.lock()->verticalSync ? helperText::SettingsTexts::TEXT_ON : helperText::SettingsTexts::TEXT_OFF))
			break;

		// init selector vsync
	_selectors["SELEC_VSYNC"] = std::make_unique<gui::Selector>(
		sf::Vector2f(
		background_layer_pos.x + mmath::p2pX(55.f, background_layer_size.x),
		background_layer_pos.y + mmath::p2pX(25.f, background_layer_size.y)),
		button_size, font,  IstateData->sd_characterSize_game_medium,
		vsync_list.data(), vsync_list.size(), vs);

	////===================================   ANTIALIASING
	////==============================================
	// init antialiasing list
	std::vector<std::string> antialiasing_list = {helperText::SettingsTexts::TEXT_OFF, "x2", "x4", "x8", "x16"};

	std::string currentAA = "x" + std::to_string(IstateData->sd_gfxSettings.lock()->contextSettings.antiAliasingLevel);
	auto aalit =
		std::find(antialiasing_list.begin(), antialiasing_list.end(), currentAA);
	unsigned AAS = (aalit != antialiasing_list.end()) ? std::distance(antialiasing_list.begin(), aalit) : 0;

	// init selector antialiasing
	_selectors["SELEC_AAL"] = std::make_unique<gui::Selector>(
		sf::Vector2f(
		background_layer_pos.x + mmath::p2pX(55.f, background_layer_size.x),
		background_layer_pos.y + mmath::p2pX(35.f, background_layer_size.y)),
		button_size, font,  IstateData->sd_characterSize_game_medium,
		antialiasing_list.data(), antialiasing_list.size(), AAS);

	//=========================================   FPS
	//==================================================
	std::vector<std::string> fps_limits;
	std::transform(_gfxResource["GFX_FPS"].begin(), _gfxResource["GFX_FPS"].end(),
				   std::back_inserter(fps_limits),
				   [](const auto& x) { return std::to_string(x); });

	std::string currentFPS = std::to_string(IstateData->sd_gfxSettings.lock()->frameRateLimit);
	auto fpsit = std::find(fps_limits.begin(), fps_limits.end(), currentFPS);
	int fpls = (fpsit != fps_limits.end()) ? std::distance(fps_limits.begin(), fpsit) : 0;

	_selectors["SELEC_FPS"] = std::make_unique<gui::Selector>(
		sf::Vector2f(
		background_layer_pos.x + mmath::p2pX(55.f, background_layer_size.x),
		background_layer_pos.y + mmath::p2pX(45.f, background_layer_size.y)),
		button_size, font,  IstateData->sd_characterSize_game_medium,
		fps_limits.data(), fps_limits.size(), fpls);
}

void SettingsState::initSounsPage() { // init sound page
  //============================================================================================
  //================================		AUDIO SETTINGS		================================
  //============================================================================================

  // init sound sliders basic _pageBackground position and size
	sf::Vector2f slider_size = {mmath::p2pX(60.f, _pageBackground.getSize().x), 20.f};
	float offsetY = 20.f;
	sf::Vector2f bgsize = _pageBackground.getSize();
	sf::Vector2f bgpos = _pageBackground.getPosition();
	// next init all sliders for sound categories

	for (int i = 0; i< int(gfx::SoundCategory::vol_COUNT); i++)

		// init MASTER slider
	_sound_SliderMap[gfx::SoundCategory(i)] = std::make_unique<gui::SliderFloat>(
		sf::Vector2f(bgpos.x, bgpos.y + offsetY*i + slider_size.y * i), slider_size, font,
		IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory(i)),
		0.f, 100.f,  IstateData->sd_characterSize_game_medium, helperText::VolumeTexts::VOL_MASTER);

}

void SettingsState::initKeyboardPage() { // init keyboard page
	sf::Vector2u window_size =  Iwindow.lock()->getSize();
	sf::Vector2f wsf = {(float)(window_size.x), (float)(window_size.y)};

	sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(16.f, wsf.x), mmath::p2pX(5.f, wsf.y));
	sf::Text text( IstateData->sd_GameFont_basic, "", 24);
	sf::RectangleShape rectangle;
	rectangle.setFillColor(sf::Color(200, 200, 200, 150));

	int i = 0;
	int i2 = 0.f;
	for (const auto& keybind : * IstateData->sd_KeySupports.lock()) {
		text.setString(keybind.first + ": " + std::to_string(static_cast<int>(keybind.second)));

		float posX = mmath::p2pX(12.f * (i % 3), wsf.x);
		float posY = mmath::p2pX(40.f, wsf.y) + mmath::p2pX(3.f * (float)(i2 / 3), wsf.y);
		text.setPosition({posX, posY});

		rectangle.setSize(sf::Vector2f(text.getGlobalBounds().size.x, text.getGlobalBounds().size.y));
		rectangle.setPosition(text.getPosition());

		_keybindText.push_back(text);
		_keybindBackground.push_back(rectangle);
		i++;
		i2 = i;
	}
}

void SettingsState::initEctPage() {}
void SettingsState::initGameplayPage() {}

void SettingsState::resetGui() {
	//	reset to new resolution, and other settings
	//	with next saving
	//	TEST: check for correcd accsess to sd_gfxSettings
	gfx::myGFXStruct gfx = * IstateData->sd_gfxSettings.lock();

	gfx.resolution = _video_modes[_selectors["SELEC_VMODE"]->getActiveElementID()];
	gfx.frameRateLimit = _gfxResource["GFX_FPS"][_selectors["SELEC_FPS"].get()->getActiveElementID()];
	gfx.contextSettings.antiAliasingLevel = _gfxResource["GFX_ALL"][_selectors["SELEC_AAL"].get()->getActiveElementID()];
	gfx.fullscreen = _gfxResource["GFX_FULLSCREEN"][_selectors["SELEC_FULLSCREEN"]->getActiveElementID()];
	gfx.verticalSync = _gfxResource["GFX_VSYNC"][_selectors["SELEC_VSYNC"].get()->getActiveElementID()];

	// reset window
	if (gfx.fullscreen)
		 Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Fullscreen, gfx.contextSettings);
	else
		 Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Windowed, gfx.contextSettings);

	 Iwindow.lock()->setFramerateLimit(gfx.frameRateLimit);

	// save all data settings to file
	// add later
	//  IstateData->sd_gfxSettings.lock()->saveToFile();
	 IstateData->sd_reserGUI = true;

	_keybindBackground.clear();
	_sound_SliderMap.clear();
	_graphic_list.clear();
	_pageButtons.clear();
	_keybindText.clear();
	_pageButtons.clear();
	_video_modes.clear();
	_gfxResource.clear();
	_keybindText.clear();
	_selectors.clear();

	// init variables
	initVariables();

		// init fonts
	reCaclulateCharacterSize();
	initGui();
	resetView();
}

void SettingsState::initPageLayout() {}

SettingsState::SettingsState(StateData* state_data)
	: State(state_data), page(settingPage::GRAPHICS), pageName("GRAPHICS") { // init variables
	initRenderDefines();
	resetView();

	initPageLayout();
	initVariables();
	initFonts();
	initGui();

	Logger::logStatic("End initilization settings state", "SettingsState::SettingsState()", logType::LINFO);
}

SettingsState::~SettingsState() {
	Logger::logStatic("SettingsState destructor", "SettingsState::~SettingsState()", logType::LINFO);

	_selectors.clear();
	_pageButtons.clear();
	_keybindText.clear();
	_keybindBackground.clear();
	_video_modes.clear();
	_gfxResource.clear();
	_sound_SliderMap.clear();
	_graphic_list.clear();
}

// Functions
void SettingsState::updateInput(const float& delta_time) {
  // if escape is pressed, end state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) &&  getKeytime())
		 endState();
	  // if slash is pressed, swith debug mode
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash) &&  getKeytime())
		 Idebud = ! Idebud;

	  // if key Q is pressed, swith page to left (back)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) &&  getKeytime())
		 page = static_cast<settingPage>((static_cast<int>( page) - 1 + static_cast<int>(settingPage::PAGE_COUNT)) % static_cast<int>(settingPage::PAGE_COUNT));

	  // if key E is pressed, swith page to right (forward)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) &&  getKeytime())
		 page = static_cast<settingPage>((static_cast<int>( page) + 1) % static_cast<int>(settingPage::PAGE_COUNT));
}

// Update audio page
void SettingsState::updateAudioPage(const float& delta_time) {
	for (auto& it : _sound_SliderMap) {
		it.second->update( ImousePosView);

		if (it.second->isChangedValue()) {
			IstateData->sd_VolumeCollector.lock()->setCategoryVolume(it.first, it.second->getValue());
			 updateSounds(delta_time);
		}
	}
}

void SettingsState::updateSounds(const float& delta_time) {
 //   Isound.setVolume( IVolumeCollector->getCategoryVolume(gfx::SoundCategory::vol_MASTER) *  IVolumeCollector->getCategoryVolume(gfx::SoundCategory::vol_MUSIC) / 100);
}

	// Update graphics page
void SettingsState::updateGraphicsPage(const float& delta_time) {
	for (auto& it : _selectors)
		it.second->update(delta_time,  ImousePosWindow);
}

// Update controls page
void SettingsState::updateControlsPage(const float& delta_time) {}

// Update ect page
void SettingsState::updateEctPage(const float& delta_time) {}

void SettingsState::updateGui(const float& delta_time) {
	switch (page) {
	case settingPage::AUDIO:
		 updateAudioPage(delta_time);
		break;
	case settingPage::GRAPHICS:
		 updateGraphicsPage(delta_time);
		break;
	case settingPage::CONTROLS:
		 updateControlsPage(delta_time);
		break;
	case settingPage::GAMEPLAY:
		 updateEctPage(delta_time);
		break;
	default:
		break;
	}

	// update page buttons
	for (auto& it : _pageButtons)
		it.second->update( ImousePosWindow);

	  // update current page when page button is pressed
	if (_pageButtons["PGB_GRAPHICS"]->isPressed() &&  getKeytime())
		 page = settingPage::GRAPHICS;
	if (_pageButtons["PGB_CONTROLS"]->isPressed() &&  getKeytime())
		 page = settingPage::CONTROLS;
	if (_pageButtons["PGB_AUDIO"]->isPressed() &&  getKeytime())
		 page = settingPage::AUDIO;
	if (_pageButtons["PGB_GAMEPLAY"]->isPressed() &&  getKeytime())
		 page = settingPage::GAMEPLAY;

	if (_pageButtons["BACK_BTN"]->isPressed() &&  getKeytime())
		 endState();
	  // apply settings
	if (_pageButtons["APPLY_BTN"]->isPressed() &&  getKeytime())
		 resetGui();

	  // update pageName
	std::map<settingPage, std::string> pageNames = {
		{settingPage::GRAPHICS, helperText::SettingsTexts::TEXT_GRAPHICS},
		{settingPage::CONTROLS, helperText::SettingsTexts::TEXT_CONTROLS},
		{settingPage::AUDIO, helperText::SettingsTexts::TEXT_AUDIO},
		{settingPage::GAMEPLAY, helperText::SettingsTexts::TEXT_GAMEPLAY}};

	pageName = pageNames.count(page) ? pageNames[page] : "ERR";

	if ( Idebud) {
		 IstringStream
			<< "Ver: " << CMAKE_PROJECT_VERSION << "\nFPS:\t" << 1 / delta_time
			<< "\nCurrent memory usage:\t"
			//<< MemoryUsageMonitor::formatMemoryUsage(MemoryUsageMonitor::getCurrentMemoryUsage())
			<< "\nPage: " << pageName << " " << static_cast<int>( page)
			<< "\nSliders: "
			<< "\n\tMASTER: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_MASTER))
			<< "\n\tSFX: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_SFX))
			<< "\n\tMUSIC: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_MUSIC))
			<< "\n\tAMBIENT: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_AMBIENT))
			<< "\n\tENTITY: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_ENTITY))
			<< "\n\tUI: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_UI))
			<< "\n\tDIALOGUE: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_DIALOGUE))
			<< "\n\tFOLEY: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_FOLEY))
			<< "\n\tWEAPON: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_WEAPON))
			<< "\n\tENVIRONMENT: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_ENVIRONMENT))
			<< "\nVideo modes: " << _video_modes.size() << "\nVideo mode: "
			<< std::to_string( IstateData->sd_gfxSettings.lock()->resolution.size.x)
			<< std::to_string( IstateData->sd_gfxSettings.lock()->resolution.size.y)
			<< "\nFramerate limit: " + std::to_string( IstateData->sd_gfxSettings.lock()->frameRateLimit)
			<< "\nResolution: " <<  IstateData->sd_Window.lock()->getSize().x
			<< "x" <<  IstateData->sd_Window.lock()->getSize().y
			<< "\nAntialiasing: "
			<<  IstateData->sd_gfxSettings.lock()->contextSettings.antiAliasingLevel
			<< "\nvSync: " <<  IstateData->sd_gfxSettings.lock()->verticalSync
			<< "\nFullscreen: "
			<<  IstateData->sd_gfxSettings.lock()->fullscreen
			<< "\nSize of state: " << sizeof(*this) << " bytes"
			<< "\nkeytime: " <<  Ikeytime
			<< "\nMouse pos: " <<  ImousePosWindow.x << " "
			<<  ImousePosWindow.y << "\narrays LINFO:"
			<< "\n\tvideo_modes: " << _video_modes.size()
			<< "\n\tgfxResource: " << _gfxResource.size()
			<< "\n\tkeybindText: " << _keybindText.size()
			<< "\n\tkeybindBackground: " << _keybindBackground.size()
			<< "\n\tpageButtons: " << _pageButtons.size()
			<< "\n\tkeybindText: " << _keybindText.size()
			<< "\n\tselectors: " << _selectors.size()
			<< "\n\tgraphic_list: " << _graphic_list.size()
			<< "\n\tsound_SliderMap: " << _sound_SliderMap.size();

		 Itext.setString( IstringStream.str());
		 IstringStream.str("");
	}
}

void SettingsState::update(const float& delta_time) {
	//if (IstateData->sd_reserGUI) resetGUI();

	 updateMousePositions();
	 updateKeytime(delta_time);
	 updateInput(delta_time);
	 updateGui(delta_time);
}

void SettingsState::renderGui(sf::RenderTarget& target) {
	for (auto& it : _pageButtons)
		target.draw(*it.second);

	switch ( page) {
	case settingPage::GRAPHICS:
	  // draw text
		for (auto& it : _graphic_list)
			target.draw(it.first);
		  // draw selector
		for (auto& it : _selectors)
			it.second->render(target);
		break;
	case settingPage::CONTROLS:
	  // draw _text_shapes

	  // draw shapes for keybinds like background layer
	  // FIXME: fix layering of keybinds
		for (auto& it : _keybindBackground)
			target.draw(it);

		for (const auto& text : _keybindText)
			target.draw(text);
		break;
	case settingPage::AUDIO:
	  // TODO: add content to settings audio
	  // draw _sound_SliderMap
		for (auto& it : _sound_SliderMap)
			target.draw(*it.second.get());

		break;
	case settingPage::GAMEPLAY:
	  // TODO add content
		break;
	default:
		break;
	}
}
// Render page layout
void SettingsState::renderPageLayout(sf::RenderTarget& target) {
  // render page layout
	target.draw(_pageBackground);
}

void SettingsState::render(sf::RenderWindow& target) {
	target.draw( background);

	 renderPageLayout(target);
	 renderGui(target);

	if ( Idebud)
		target.draw( Itext);
}