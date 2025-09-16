#ifndef CPP_STATE_NOICEVIEW_HPP
#define CPP_STATE_NOICEVIEW_HPP

#include "../math/LSystem.hpp"

#include "State.hpp"

#include "editModes/NoiceViewer.hpp"

#include "../Content/Map/TileMap.hpp"
#include "../GUI/components/button.hpp"
#include "../GUI/components/selector.hpp"
#include "../GUI/components/staticSelector.hpp"

// The EditorState class represents the state of the game editor
class EditorState : public State {
private:
  // Variables
  NoiceViewer *m_NoiceViewer;         // Noise viewer
  mmath::noiceData m_noiceData;       // Noise data
  std::unique_ptr<TileMap> m_tileMap; // tile map

  // trees
  LSystem *myLS; // L-system for generating trees

  // GUI elements (buttons, selectors, etc)
  bool showTabmenu; // Flag to show or hide the tab menu
  std::map<std::string, gui::Button *> buttons; // Map of buttons
  sf::RectangleShape tabShape;                  // Shape of the tab
  // Map of static selectors
  std::map<std::string, gui::StaticSelector *> staticSelector;
  gui::Selector *selector; // Current selector

  int current_View_Generator = 1; // Current view generator

  // Initialization functions
  void initKeybinds();  // Initialize key bindings
  void initButtons();   // Initialize buttons
  void initSelectors(); // Initialize selectors
  void initTabMenu();   // Initialize tab menu
  void initNoice();     // Initialize noise
  void initDebugText(); // Initialize debug text

  // Update functions
  void saveTreeAsImage(sf::RenderWindow &window); // Save tree as image
  sf::IntRect findNonTransparentRect(
      const sf::Image &image); // Find non-transparent rectangle in an image

  void updateInput(const float &delta_time);     // Update input
  void updateButtons(const float &delta_time);   // Update buttons
  void updateDebugText(const float &delta_time); // Update debug text
  void updateSounds(const float &delta_time);    // Update sounds

  // Render functions
  void renderTabMenu(sf::RenderTarget &target); // Render tab menu

public:
  EditorState(StateData *statedata); // Constructor
  virtual ~EditorState();            // Destructor

  void update(const float &delta_time);  // Update state
  void render(sf::RenderWindow &target); // Render state

  virtual size_t getMemoryUsage() const { return sizeof(*this); }
};
#endif