#include "MainMenu.hpp"

void MainMenu::initBackground() {
	auto ws = Iwindow.lock()->getSize();
	sf::Texture tx;
	for (int i = 0; i < 3; i++)
		background_textures.push_back(sf::Texture());

	tx = TextureManager::getTexture("texture_background_lay_3");
	background_textures[0] = tx;
	tx = TextureManager::getTexture("texture_background_lay_2");
	background_textures[1] = tx;
	tx = TextureManager::getTexture("texture_background_lay_1");
	background_textures[2] = tx;

	// init background shapes
	for (size_t i = 0; i < 3; i++) {
		background_textures[i].setSmooth(true);
		backgrond_shapes.push_back(sf::RectangleShape());

		backgrond_shapes[i].setSize(sf::Vector2f(background_textures[i].getSize()));
		backgrond_shapes[i].setTexture(&background_textures[i], true);

		backgrond_shapes[i].setOrigin(
			sf::Vector2f(backgrond_shapes[i].getSize().x / 2, backgrond_shapes[i].getSize().y / 2));

		backgrond_shapes[i].setPosition(sf::Vector2f(
			static_cast<float>(ws.x) / 2 - (backgrond_shapes[i].getSize().x / 2) + backgrond_shapes[i].getOrigin().x,
			static_cast<float>(ws.y) / 2 - (backgrond_shapes[i].getSize().y / 2) + backgrond_shapes[i].getOrigin().y));
	}
	backgrond_shapes[0].scale(sf::Vector2f(2.f, 2.f));
}

void MainMenu::initButtons() {
	struct ButtonLINFO {
		std::string key;
		std::string text;

		ButtonLINFO(const char* k, std::string t): key(k), text(t) {}
	};

	auto ws = Iwindow.lock()->getSize();
	float offsetX = mmath::p2pX(5.f, static_cast<float>(ws.x));
	float offsetY = mmath::p2pX(5.f, static_cast<float>(ws.y));

	sf::Vector2f sizebutton{mmath::p2pX(15.f, (float)(ws.x)),mmath::p2pX(7.f, (float)(ws.y))};

	// Массив с координатами для каждой кнопки
	std::vector<sf::Vector2f> buttonOffsets = {
		{offsetX * 15.5f, offsetY * 2}, // noice
		{offsetX * 15.5f, offsetY * 10}, // continue
		{offsetX * 15.5f, offsetY * 12}, // start
		{offsetX * 15.5f, offsetY * 14}, // settings
		{offsetX * 15.5f, offsetY * 18} // exit
	};

	// Данные о кнопках
	std::vector<ButtonLINFO> buttonData = {
		{"NOICE_BTN", helperText::Button::BUTTON_NOICE_EDITOR},
		{"CONT_BTN", helperText::Button::BUTTON_CONTINUE},
		{"START_BTN", helperText::Button::BUTTON_PLAY},
		{"SETTINGS_BTN", helperText::Button::BUTTON_OPTIONS},
		{"EXIT_BTN", helperText::Button::BUTTON_EXIT}};

	// Добавляем кнопку для отладки в режиме отладки
#ifdef _DEBUG
	buttonData.push_back({"DRS_BTN", helperText::Button::BUTTON_DEBUG_ROOM_STATE});

	// Добавляем позицию для кнопки отладки
	buttonOffsets.push_back({offsetX, offsetY});
#endif

	//Цикл для создания кнопок с данными из массива
	for (size_t i = 0; i < buttonData.size(); ++i) {
		const auto& button = buttonData[i];
		IGUILayout[button.key] = std::make_unique<gui::Button>(buttonOffsets[i], sizebutton, button.text);
	}
}

void MainMenu::initGUI() {
	Itext.setCharacterSize(IstateData->sd_characterSize_debug);
	initBackground();
	initButtons();

}

void MainMenu::resetGUI() {
	// delete buttons
	if (!IGUILayout.empty())
		IGUILayout.clear();
	backgrond_shapes.clear();
	//// reset window
	//auto& gfx = *IstateData->sd_gfxSettings.lock();
	//if (gfx.fullscreen)
	//	Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Fullscreen, gfx.contextSettings);
	//else
	//	Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Windowed, gfx.contextSettings);

	//Iwindow.lock()->setFramerateLimit(gfx.frameRateLimit);

//	initRenderDefines();
	resetView();

	reCaclulateCharacterSize();

	initGUI();
	IstateData->sd_reserGUI = false;
}

void MainMenu::initSounds() {
	try {
		for (const auto& [category, soundKey, mapKey] :
			 {std::tuple{gfx::SoundCategory::vol_MUSIC, appfn::path::sounds::music_menu, "MAIN_MENU"},
			 {gfx::SoundCategory::vol_UI, appfn::path::sounds::selbtn_menu, "SELECT_MENU"},
			 {gfx::SoundCategory::vol_UI, appfn::path::sounds::press_newg, "PRESS_NEW_GAME"},
			 {gfx::SoundCategory::vol_UI, appfn::path::sounds::press_btn, "PRESS_BUTTON"}})
			if (!loadSoundtoBuffer(category, soundKey, mapKey)) {
				char tmp[256];
				sprintf(tmp, "%s", soundKey);
				throw std::exception(tmp);
			}
	} catch (std::exception& e) {
		appfn::Logger::logStatic("can't load: " + std::string(e.what()), "MainMenu::initSounds()", logType::LERROR);
	}

	// Upload sounds from buffer
	for (const auto& [mapKey, category] :
		 {std::pair{"MAIN_MENU", gfx::SoundCategory::vol_MUSIC},
		 {"SELECT_MENU", gfx::SoundCategory::vol_UI},
		 {"PRESS_NEW_GAME", gfx::SoundCategory::vol_UI},
		 {"PRESS_BUTTON", gfx::SoundCategory::vol_UI}}) {
		IsoundsMap.emplace(mapKey, IsoundBufferMap[category][mapKey]);
	}

	// set volume in sound map
	updateSounds(0.f);
}

MainMenu::MainMenu(StateData* statedata)
	: State(statedata) {
	// logger
	appfn::Logger::logStatic("MainMenu constructor", "MainMenu");
	initRenderDefines();
	initGUI();

	initButtons();
	initSounds();
}

MainMenu::~MainMenu() {
	appfn::Logger::logStatic("MainMenu destructor", "MainMenu");

	// delete buttons
	if (!IGUILayout.empty()) IGUILayout.clear();

	backgrond_shapes.clear();
	IsoundsMap.clear();
	IsoundBufferMap.clear();
}

void MainMenu::updateDebugTextState(const float& delta_time) {
		IstringStream
			<< "\nVolume: "
			<< "\n\tMASTER: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_MASTER))
			<< "\n\tSFX: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_SFX))
			<< "\n\tMUSIC: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_MUSIC))
			<< "\n\tAMBIENT: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_AMBIENT))
			<< "\n\tENTITY: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_ENTITY))
			<< "\n\tUI: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_UI))
			<< "\n\tDIALOGUE: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_DIALOGUE))
			<< "\n\tFOLEY: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_FOLEY))
			<< "\n\tWEAPON: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_WEAPON))
			<< "\n\tENVIRONMENT: " + std::to_string(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(gfx::SoundCategory::vol_ENVIRONMENT));
}

void MainMenu::update(const float& delta_time) {
	if (IstateData->sd_reserGUI) resetGUI();

	updateKeytime(delta_time);
	updateGUI(delta_time);
	updateMousePositions(&view);
	updateInput(delta_time);
	updateButtons();
	updateSounds(delta_time);

	if (Idebud) {
		updateDebugTextBase(delta_time);
		updateDebugTextState(delta_time);
		updateDebugText();
	}
}

void MainMenu::updateInput(const float& delta_time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash) && getKeytime())
		Idebud = !Idebud;
}

void MainMenu::updateButtons() {
	if (!IGUILayout.empty()) {
		sf::Vector2f pos = {float(ImousePosWindow.x), float(ImousePosWindow.y)};
		auto& it = IGUILayout;
		for (auto& q : it)
			q.second.get()->update(sf::Vector2f(ImousePosWindow));
	}

	//	if (it.second->isPressed())
	//		if (IsoundsMap.find("PRESS_BUTTON")->second.getStatus() != sf::Sound::Status::Playing) IsoundsMap.at("PRESS_BUTTON").play(); // play sound once
	//	if (it.second->isHover())
	//		if (IsoundsMap.find("SELECT_MENU")->second.getStatus() != sf::Sound::Status::Playing) IsoundsMap.at("SELECT_MENU").play(); // play sound once
	//}

	if (IGUILayout["EXIT_BTN"]->isPressed() && getKeytime())
		endState();

	if (IGUILayout["START_BTN"]->isPressed() && getKeytime())
		Istates->push(new Process(IstateData, false));

	// if (buttons["CONT_BTN"]->isPressed() && getKeytime()) {
	//  Istates->push(new Process(IstateData, true));
	//  resetView();
	// }
	if (IGUILayout["SETTINGS_BTN"]->isPressed() && getKeytime())
		Istates->push(new SettingsState(IstateData));

	if (IGUILayout["NOICE_BTN"]->isPressed() && getKeytime())
		Istates->push(new EditorState(IstateData));

}

void MainMenu::updateGUI(const float& delta_time) {
	// update debug text
	

	// update GUI
	backgrond_shapes[0].rotate(sf::degrees(delta_time));
	backgrond_shapes[1].rotate(sf::degrees(-delta_time));
}

void MainMenu::updateSounds(const float& delta_time) {
	// update for music menu
	for (const auto& [key, category] :
		 {std::pair{"MAIN_MENU", gfx::SoundCategory::vol_MUSIC},
		 {"SELECT_MENU", gfx::SoundCategory::vol_UI},
		 {"PRESS_NEW_GAME", gfx::SoundCategory::vol_UI},
		 {"PRESS_BUTTON", gfx::SoundCategory::vol_UI}}) {
		auto it = IsoundsMap.find(key);
		if (it != IsoundsMap.end())
			it->second.setVolume(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(category));
	}

	// check for playing music "main menu"
	if (IsoundsMap.find("MAIN_MENU")->second.getStatus() != sf::Sound::Status::Playing)
		IsoundsMap.find("MAIN_MENU")->second.play();

	// check for playing sound "select menu" when cursor on button

	// stop if lost focus on window
	if (!Iwindow.lock()->hasFocus())
		for (auto& it : IsoundsMap)
			it.second.pause();
}

void MainMenu::render(sf::RenderWindow& target) {
	IRenderTexture.clear();
	IRenderTexture.setView(view);
	for (auto& it : backgrond_shapes)
		IRenderTexture.draw(it);

	if (!IGUILayout.empty())
		for (auto& it : IGUILayout)
			IRenderTexture.draw(*it.second.get());

	//renderTexture.setView(target.getDefaultView());
	if (Idebud) IRenderTexture.draw(Itext);

	IRenderTexture.display();
	target.draw(IRenderSprite);
}