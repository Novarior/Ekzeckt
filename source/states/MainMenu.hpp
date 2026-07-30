#ifndef MAINMENU
#define MAINMENU

#include "State.hpp"

#include "EditorState.hpp"
#include "Process.hpp"
#include "settings.hpp"

#include "../core/cmakever.h"
#include "../core/tools/staticFPSMetter.hpp"

#include "../localisation/helperText.hpp"

#include "../GUI/GUI_Component.hpp"
#include "../GUI/components/button.hpp"


// The MainMenu class represents the game's main menu
class MainMenu: public State {
private:
	// Background textures and shapes
	std::vector<sf::Texture> background_textures;
	std::vector<sf::RectangleShape> backgrond_shapes;

	// Initialization methods
	void initButtons();    // Initialize buttons
	void initBackground(); // Initialize background
	void initGUI();        // Initialize GUI
	void resetGUI();       // Reset GUI
	void initSounds();     // Initialize sounds

	// Elements for start

public:
	MainMenu(StateData* sDate); // Constructor
	virtual ~MainMenu();        // Destructor

	// Update methods
	void updateInput(const float& delta_time);  // Update input
	void updateButtons();                       // Update buttons
	void updateSounds(const float& delta_time); // Update sounds
	void updateGUI(const float& delta_time);    // Update GUI
	void update(const float& delta_time);       // Update state
	void render(sf::RenderWindow& target);      // Render

	//virtual size_t getMemoryUsage() const { return sizeof(*this); }
};
#endif /* MAINMENU */
