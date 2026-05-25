#ifndef STATE
#define STATE

#include "../core/header.h"

#include "../core/dataCollector/_keybind_enum.h"
#include "../core/dataCollector/_man_Volume.hpp"
#include "../core/dataCollector/_man_graphics.hpp"
#include "../core/math/mymath.hpp"

// Forward declaration of State class
class State;

// Class for state data
// This class holds data that is shared across different states
class StateData {
public:
  // Constructor initializes all pointers to nullptr
	StateData() {
		sd_States = nullptr;
		sd_reserGUI = false;
		sd_gridSize = 0;
		sd_characterSize_debug = 0;
		sd_characterSize_game_big = 0;
		sd_characterSize_game_medium = 0;
		sd_characterSize_game_small = 0;
	}

	float sd_gridSize;                         // Size of the grid
	std::weak_ptr<sf::RenderWindow> sd_Window; // Pointer to the SFML window
	// Font used in the game
	sf::Font sd_GameFont_basic;
	sf::Font sd_debugFont; // Font used for debugging
	// Pointer to the graphics settings
	std::weak_ptr<gfx::myGFXStruct> sd_gfxSettings;
	// pointer to volume manager
	std::weak_ptr<gfx::VolumeCollector> sd_VolumeCollector;
	std::weak_ptr<std::map<std::string, sf::Sound>> sd_SoundMap;
	std::weak_ptr<std::map<std::string, sf::Sound>> sd_SoundBufferMap;
	// KeyMap and KeyBinds
	std::weak_ptr<std::map<std::string, uint16_t>> sd_KeySupports;
	// pointer to keyboard
	// std::weak_ptr<keyboardOSX> sd_keyboard_prt;
	// Character size for text's
	unsigned int sd_characterSize_debug;
	unsigned int sd_characterSize_game_big;
	unsigned int sd_characterSize_game_medium;
	unsigned int sd_characterSize_game_small;
	// Flag to reset GUI
	bool sd_reserGUI;

	// Stack of states
	std::stack<State*>* sd_States;
};

// Abstract class for game states
class State {
private:
protected:
  // Variables
	StateData* IstateData;                   // Pointer to shared state data
	std::stack<State*>* Istates;            // Stack of states
	std::weak_ptr<sf::RenderWindow> Iwindow; // Weak pointer to the SFML window
	// Map of Binds keys
	std::weak_ptr<std::map<std::string, uint16_t>> IKeySupports;
	//   std::weak_ptr<keyboardOSX> IKeyboard; // Pointer to keyboard

	// Resources
	bool Iquit;        // Flag to quit the state
	bool Ipaused;      // Flag to pause the state
	float Ikeytime;    // Time since last key press
	float IkeytimeMax; // Maximum time between key presses
	float IgridSize;   // Size of the grid

	sf::Vector2i ImousePosScreen;
	sf::Vector2i ImousePosWindow;
	sf::Vector2f ImousePosView;
	sf::Vector2i ImousePosGrid;

	std::stringstream IstringStream; // Stream for debug string
	sf::Text Itext;                  // Debug text
	bool Idebud;                     // Flag for debug mode into game

	// Sounds and him elements for game (volume, sound, buffer, ect )
	// shared map with sounds and name itself
	std::map<std::string, sf::Sound> IsoundsMap;

	// Map of sound buffers, one key one sound
	std::unordered_map<gfx::SoundCategory, std::map<std::string, sf::SoundBuffer>> IsoundBufferMap;

	void initBuffer();               // Initialize buffer
	void reCaclulateCharacterSize(); // Recalculate character size

	// Functions for sounds key
	// for calling sf::Sound from map using category layer
	virtual bool loadSoundtoBuffer(gfx::SoundCategory _soundcategory, std::filesystem::path, std::string _typename);

   // void playSound(gfx::SoundCategory _soundcategory, std::string _typename); // Play sound from category[_typename]

	// functions accses
	void setVolume(gfx::SoundCategory _category, const float _newVal) // Set volume for all categories
	{
		IstateData->sd_VolumeCollector.lock()->setCategoryVolume(_category, _newVal);
		for (auto& it : IsoundsMap)
			it.second.setVolume(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(_category));
	}

public:
  // Constructor
	State(StateData* state_data);
	// Destructor
	virtual ~State();

	// Accessors
	const bool& getQuit() const { return this->Iquit; } // Get quit flag
	const bool getKeytime();                            // Get key time

	// Functions
	void endState() { this->Iquit = true; }        // End the state
	void pauseState() { this->Ipaused = true; }    // Pause the state
	void unpauseState() { this->Ipaused = false; } // Unpause the state

	// update sounds (virtual function)
	virtual void updateSounds(const float& delta_time) = 0;
	// Update mouse positions (virtual function)
	virtual void updateMousePositions(sf::View* view = NULL);
	// Update key time (virtual function)
	virtual void updateKeytime(const float& delta_time);
	// Update input (pure virtual function)
	virtual void updateInput(const float& delta_time) = 0;
	// Update the state (pure virtual function)
	virtual void update(const float& delta_time) = 0;
	// Render the state (pure virtual function)
	virtual void render(sf::RenderWindow& target) = 0;
};
#endif /* STATE */
