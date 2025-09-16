#ifndef MAINMENU
#define MAINMENU

#include "EditorState.hpp"
#include "Process.hpp"
#include "State.hpp"
#include "settings.hpp"

#include "../GUI/components/button.hpp"

// The MainMenu class represents the game's main menu
class MainMenu : public State {
private:
  // Render components
  sf::View view;
  sf::RenderTexture renderTexture;
  sf::Sprite renderSprite;

  // Menu buttons
  std::map<std::string, std::unique_ptr<gui::Button>> buttons;

  // Background textures and shapes
  std::vector<sf::Texture> background_textures;
  std::vector<sf::RectangleShape> backgrond_shapes;

  // Initialization methods
  void initRenderDefines(); // Initialize render settings
  void initKeybinds();      // Initialize key bindings
  void initButtons();       // Initialize buttons
  void initBackground();    // Initialize background
  void initGUI();           // Initialize GUI
  void resetGUI();          // Reset GUI
  void initSounds();        // Initialize sounds

  // Elements for start
  void resetView(); // Reset view

public:
  MainMenu(StateData *sDate); // Constructor
  virtual ~MainMenu();        // Destructor

  // Update methods
  void updateInput(const float &delta_time);  // Update input
  void updateButtons();                       // Update buttons
  void updateSounds(const float &delta_time); // Update sounds
  void updateGUI(const float &delta_time);    // Update GUI
  void update(const float &delta_time);       // Update state
  void render(sf::RenderWindow &target);      // Render

  virtual size_t getMemoryUsage() const { return sizeof(*this); }
};
#endif /* MAINMENU */
