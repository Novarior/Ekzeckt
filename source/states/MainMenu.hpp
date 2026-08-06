#ifndef MAINMENU
#define MAINMENU

#include "State.hpp"

#include "EditorState.hpp"
#include "Process.hpp"
#include "settings.hpp"

#include "../core/cmakever.h"
#include "../core/math/models fractal/SpiralModel.hpp"

#include "../localisation/helperText.hpp"

#include "../GUI/GUI_Component.hpp"
#include "../GUI/components/button.hpp"


// The MainMenu class represents the game's main menu
class MainMenu: public State {
private:
	// Background textures and shapes
	std::vector<sf::Texture> background_textures;
	std::vector<sf::RectangleShape> backgrond_shapes;
	std::unique_ptr<SpiralModel> sModel;
	ModelData sData;

	// Initialization methods
	void initButtons();  // Initialize buttons
	void initBackground(); // Initialize background
	void initGUI();    // Initialize GUI

	void initBackgroundSpiral();
	void initSounds();   // Initialize sounds

	// Elements for start

public:
	MainMenu(StateData* sDate); // Constructor
	virtual ~MainMenu();    // Destructor

	void updateDebugTextState(const float& delta_time) override;

	void resetGUI() override;    // Reset GUI

	// Update methods
	void update(const float& delta_time);    // Update state
	void updateInput(const float& delta_time); // Update input
	void updateSounds(const float& delta_time); // Update sounds
	void updateButtons();            // Update buttons

	void updateGUI(const float& delta_time);  // Update GUI
	void render(sf::RenderWindow& target);   // Render

	//virtual size_t getMemoryUsage() const { return sizeof(*this); }
};
#endif /* MAINMENU */
