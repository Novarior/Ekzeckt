#ifndef CPP_STATE_NOICEVIEW_HPP
#define CPP_STATE_NOICEVIEW_HPP

#include "State.hpp"

#include "editModes/NoiceViewer.hpp"

#include "../core/math/models fractal/LSystem.hpp"
#include "../core/math/models fractal/SpiralModel.hpp"

#include "../Content/Map/TileMap.hpp"

#include "../GUI/GUI_Component.hpp"
#include "../GUI/components/button.hpp"
#include "../GUI/components/selector.hpp"
#include "../GUI/components/staticSelector.hpp"
#include "../GUI/components/slider.hpp"


enum cViewGen {
	vNoice = 0,
	vLSystem,
	vSpiral,
	vAll,
	vCount
};
// The EditorState class represents the state of the game editor
class EditorState: public State {
private:
	std::array<std::string, 4> strCurrentViewGen;
	// Variables
	NoiceViewer* m_NoiceViewer;     // Noise viewer
	NoiceData* m_noiceData;    // Noise data
	std::unique_ptr<TileMap> m_tileMap; // tile map

	// trees
	LSystem* myLS; // L-system for generating trees
	SpiralModel* spiralModel;
	ModelData spiralData;

	// GUI elements (buttons, selectors, etc)
	bool showTabmenu;               // Flag to show or hide the tab menu
	sf::RectangleShape tabShape;         // Shape of the tab
	// Map of static selectors

	std::vector<std::map<std::string, gui::SliderFloat*>> staticSelector;
	std::vector<std::map<std::string, gui::SliderUInt*>> staticSelectorUInt;
	gui::Selector* selector; // Current selector

	int current_View_Generator = cViewGen::vSpiral; // Current view generator

	// Initialization functions
	void initGUI();			// init all GUI layout
	void initButtons();		// Initialize buttons
	void initSelectors();	// Initialize selectors
	void initTabMenu();		// Initialize tab menu

	void initNoice();		// Initialize noise
	void initMathMoodels();
	void initSpiralMathModel();
	void initLSystemMathModel();

	void initDebugText();	// Initialize debug text

	// Update functions
	void saveTreeAsImage(sf::RenderWindow& window);       // Save tree as image
	sf::IntRect findNonTransparentRect(const sf::Image& image); // Find non-transparent rectangle in an image
	virtual size_t getMemoryUsage() const { return sizeof(*this); }

public:
	EditorState(StateData* statedata); // Constructor
	virtual ~EditorState();      // Destructor

	void updateDebugTextState(const float& delta_time) override;

	void resetGUI() override;

	void update(const float& delta_time);			// Update state
	void updateInput(const float& delta_time);	// Update input
	void updateButtons(const float& delta_time);					// Update buttons
	void updateSounds(const float& delta_time);						// Update sounds

	// Render functions
	void renderTabMenu(sf::RenderTarget& target);	// Render tab menu
	void render(sf::RenderWindow& target);			// Render state
};
#endif