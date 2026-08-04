#ifndef STATE
#define STATE

#include "../core/header.h"
#include "../core/math/mymath.hpp"
#include "../core/cmakever.h"
#include "../core/tools/appfn_memory.hpp"
#include "../core/tools/appfn_fpsClock.hpp"

#include "../core/dataCollector/_keybind_enum.h"
#include "../core/dataCollector/_man_Volume.hpp"
#include "../core/dataCollector/_man_graphics.hpp"
#include "../core/dataCollector/_man_Texture.hpp"
#include "../core/dataCollector/_man_Fonts.hpp"

#include "../GUI/GUI_Component.hpp"

// Forward declaration of State class
class State;

// Class for state data
// This class holds data that is shared across different states
class StateData {
public:
	StateData() {
		sd_States = nullptr;
		sd_reserGUI = false;
		sd_gridSize = 0;
		sd_characterSize_debug = 0;
		sd_characterSize_game_big = 0;
		sd_characterSize_game_medium = 0;
		sd_characterSize_game_small = 0;
	}

	std::weak_ptr<sf::RenderWindow> sd_Window;
	std::weak_ptr<gfx::myGFXStruct> sd_gfxSettings;
	std::weak_ptr<gfx::VolumeCollector> sd_VolumeCollector;
	std::weak_ptr<std::map<std::string, sf::Sound>> sd_SoundMap;
	std::weak_ptr<std::map<std::string, sf::Sound>> sd_SoundBufferMap;
	std::weak_ptr<std::map<std::string, uint16_t>> sd_KeySupports;

	unsigned int sd_characterSize_debug;
	unsigned int sd_characterSize_game_big;
	unsigned int sd_characterSize_game_medium;
	unsigned int sd_characterSize_game_small;
	float sd_gridSize;
	bool sd_reserGUI;

	std::stack<State*>* sd_States;
};

// Abstract class for game states
class State {
private:
protected:
	// Variables
	StateData* IstateData;						// Pointer to shared state data
	std::stack<State*>* Istates;				// Stack of states
	std::weak_ptr<sf::RenderWindow> Iwindow;	// Weak pointer to the SFML window
	sf::View view;
	sf::RenderTexture IRenderTexture;
	sf::Sprite IRenderSprite;
	std::weak_ptr<std::map<std::string, uint16_t>> IKeySupports;			// Map of Binds keys
	std::map<std::string, std::unique_ptr<gui::GuiComponent>> IGUILayout;	// map of GUI

	// Resources
	bool Iquit;			// Flag to quit the state
	bool Ipaused;		// Flag to pause the state
	bool Idebud;		// Flag for debug mode into game
	float Ikeytime;		// Time since last key press
	float IkeytimeMax;	// Maximum time between key presses
	float IgridSize;	// Size of the grid

	sf::Vector2i ImousePosScreen;
	sf::Vector2i ImousePosWindow;
	sf::Vector2f ImousePosView;
	sf::Vector2i ImousePosGrid;

	std::stringstream IstringStream; // Stream for debug string
	sf::Text Itext;         // Debug text

	// Sounds and him elements for game (volume, sound, buffer, ect )
	std::map<std::string, sf::Sound> IsoundsMap; // shared map with sounds and name itself
	std::unordered_map<gfx::SoundCategory, std::map<std::string, sf::SoundBuffer>> IsoundBufferMap;// Map of sound buffers, one key one sound

	void initBuffer();					// Initialize buffer
	void reCaclulateCharacterSize();	// Recalculate character size
	void initRenderDefines();
	void resetView();

	virtual bool loadSoundtoBuffer(gfx::SoundCategory _soundcategory, std::filesystem::path, std::string _typename);

	// void playSound(gfx::SoundCategory _soundcategory, std::string _typename); // Play sound from category[_typename]

	// functions accses
	void setVolume(gfx::SoundCategory _category, const float _newVal); // Set volume for all categories

public:
	State(StateData* state_data);	// Constructor
	virtual ~State();				// Destructor

	virtual void resetGUI() = 0;

	// Accessors
	const bool& getQuit() const { return Iquit; }	// Get quit flag
	const bool getKeytime();						// Get key time

	void updateDebugTextBase(const float& delta_time);
	virtual void updateDebugTextState(const float& delta_time) = 0;
	void updateDebugText();

	// Functions
	void endState() { Iquit = true; }    // End the state
	void pauseState() { Ipaused = true; }  // Pause the state
	void unpauseState() { Ipaused = false; } // Unpause the state
	void wasUpdateWindow() { IstateData->sd_reserGUI = true; }

	virtual void updateSounds(const float& delta_time) = 0;						// update sounds (virtual function)
	virtual void updateMousePositions(sf::View* view = NULL);					// Update mouse positions (virtual function)
	virtual void updateKeytime(const float& delta_time);						// Update key time (virtual function)
	virtual void updateInput(const float& delta_time) = 0;	// Update input (pure virtual function)

	virtual void update(const float& delta_time) = 0;			// Update the state (pure virtual function)
	virtual void render(sf::RenderWindow& target) = 0;							// Render the state (pure virtual function)
};
#endif /* STATE */
