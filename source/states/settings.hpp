#ifndef SETTINGS
#define SETTINGS

#include "../localisation/helperText.hpp"
#include "State.hpp"

#include "../GUI/components/button.hpp"
#include "../GUI/components/selector.hpp"
#include "../GUI/components/slider.hpp"

/// @brief  Class for the settings state
/// @note   Inherited from the State class
/// @retval None
class SettingsState : public State {
private:
  enum settingPage { AUDIO, GRAPHICS, CONTROLS, GAMEPLAY, ECTPAGE, PAGE_COUNT };
  // Variables
  sf::Texture backgroundTexture; // Texture for the background
  sf::RectangleShape background; // Shape for the background
  sf::Font font;                 // Font used in the settings state
  std::map<std::string, std::unique_ptr<gui::Button>>
      _pageButtons;     // Map of buttons, used for change current settings page
  std::string pageName; // Name of the current page

  // resources for page layout
  std::vector<sf::Text> _pageText;    // List of page texts
  sf::RectangleShape _pageBackground; // List of page backgrounds

  // Resources for GraphicsSettings
  std::vector<sf::VideoMode> _video_modes; // List of video modes
  std::map<std::string, std::vector<int>>
      _gfxResource; // Map case for Resolutions, FPS, Antialiasing, VSync,
                    // Fullscreen
  std::vector<std::pair<sf::Text, sf::RectangleShape>>
      _graphic_list; // List of graphics texts

  // Resources for Keybinds
  std::vector<sf::Text> _keybindText; // List of keybind texts
  std::vector<sf::RectangleShape>
      _keybindBackground; // List of keybind backgrounds

  // Resources for AudioSettings
  std::map<SoundCategory, std::unique_ptr<gui::SliderInt>>
      _sound_SliderMap; // Map case for Master, Music, Sound, Ambient, Voice

  // Gui selectors
  std::map<std::string, std::unique_ptr<gui::Selector>>
      _selectors; // Map of selectors

  settingPage page; // Current page of settings

  // Initializer functions
  void initVariables();  // Initialize variables
  void initFonts();      // Initialize fonts
  void initKeybinds();   // Initialize key bindings
  void initGui();        // Initialize GUI
  void initPageLayout(); // Initialize page layout
  void resetGui();       // Reset GUI

  // init categories settings
  void initButtons();
  void initGraphicsPage();
  void initSounsPage();
  void initGameplayPage();
  void initKeyboardPage();
  void initEctPage();

  void saveVolumeSettings(); // Save volume settings

public:
  /// @brief Constructor for SettingsState
  /// @param state_data
  SettingsState(StateData *state_data);
  virtual ~SettingsState();

  // Functions
  void updateSounds(const float &delta_time); // Update sounds

  void updateAudioPage(const float &delta_time);    // Update audio page
  void updateGraphicsPage(const float &delta_time); // Update graphics page
  void updateControlsPage(const float &delta_time); // Update controls page
  void updateEctPage(const float &delta_time);      // Update ect page

  void updateInput(const float &delta_time); // Update input
  void updateGui(const float &delta_time);   // Update GUI
  void update(const float &delta_time);      // Update the state

  void renderPageLayout(sf::RenderTarget &target); // Render page layout
  void renderGui(sf::RenderTarget &target);        // Render the GUI
  void render(sf::RenderWindow &target);           // Render the state

  virtual size_t getMemoryUsage() const { return sizeof(*this); }
};

#endif /* SETTINGS */
