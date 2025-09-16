#include "MainMenu.hpp"
#include <IOKit/hid/IOHIDUsageTables.h>

void MainMenu::initRenderDefines() {
  if (!renderTexture.resize({IstateData->sd_Window.lock()->getSize().x,
                             IstateData->sd_Window.lock()->getSize().y}))
    Logger::logStatic("renderTexture cannot be resize",
                      "MainMenu::initRenderDefines()", logType::ERROR);
  renderTexture.setSmooth(true);

  renderSprite.setTexture(renderTexture.getTexture());
  renderSprite.setTextureRect(sf::IntRect(
      {0, 0}, {static_cast<int>(IstateData->sd_Window.lock()->getSize().x),
               static_cast<int>(IstateData->sd_Window.lock()->getSize().y)}));

  view.setSize(sf::Vector2f(
      static_cast<float>(IstateData->sd_Window.lock()->getSize().x),
      static_cast<float>(IstateData->sd_Window.lock()->getSize().y)));

  view.setCenter(sf::Vector2f(
      static_cast<float>(IstateData->sd_Window.lock()->getSize().x) / 2,
      static_cast<float>(IstateData->sd_Window.lock()->getSize().y) / 2));
}

void MainMenu::initKeybinds() {
  Ikeybinds["CLOSE"] = IsupportedKeys->at("Escape");
  IkeyBinds["KEY_SLASH"] = IKeyboard.lock().->at("Slash");
  Ikeybinds["KEY_R"] = IsupportedKeys->at("R");
}

void MainMenu::initBackground() {

  sf::Texture tx;
  for (int i = 0; i < 3; i++) {
    background_textures.push_back(sf::Texture());
  }
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
        sf::Vector2f(backgrond_shapes[i].getSize().x / 2,
                     backgrond_shapes[i].getSize().y / 2));

    backgrond_shapes[i].setPosition(sf::Vector2f(
        static_cast<float>(IstateData->sd_Window.lock()->getSize().x) / 2 -
            (backgrond_shapes[i].getSize().x / 2) +
            backgrond_shapes[i].getOrigin().x,
        static_cast<float>(IstateData->sd_Window.lock()->getSize().y) / 2 -
            (backgrond_shapes[i].getSize().y / 2) +
            backgrond_shapes[i].getOrigin().y));
  }
  backgrond_shapes[0].scale(sf::Vector2f(2.f, 2.f));
}

void MainMenu::initButtons() {
  struct ButtonInfo {
    std::string key;
    std::string text;

    ButtonInfo(const char *k, std::string t) : key(k), text(t) {}
  };

  float offsetX = mmath::p2pX(5, Iwindow.lock()->getSize().x);
  float offsetY = mmath::p2pX(5, Iwindow.lock()->getSize().y);

  sf::Vector2f sizebutton = {mmath::p2pX(15, Iwindow.lock()->getSize().x),
                             mmath::p2pX(7, Iwindow.lock()->getSize().y)};
  // Массив с координатами для каждой кнопки
  std::vector<sf::Vector2f> buttonOffsets = {
      {offsetX * 15.5f, offsetY * 2},  // noice
      {offsetX * 15.5f, offsetY * 10}, // continue
      {offsetX * 15.5f, offsetY * 12}, // start
      {offsetX * 15.5f, offsetY * 14}, // settings
      {offsetX * 15.5f, offsetY * 18}  // exit
  };

  // Данные о кнопках
  std::vector<ButtonInfo> buttonData = {
      {"NOICE_BTN", helperText::Button::BUTTON_NOICE_EDITOR},
      {"CONT_BTN", helperText::Button::BUTTON_CONTINUE},
      {"START_BTN", helperText::Button::BUTTON_PLAY},
      {"SETTINGS_BTN", helperText::Button::BUTTON_OPTIONS},
      {"EXIT_BTN", helperText::Button::BUTTON_EXIT}};

// Добавляем кнопку для отладки в режиме отладки
#if __MDEBUG__ == 1
  buttonData.push_back(
      {"DRS_BTN", helperText::Button::BUTTON_DEBUG_ROOM_STATE});

  // Добавляем позицию для кнопки отладки
  buttonOffsets.push_back({offsetX, offsetY});
#endif

  // Цикл для создания кнопок с данными из массива
  for (size_t i = 0; i < buttonData.size(); ++i) {
    const auto &button = buttonData[i];
    buttons[button.key] = std::make_unique<gui::Button>(
        buttonOffsets[i], sizebutton, button.text,
        gui::styles::buttons::btn_default, gui::type::BUTTON);
  }
}
void MainMenu::initGUI() {
  initBackground();
  initButtons();
}

void MainMenu::resetGUI() {
  // delete buttons
  if (!buttons.empty())
    buttons.clear();

  backgrond_shapes.clear();

  initBackground();
  initButtons();
  initRenderDefines();
  IstateData->reserGUI = false;
}

void MainMenu::resetView() {
  view.setSize(sf::Vector2f(
      static_cast<float>(IstateData->sd_Window.lock()->getSize().x),
      static_cast<float>(IstateData->sd_Window.lock()->getSize().y)));

  view.setCenter(sf::Vector2f(
      static_cast<float>(IstateData->sd_Window.lock()->getSize().x) / 2,
      static_cast<float>(IstateData->sd_Window.lock()->getSize().y) / 2));
}

void MainMenu::initSounds() {
  // link to volume manager
  IVolumeCollector = IstateData->sd_VolumeCollector;

  try {
    for (const auto &[category, soundKey, mapKey] :
         {std::tuple{SoundCategory::vol_MUSIC, myConst::sounds::music_menu,
                     "MAIN_MENU"},
          {SoundCategory::vol_UI, myConst::sounds::selbtn_menu, "SELECT_MENU"},
          {SoundCategory::vol_UI, myConst::sounds::press_newg,
           "PRESS_NEW_GAME"},
          {SoundCategory::vol_UI, myConst::sounds::press_btn,
           "PRESS_BUTTON"}}) {
      if (!loadSoundtoBuffer(category, soundKey, mapKey)) {
        throw soundKey;
      }
    }
  } catch (std::exception &e) {
    Logger::logStatic("can't load: " + std::string(e.what()),
                      "MainMenu::initSounds()", logType::ERROR);
  }

  // Upload sounds from buffer
  for (const auto &[mapKey, category] :
       {std::pair{"MAIN_MENU", SoundCategory::vol_MUSIC},
        {"SELECT_MENU", SoundCategory::vol_UI},
        {"PRESS_NEW_GAME", SoundCategory::vol_UI},
        {"PRESS_BUTTON", SoundCategory::vol_UI}}) {
    IsoundsMap.emplace(mapKey, IsoundBufferMap[category][mapKey]);
  }

  // set volume in sound map
  updateSounds(0.f);
}

MainMenu::MainMenu(StateData *statedata)
    : State(statedata),
      renderSprite(TextureManager::getTexture("texture_null")) {
  // logger
  Logger::logStatic("MainMenu constructor", "MainMenu");
  initRenderDefines();
  initGUI();
  initKeybinds();
  initButtons();
  initSounds();
}

MainMenu::~MainMenu() {
  Logger::logStatic("MainMenu destructor", "MainMenu");

  // delete buttons
  if (!buttons.empty())
    buttons.clear();

  backgrond_shapes.clear();
  IsoundsMap.clear();
  IsoundBufferMap.clear();
}

void MainMenu::update(const float &delta_time) {
  if (IstateData->reserGUI)
    resetGUI();

  updateKeytime(delta_time);

  updateGUI(delta_time);

  updateMousePositions(&view);
  updateInput(delta_time);
  updateButtons();
  updateSounds(delta_time);
}

void MainMenu::updateInput(const float &delta_time) {
  if (Ikeyboard.lock()->isKeyPressed(Ikeybinds.at("KEY_SLASH")) && getKeytime())
    Idebud = !Idebud;

  if (Ikeyboard.lock()->isKeyPressed(Ikeybinds.at("KEY_R")) && getKeytime())
    resetGUI();
}

void MainMenu::updateButtons() {
  if (!buttons.empty()) {
    for (auto &it : buttons) {

      it.second->update(ImousePosWindow);
      if (it.second->isPressed())
        if (IsoundsMap.find("PRESS_BUTTON")->second.getStatus() !=
            sf::Sound::Status::Playing)
          IsoundsMap.at("PRESS_BUTTON").play(); // play sound once
      if (it.second->isHover())
        if (IsoundsMap.find("SELECT_MENU")->second.getStatus() !=
            sf::Sound::Status::Playing)
          IsoundsMap.at("SELECT_MENU").play(); // play sound once
    }

    if (buttons["EXIT_BTN"]->isPressed() && getKeytime()) {
      endState();
    }

    if (buttons["START_BTN"]->isPressed() && getKeytime()) {
      Istates->push(new Process(IstateData, false));
    }

    if (buttons["CONT_BTN"]->isPressed() && getKeytime()) {
      Istates->push(new Process(IstateData, true));
      resetView();
    }
    if (buttons["SETTINGS_BTN"]->isPressed() && getKeytime())
      Istates->push(new SettingsState(IstateData));

    if (buttons["NOICE_BTN"]->isPressed() && getKeytime())
      Istates->push(new EditorState(IstateData));
  }
}

void MainMenu::updateGUI(const float &delta_time) {
  // update debug text
  if (Idebud) {
    IstringStream
        << "\nver:\t" << CMAKE_PROJECT_VERSION << "\nCurrent memory usage:\t"
        << MemoryUsageMonitor::formatMemoryUsage(
               MemoryUsageMonitor::getCurrentMemoryUsage())
        << "\nCurrent state memory usage:\t" << getMemoryUsage() << " bytes"
        << "\nFPS delta:\t" << 1 / delta_time << "\nFPS Clock:\t"
        << FPS::getFPS() << "\nFPS limit:\t"
        << IstateData->sd_gfxSettings.lock()->_struct.frameRateLimit
        << "\nDelta Time:\t" << delta_time << "\nResolution:\t"
        << IstateData->sd_Window.lock()->getSize().x << " x "
        << IstateData->sd_Window.lock()->getSize().y << "\nAntialiasing:\t"
        << IstateData->sd_Window.lock()->getSettings().antiAliasingLevel
        << "\nvSync:\t"
        << IstateData->sd_gfxSettings.lock()->_struct.verticalSync
        << "\nMouse Pos:\t" << ImousePosWindow.x << " x " << ImousePosWindow.y
        << "\nVolume: "
        << "\n\tMASTER: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_MASTER))
        << "\n\tSFX: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_SFX))
        << "\n\tMUSIC: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_MUSIC))
        << "\n\tAMBIENT: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_AMBIENT))
        << "\n\tENTITY: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_ENTITY))
        << "\n\tUI: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_UI))
        << "\n\tDIALOGUE: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_DIALOGUE))
        << "\n\tFOLEY: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_FOLEY))
        << "\n\tWEAPON: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_WEAPON))
        << "\n\tENVIRONMENT: " +
               std::to_string(
                   IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
                       SoundCategory::vol_ENVIRONMENT));
    Itext.setString(IstringStream.str());
    IstringStream.str("");
  }

  // update GUI
  backgrond_shapes[0].rotate(sf::degrees(delta_time));
  backgrond_shapes[1].rotate(sf::degrees(-delta_time));
}

void MainMenu::updateSounds(const float &delta_time) {
  // update for music menu
  for (const auto &[key, category] :
       {std::pair{"MAIN_MENU", SoundCategory::vol_MUSIC},
        {"SELECT_MENU", SoundCategory::vol_UI},
        {"PRESS_NEW_GAME", SoundCategory::vol_UI},
        {"PRESS_BUTTON", SoundCategory::vol_UI}}) {
    auto it = IsoundsMap.find(key);
    if (it != IsoundsMap.end()) {
      it->second.setVolume(IVolumeCollector->getCategoryVolume(category));
    }
  }

  // check for playing music "main menu"
  if (IsoundsMap.find("MAIN_MENU")->second.getStatus() !=
      sf::Sound::Status::Playing)
    IsoundsMap.find("MAIN_MENU")->second.play();

  // check for playing sound "select menu" when cursor on button

  // stop if lost focus on window
  if (!Iwindow.lock()->hasFocus())
    for (auto &it : IsoundsMap)
      it.second.pause();
}

void MainMenu::render(sf::RenderWindow &target) {
  renderTexture.clear();
  renderTexture.setView(view);

  // render background shapes
  for (auto &it : backgrond_shapes)
    renderTexture.draw(it);

  // render GUI
  if (!buttons.empty())
    for (auto &it : buttons)
      renderTexture.draw(
          *it.second
               .get()); // Отрисовываем кнопки в renderTexture, а не в target

  // debug text
  if (Idebud)
    renderTexture.draw(Itext);

  renderTexture.setView(renderTexture.getDefaultView());

  renderTexture.display();

  target.draw(renderSprite);
}