#include "State.hpp"
#include "../math/mymath.hpp"
#include "../source/mypars/parsJSON.hpp"

/**
 * @brief Construct a new State:: State object
 *
 * @param state_data
 */
State::State(StateData *state_data)
    : IstateData(state_data), Itext(IstateData->sd_debugFont, "",
                                    IstateData->sd_characterSize_game_medium) {
  // write log message what im here doing something
  Logger::logStatic("Start initilization state", "State::State()");

  // init variabless from state_data to curent state

  Iwindow = state_data->sd_Window;
  Istates = state_data->sd_States;
  Iquit = false;
  Ipaused = false;
  Ikeytime = 0.f;
  IkeytimeMax = 0.3f;
  IgridSize = state_data->sd_gridSize;
  // get access to volume manager from global state data like a shared pointer

  IstringStream.str("");
  Idebud = __MDEBUG__;

  Itext.setOutlineThickness(1);
  Itext.setOutlineColor(sf::Color::Black);

  Logger::logStatic("End initilization state", "State::State()");
  this->initBuffer();
}

State::~State() { Logger::logStatic("destroy state", "State::~State()"); }

// Accessors
const bool State::getKeytime() {
  if (Ikeytime >= IkeytimeMax) {
    Ikeytime = 0.f;
    return true;
  }
  return false;
}

// create shared maps with sounds and categoty, buffers and categoty
void State::initBuffer() {
  this->IsoundsMap = std::map<std::string, sf::Sound>();
  this->IsoundBufferMap =
      std::unordered_map<SoundCategory,
                         std::map<std::string, sf::SoundBuffer>>();
}

// load sound to buffer
bool State::loadSoundtoBuffer(SoundCategory _soundcategory,
                              std::string _namepath, std::string _typename) {
  sf::SoundBuffer buffer;
  if (!buffer.loadFromFile(
          std::string(ApplicationsFunctions::get_resources_dir()) +
          _namepath)) {
    Logger::logStatic("Failed to load sound buffer",
                      "State::loadSoundtoBuffer()");
    return false;
  }

  this->IsoundBufferMap[_soundcategory][_typename] = buffer;
  return true;
}

void State::updateKeytime(const float &delta_time) {
  if (Ikeytime < IkeytimeMax)
    Ikeytime += delta_time;
}

void State::reCaclulateCharacterSize() {
  IstateData->sd_characterSize_debug =
      mmath::calcCharSize(Iwindow.lock()->getSize(), 150);
  IstateData->sd_characterSize_game_big =
      mmath::calcCharSize(Iwindow.lock()->getSize(), 75);
  IstateData->sd_characterSize_game_medium =
      mmath::calcCharSize(Iwindow.lock()->getSize(), 85);
  IstateData->sd_characterSize_game_small =
      mmath::calcCharSize(Iwindow.lock()->getSize(), 95);
}

void State::updateMousePositions(sf::View *view) {

  ImousePosScreen = sf::Mouse::getPosition();
  ImousePosWindow = sf::Mouse::getPosition(*Iwindow.lock());

  if (view)
    Iwindow.lock()->setView(*view);

  ImousePosView =
      Iwindow.lock()->mapPixelToCoords(sf::Mouse::getPosition(*Iwindow.lock()));
  ImousePosGrid = sf::Vector2i(
      static_cast<int>(ImousePosView.x) / static_cast<int>(IgridSize),
      static_cast<int>(ImousePosView.y) / static_cast<int>(IgridSize));

  Iwindow.lock()->setView(Iwindow.lock()->getDefaultView());
}
