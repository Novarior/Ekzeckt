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
  this->font = this->IstateData->sd_GameFont_basic;
}

void SettingsState::initKeybinds() { // init key escape like defoult back button
  IkeyBinds["KEY_BACK"] = IstateData->sd_KeySupports.lock()->at("Escape");
  IkeyBinds["KEY_SLASH"] = IstateData->sd_KeySupports.lock()->at("Slash");
  IkeyBinds["KEY_BACK_PAGE"] = IstateData->sd_KeySupports.lock()->at("Q");
  IkeyBinds["KEY_FORWARD_PAGE"] = IstateData->sd_KeySupports.lock()->at("E");
  IkeyBinds["KEY_A"] = IstateData->sd_KeySupports.lock()->at("A");
  IkeyBinds["KEY_W"] = IstateData->sd_KeySupports.lock()->at("W");
  IkeyBinds["KEY_S"] = IstateData->sd_KeySupports.lock()->at("S");
  IkeyBinds["KEY_D"] = IstateData->sd_KeySupports.lock()->at("D");
}

void SettingsState::initGui() { // init gui with next call functions
  //
  sf::Vector2u window_size = this->Iwindow.lock()->getSize();

  // init background
  this->background.setSize(sf::Vector2f(window_size.x, window_size.y));
  // darkest blue color
  this->background.setFillColor(sf::Color(3, 3, 30, 100));

  // init page background
  _pageBackground.setSize(sf::Vector2f( // size of page background
      mmath::p2pX(70, window_size.x), mmath::p2pX(66, window_size.y)));

  _pageBackground.setPosition(sf::Vector2f( // position of page background
      mmath::p2pX(50, window_size.x) - _pageBackground.getSize().x / 2,
      mmath::p2pX(50, window_size.y) - _pageBackground.getSize().y / 2));
  _pageBackground.setFillColor(sf::Color(140, 140, 140, 140));

  sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(16, window_size.x),
                                          mmath::p2pX(5, window_size.y));

  this->initButtons();
  this->initGraphicsPage();
  this->initSounsPage();
  this->initGameplayPage();
  this->initKeyboardPage();
  this->initEctPage();
}

void SettingsState::initButtons() { // Navigaton buttons in settings
  sf::Vector2u window_size = this->Iwindow.lock()->getSize();
  sf::Vector2f background_layer_pos = sf::Vector2f(
      mmath::p2pX(50, window_size.x) - _pageBackground.getSize().x / 2,
      mmath::p2pX(50, window_size.y) - _pageBackground.getSize().y / 2);
  sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(10, window_size.x),
                                          mmath::p2pX(5, window_size.y));

  // exit gui button
  _pageButtons["BACK_BTN"] = std::make_unique<gui::Button>(
      sf::Vector2f(window_size.x - 120, 0.f), sf::Vector2f(120.f, 50.f),
      helperText::Button::BUTTON_BACK, gui::styles::buttons::btn_default,
      gui::type::BUTTON);
  // apply gui button
  // set "apply" button position litle bit left from "back" button
  _pageButtons["APPLY_BTN"] = std::make_unique<gui::Button>(
      sf::Vector2f(window_size.x - 240, 0.f), sf::Vector2f(120.f, 50.f),
      helperText::Button::BUTTON_APPLY, gui::styles::buttons::btn_default,
      gui::type::BUTTON);

  //============================================================================
  //==========================    PAGE BUTTONS    ==============================
  //============================================================================

  // init page buttons
  // five buttons for five pages in one row
  // have to be in the same order as settingPage enum

  _pageButtons["PGB_AUDIO"] = std::make_unique<gui::Button>(
      sf::Vector2f(background_layer_pos.x,
                   background_layer_pos.y - button_size.y),
      button_size, helperText::SettingsTexts::TEXT_AUDIO,
      gui::styles::buttons::btn_default, gui::type::BUTTON);

  _pageButtons["PGB_GRAPHICS"] = std::make_unique<gui::Button>(
      sf::Vector2f(background_layer_pos.x + button_size.x,
                   background_layer_pos.y - button_size.y),
      button_size, helperText::SettingsTexts::TEXT_GRAPHICS,
      gui::styles::buttons::btn_default, gui::type::BUTTON);

  _pageButtons["PGB_CONTROLS"] = std::make_unique<gui::Button>(
      sf::Vector2f(background_layer_pos.x + button_size.x * 2,
                   background_layer_pos.y - button_size.y),
      button_size, helperText::SettingsTexts::TEXT_CONTROLS,
      gui::styles::buttons::btn_default, gui::type::BUTTON);

  _pageButtons["PGB_GAMEPLAY"] = std::make_unique<gui::Button>(
      sf::Vector2f(background_layer_pos.x + button_size.x * 3,
                   background_layer_pos.y - button_size.y),
      button_size, helperText::SettingsTexts::TEXT_GAMEPLAY,
      gui::styles::buttons::btn_default, gui::type::BUTTON);
}

void SettingsState::initGraphicsPage() {
  //=======================================   GRAPHICS
  //===============================================
  sf::Vector2u window_size = this->Iwindow.lock()->getSize();
  sf::Vector2f background_layer_pos = sf::Vector2f(
      mmath::p2pX(50, window_size.x) - _pageBackground.getSize().x / 2,
      mmath::p2pX(50, window_size.y) - _pageBackground.getSize().y / 2);
  sf::Vector2f background_layer_size = sf::Vector2f(
      mmath::p2pX(70, window_size.x), mmath::p2pX(66, window_size.y));
  sf::Vector2f button_size =
      sf::Vector2f(mmath::p2pX(20, background_layer_size.x),
                   mmath::p2pX(5, background_layer_size.y));

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
        background_layer_pos.x + mmath::p2pX(5, background_layer_size.x),
        background_layer_pos.y + mmath::p2pX(5, background_layer_size.y) +
            i * mmath::p2pX(10, background_layer_size.y)));
    shape.setSize(sf::Vector2f(mmath::p2pX(20, background_layer_size.x),
                               mmath::p2pX(5, background_layer_size.y)));
    sf::Text text(this->font, settingsNames[i],
                  this->IstateData->sd_characterSize_game_medium);

    text.setPosition(sf::Vector2f(shape.getPosition().x,
                                  shape.getPosition().y +
                                      (shape.getGlobalBounds().position.y / 2) -
                                      (text.getGlobalBounds().position.y / 2)));

    _graphic_list.push_back(std::make_pair(text, shape));
  }

  //=====================================   RESOLUTION
  //===============================================
  // init dropdown list with video modes
  std::vector<std::string> modes_str;
  int index = 0;
  for (auto &i : _video_modes) {
    modes_str.push_back(std::to_string(i.size.x) + " x " +
                        std::to_string(i.size.y));
    if (i.size.x ==
            IstateData->sd_gfxSettings.lock()->_struct.resolution.size.x &&
        i.size.y ==
            IstateData->sd_gfxSettings.lock()->_struct.resolution.size.y)
      index = modes_str.size() - 1;
  }

  // init selector with video modes
  _selectors["SELEC_VMODE"] = std::make_unique<gui::Selector>(
      sf::Vector2f(
          background_layer_pos.x + mmath::p2pX(55, background_layer_size.x),
          background_layer_pos.y + mmath::p2pX(5, background_layer_size.y)),
      button_size, font, this->IstateData->sd_characterSize_game_medium,
      modes_str.data(), modes_str.size(), index);

  //===================================   FULLSCREEN
  //=================================================
  // init fullscreen list
  std::vector<std::string> fullscreen_list;
  fullscreen_list.push_back("Windowed");
  fullscreen_list.push_back("Fullscreen");

  // check current fullscreen and set it to selector like active element
  unsigned fs = 0;
  for (; fs < fullscreen_list.size(); fs++)
    if (fullscreen_list[fs] ==
        (IstateData->sd_gfxSettings.lock()->_struct.fullscreen ? "Fullscreen"
                                                               : "Windowed"))
      break;

  // init selector fullscreen
  _selectors["SELEC_FULLSCREEN"] = std::make_unique<gui::Selector>(
      sf::Vector2f(
          background_layer_pos.x + mmath::p2pX(55, background_layer_size.x),
          background_layer_pos.y + mmath::p2pX(15, background_layer_size.y)),
      button_size, font, this->IstateData->sd_characterSize_game_medium,
      fullscreen_list.data(), fullscreen_list.size(), fs);

  //=======================================   VSYNC
  //==================================================
  // init vsync list
  std::vector<std::string> vsync_list;
  vsync_list.push_back(helperText::SettingsTexts::TEXT_OFF);
  vsync_list.push_back(helperText::SettingsTexts::TEXT_ON);

  // check current vsync and set it to selector like active element
  unsigned vs = 0;
  for (; vs < vsync_list.size(); vs++)
    if (vsync_list[vs] ==
        (IstateData->sd_gfxSettings.lock()->_struct.verticalSync
             ? helperText::SettingsTexts::TEXT_ON
             : helperText::SettingsTexts::TEXT_OFF))
      break;

  // init selector vsync
  _selectors["SELEC_VSYNC"] = std::make_unique<gui::Selector>(
      sf::Vector2f(
          background_layer_pos.x + mmath::p2pX(55, background_layer_size.x),
          background_layer_pos.y + mmath::p2pX(25, background_layer_size.y)),
      button_size, font, this->IstateData->sd_characterSize_game_medium,
      vsync_list.data(), vsync_list.size(), vs);

  //===================================   ANTIALIASING
  //==============================================
  // init antialiasing list
  std::vector<std::string> antialiasing_list = {
      helperText::SettingsTexts::TEXT_OFF, "x2", "x4", "x8", "x16"};

  std::string currentAA =
      "x" + std::to_string(IstateData->sd_gfxSettings.lock()
                               ->_struct.contextSettings.antiAliasingLevel);
  auto aalit =
      std::find(antialiasing_list.begin(), antialiasing_list.end(), currentAA);
  unsigned AAS = (aalit != antialiasing_list.end())
                     ? std::distance(antialiasing_list.begin(), aalit)
                     : 0;

  // init selector antialiasing
  _selectors["SELEC_AAL"] = std::make_unique<gui::Selector>(
      sf::Vector2f(
          background_layer_pos.x + mmath::p2pX(55, background_layer_size.x),
          background_layer_pos.y + mmath::p2pX(35, background_layer_size.y)),
      button_size, font, this->IstateData->sd_characterSize_game_medium,
      antialiasing_list.data(), antialiasing_list.size(), AAS);

  //=========================================   FPS
  //==================================================
  std::vector<std::string> fps_limits;
  std::transform(_gfxResource["GFX_FPS"].begin(), _gfxResource["GFX_FPS"].end(),
                 std::back_inserter(fps_limits),
                 [](const auto &x) { return std::to_string(x); });

  std::string currentFPS =
      std::to_string(IstateData->sd_gfxSettings.lock()->_struct.frameRateLimit);
  auto fpsit = std::find(fps_limits.begin(), fps_limits.end(), currentFPS);
  int fpls = (fpsit != fps_limits.end())
                 ? std::distance(fps_limits.begin(), fpsit)
                 : 0;

  _selectors["SELEC_FPS"] = std::make_unique<gui::Selector>(
      sf::Vector2f(
          background_layer_pos.x + mmath::p2pX(55, background_layer_size.x),
          background_layer_pos.y + mmath::p2pX(45, background_layer_size.y)),
      button_size, font, this->IstateData->sd_characterSize_game_medium,
      fps_limits.data(), fps_limits.size(), fpls);
}

void SettingsState::initSounsPage() { // init sound page
  //=====================================================================================================
  //=====================================   AUDIO SETTINGS
  //===========================================
  //=====================================================================================================

  // init sound sliders basic _pageBackground position and size
  float slidersizeX = mmath::p2pX(60, _pageBackground.getSize().x);
  float slidersizeY = mmath::p2pX(10, _pageBackground.getSize().y);
  sf::Vector2f slider_size = sf::Vector2f(slidersizeX, slidersizeY);
  sf::Vector2f background_size = _pageBackground.getSize();
  sf::Vector2f offset_position_for_sliders =
      _pageBackground.getPosition() /
      2.f; // init slider from top left corner of _pageBackground
  // next init all sliders for sound categories

  _sound_SliderMap[SoundCategory::vol_MASTER] =
      std::make_unique<gui::SliderInt>( // init MASTER slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_MASTER),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_MASTER);

  _sound_SliderMap[SoundCategory::vol_SFX] =
      std::make_unique<gui::SliderInt>( // init SFX slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(10, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_SFX),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_SFX);

  _sound_SliderMap[SoundCategory::vol_MUSIC] =
      std::make_unique<gui::SliderInt>( // init MUSIC slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(20, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_MUSIC),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_MUSIC);

  _sound_SliderMap[SoundCategory::vol_AMBIENT] =
      std::make_unique<gui::SliderInt>( // init AMBIENT slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(30, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_AMBIENT),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_AMBIENT);

  _sound_SliderMap[SoundCategory::vol_ENTITY] =
      std::make_unique<gui::SliderInt>( // init ENTITY slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(50, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_ENTITY),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_ENTITYSFX);

  _sound_SliderMap[SoundCategory::vol_UI] =
      std::make_unique<gui::SliderInt>( // init UI slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(60, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_UI),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_UI_VOL);

  _sound_SliderMap[SoundCategory::vol_DIALOGUE] =
      std::make_unique<gui::SliderInt>( // init DIALOGUE slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(70, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_DIALOGUE),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_DIALOGUE_VOL);

  _sound_SliderMap[SoundCategory::vol_FOLEY] =
      std::make_unique<gui::SliderInt>( // init FOLEY slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(80, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_FOLEY),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_FOLEYVOL);

  _sound_SliderMap[SoundCategory::vol_WEAPON] =
      std::make_unique<gui::SliderInt>( // init WEAPON slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(90, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_WEAPON),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_WEAPONVOL);

  _sound_SliderMap[SoundCategory::vol_ENVIRONMENT] =
      std::make_unique<gui::SliderInt>( // init ENVIRONMENT slider
          sf::Vector2f(offset_position_for_sliders.x +
                           mmath::p2pX(50, background_size.x),
                       offset_position_for_sliders.y +
                           mmath::p2pX(100, background_size.y)),
          slider_size, font,
          IstateData->sd_VolumeCollector.lock()->getCategoryVolume(
              SoundCategory::vol_ENVIRONMENT),
          0, 100, 1, this->IstateData->sd_characterSize_game_medium,
          helperText::VolumeTexts::VOL_ENVIRONMENTVOL);
}

void SettingsState::initKeyboardPage() { // init keyboard page
  sf::Vector2u window_size = this->Iwindow.lock()->getSize();
  sf::Vector2f button_size = sf::Vector2f(mmath::p2pX(16, window_size.x),
                                          mmath::p2pX(5, window_size.y));

  sf::Text text(this->IstateData->sd_GameFont_basic, "", 24);

  sf::RectangleShape rectangle;
  rectangle.setFillColor(sf::Color(200, 200, 200, 150));

  int i = 0;
  float i2 = i;
  for (const auto &keybind : *this->IstateData->sd_KeySupports.lock()) {
    text.setString(keybind.first + ": " +
                   std::to_string(static_cast<int>(keybind.second)));

    float posX = mmath::p2pX(12.f * (i % 3), window_size.x);
    float posY = mmath::p2pX(40.f, window_size.y) +
                 mmath::p2pX(3.f * (i2 / 3), window_size.y);
    text.setPosition({posX, posY});

    rectangle.setSize(sf::Vector2f(text.getGlobalBounds().size.x,
                                   text.getGlobalBounds().size.y));
    rectangle.setPosition(text.getPosition());

    _keybindText.push_back(text);
    _keybindBackground.push_back(rectangle);
    i++;
    i2 = i;
  }
}

void SettingsState::initEctPage() {}
void SettingsState::initGameplayPage() {}

void SettingsState::resetGui() { // reser to new resolution, and other settings
                                 // with next saving
  myGFXStruct gfx = this->IstateData->sd_gfxSettings.lock()->getgfxsettings();

  gfx.resolution =
      _video_modes[_selectors["SELEC_VMODE"]->getActiveElementID()];
  gfx.frameRateLimit =
      _gfxResource["GFX_FPS"]
                  [_selectors["SELEC_FPS"].get()->getActiveElementID()];
  gfx.contextSettings.antiAliasingLevel =
      _gfxResource["GFX_ALL"]
                  [_selectors["SELEC_AAL"].get()->getActiveElementID()];
  gfx.fullscreen =
      _gfxResource["GFX_FULLSCREEN"]
                  [_selectors["SELEC_FULLSCREEN"]->getActiveElementID()];
  gfx.verticalSync =
      _gfxResource["GFX_VSYNC"]
                  [_selectors["SELEC_VSYNC"].get()->getActiveElementID()];

  this->IstateData->sd_gfxSettings.lock()->setgfxsettings(gfx);

  // reset window
  if (gfx.fullscreen)
    this->Iwindow.lock()->create(gfx.resolution, gfx.title,
                                 sf::State::Fullscreen, gfx.contextSettings);
  else
    this->Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Windowed,
                                 gfx.contextSettings);
  this->Iwindow.lock()->setFramerateLimit(gfx.frameRateLimit);

  this->IstateData->sd_reserGUI = true;
  this->saveVolumeSettings();
  this->IstateData->sd_gfxSettings.lock()->saveToFile();

  _keybindBackground.clear();
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
  this->initVariables();

  // init fonts
  this->reCaclulateCharacterSize();
  this->initGui();
}

void SettingsState::saveVolumeSettings() { // save volume settings to file
  ParserJson::saveSoundVolumes(IstateData->sd_VolumeCollector.lock().get());
}

void SettingsState::initPageLayout() {}

SettingsState::SettingsState(StateData *state_data)
    : State(state_data), page(settingPage::GRAPHICS),
      pageName("GRAPHICS") { // init variables
  initPageLayout();
  initVariables();
  initFonts();
  initGui();
  initKeybinds();

  Logger::logStatic("End initilization settings state",
                    "SettingsState::SettingsState()", logType::INFO);
}

SettingsState::~SettingsState() {
  Logger::logStatic("SettingsState destructor",
                    "SettingsState::~SettingsState()", logType::INFO);

  // delete selector
  _selectors.clear();

  // clear page buttons
  _pageButtons.clear();

  // clear keybinds
  _keybindText.clear();

  // clear keybind background
  _keybindBackground.clear();

  // clear video modes
  _video_modes.clear();

  // clear gfx resource
  _gfxResource.clear();

  // clear myTest
  _sound_SliderMap.clear();

  // clear text
  _graphic_list.clear();
}

// Functions
void SettingsState::updateInput(const float &delta_time) {
  // if escape is pressed, end state
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(IkeyBinds.at("KEY_BACK"))) &&
      this->getKeytime())
    this->endState();
  // if slash is pressed, swith debug mode
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(IkeyBinds.at("KEY_SLASH"))) &&
      this->getKeytime())
    this->Idebud = !this->Idebud;

  // if key Q is pressed, swith page to left (back)
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(IkeyBinds.at("KEY_BACK_PAGE"))) &&
      this->getKeytime())
    this->page =
        static_cast<settingPage>((static_cast<int>(this->page) - 1 +
                                  static_cast<int>(settingPage::PAGE_COUNT)) %
                                 static_cast<int>(settingPage::PAGE_COUNT));

  // if key E is pressed, swith page to right (forward)
  if (sf::Keyboard::isKeyPressed(
          sf::Keyboard::Scancode(IkeyBinds.at("KEY_FORWARD_PAGE"))) &&
      this->getKeytime())
    this->page =
        static_cast<settingPage>((static_cast<int>(this->page) + 1) %
                                 static_cast<int>(settingPage::PAGE_COUNT));
}

void SettingsState::updateAudioPage(
    const float &delta_time) // Update audio page
{
  for (auto &it : _sound_SliderMap) {
    it.second->update(this->ImousePosView);

    if (it.second->isChangedValue()) {
      IstateData->sd_VolumeCollector.lock()->setCategoryVolume(
          it.first, it.second->getValue());
      this->updateSounds(delta_time);
    }
  }
}

void SettingsState::updateSounds(const float &delta_time) {
  // this->Isound.setVolume(this->IVolumeCollector->getCategoryVolume(SoundCategory::vol_MASTER)
  //    * this->IVolumeCollector->getCategoryVolume(SoundCategory::vol_MUSIC) /
  //    100);
}

void SettingsState::updateGraphicsPage(
    const float &delta_time) // Update graphics page
{
  // update selector
  for (auto &it : _selectors)
    it.second->update(delta_time, this->ImousePosWindow);
}

void SettingsState::updateControlsPage(
    const float &delta_time) // Update controls page
{}

void SettingsState::updateEctPage(const float &delta_time) // Update ect page
{}

void SettingsState::updateGui(const float &delta_time) {
  switch (page) {
  case settingPage::AUDIO:
    this->updateAudioPage(delta_time);
    break;
  case settingPage::GRAPHICS:
    this->updateGraphicsPage(delta_time);
    break;
  case settingPage::CONTROLS:
    this->updateControlsPage(delta_time);
    break;
  case settingPage::GAMEPLAY:
    this->updateEctPage(delta_time);
    break;
  default:
    break;
  }

  // update page buttons
  for (auto &it : _pageButtons)
    it.second->update(this->ImousePosWindow);

  // update current page when page button is pressed
  if (_pageButtons["PGB_GRAPHICS"]->isPressed() && this->getKeytime())
    this->page = settingPage::GRAPHICS;
  if (_pageButtons["PGB_CONTROLS"]->isPressed() && this->getKeytime())
    this->page = settingPage::CONTROLS;
  if (_pageButtons["PGB_AUDIO"]->isPressed() && this->getKeytime())
    this->page = settingPage::AUDIO;
  if (_pageButtons["PGB_GAMEPLAY"]->isPressed() && this->getKeytime())
    this->page = settingPage::GAMEPLAY;

  if (_pageButtons["BACK_BTN"]->isPressed() && this->getKeytime())
    this->endState();
  // apply settings
  if (_pageButtons["APPLY_BTN"]->isPressed() && this->getKeytime())
    this->resetGui();

  // update pageName
  std::map<settingPage, std::string> pageNames = {
      {settingPage::GRAPHICS, helperText::SettingsTexts::TEXT_GRAPHICS},
      {settingPage::CONTROLS, helperText::SettingsTexts::TEXT_CONTROLS},
      {settingPage::AUDIO, helperText::SettingsTexts::TEXT_AUDIO},
      {settingPage::GAMEPLAY, helperText::SettingsTexts::TEXT_GAMEPLAY}

  };

  pageName = pageNames.count(page) ? pageNames[page] : "ERR";

  if (this->Idebud) {
    this->IstringStream
        << "Ver: " << CMAKE_PROJECT_VERSION << "\nFPS:\t" << 1 / delta_time
        << "\nCurrent memory usage:\t"
        << MemoryUsageMonitor::formatMemoryUsage(
               MemoryUsageMonitor::getCurrentMemoryUsage())

        << "\nPage: " << pageName << " " << static_cast<int>(this->page)
        << "\nSliders: "
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
                       SoundCategory::vol_ENVIRONMENT))
        << "\nVideo modes: " << _video_modes.size() << "\nVideo mode: "
        << std::to_string(this->IstateData->sd_gfxSettings.lock()
                              ->_struct.resolution.size.x)
        << std::to_string(this->IstateData->sd_gfxSettings.lock()
                              ->_struct.resolution.size.y)
        << "\nFramerate limit: " +
               std::to_string(this->IstateData->sd_gfxSettings.lock()
                                  ->_struct.frameRateLimit)
        << "\nResolution: " << this->IstateData->sd_Window.lock()->getSize().x
        << "x" << this->IstateData->sd_Window.lock()->getSize().y
        << "\nAntialiasing: "
        << this->IstateData->sd_gfxSettings.lock()
               ->_struct.contextSettings.antiAliasingLevel
        << "\nvSync: "
        << this->IstateData->sd_gfxSettings.lock()->_struct.verticalSync
        << "\nFullscreen: "
        << this->IstateData->sd_gfxSettings.lock()->_struct.fullscreen
        << "\nSize of state: " << sizeof(*this) << " bytes"
        << "\nkeytime: " << this->Ikeytime
        << "\nMouse pos: " << this->ImousePosWindow.x << " "
        << this->ImousePosWindow.y << "\narrays info:"
        << "\n\tvideo_modes: " << _video_modes.size()
        << "\n\tgfxResource: " << _gfxResource.size()
        << "\n\tkeybindText: " << _keybindText.size()
        << "\n\tkeybindBackground: " << _keybindBackground.size()
        << "\n\tpageButtons: " << _pageButtons.size()
        << "\n\tkeybindText: " << _keybindText.size()
        << "\n\tselectors: " << _selectors.size()
        << "\n\tgraphic_list: " << _graphic_list.size()
        << "\n\tsound_SliderMap: " << _sound_SliderMap.size();

    this->Itext.setString(this->IstringStream.str());
    this->IstringStream.str("");
  }
}

void SettingsState::update(const float &delta_time) {
  this->updateMousePositions();
  this->updateKeytime(delta_time);
  this->updateInput(delta_time);
  this->updateGui(delta_time);
}

void SettingsState::renderGui(sf::RenderTarget &target) {
  // render gui elements on some page

  // render page buttons
  for (auto &it : _pageButtons)
    target.draw(*it.second);

  switch (this->page) {
  case settingPage::GRAPHICS:
    // draw text
    for (auto &it : _graphic_list)
      target.draw(it.first);
    // draw selector
    for (auto &it : _selectors)
      it.second->render(target);
    break;
  case settingPage::CONTROLS:
    // draw _text_shapes

    // draw shapes for keybinds like background layer
    // FIXME: fix layering of keybinds
    for (auto &it : _keybindBackground)
      target.draw(it);

    for (const auto &text : _keybindText)
      target.draw(text);
    break;
  case settingPage::AUDIO:
    // TODO add content
    // draw _sound_SliderMap
    for (auto &it : _sound_SliderMap)
      it.second->render(target);

    break;
  case settingPage::GAMEPLAY:
    // TODO add content
    break;
  default:
    break;
  }
}
// Render page layout
void SettingsState::renderPageLayout(sf::RenderTarget &target) {
  // render page layout
  target.draw(_pageBackground);
}

void SettingsState::render(sf::RenderWindow &target) {
  target.draw(this->background);

  this->renderPageLayout(target);
  this->renderGui(target);

  if (this->Idebud)
    target.draw(this->Itext);
}