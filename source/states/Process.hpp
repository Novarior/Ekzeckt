#ifndef PROCESS
#define PROCESS

#include "PauseMenu.hpp"
#include "State.hpp"

#include "../core/math/models noice/Noice_PGN.hpp"

#include "../GUI/GUI_Component.hpp"
#include "../GUI/components/progressBar.hpp"
#include "../GUI/UI/inventoryGUI.hpp"
#include "../GUI/UI/minimap.hpp"

#include "../entitys/player.hpp"
#include "../Content/Map/TileMap.hpp"

// The Process class represents the main game state
class Process: public State {
private:
	// View and window variables
	sf::View view;
	sf::View playerView;
	std::unique_ptr<PauseMenu> pausemenu;
	sf::Sprite renderSprite;
	sf::RenderTexture renderTexture;

	// Game elements
	Player* player;					// Player
	TileMap* mapTiles;				// Tile map
	NoiceData* noicedata;							// Noise data
	std::vector<Entity*> entitys;					// Entities
	ProcessGenerationNoice* myGN;	// Noise generation
	sf::Shader shader;								// Shader

	// GUI
	gui::InventoryGUI* inventoryGUI;		// GUI inventory
	std::map<std::string, std::unique_ptr<gui::ProgressBar>> playerBar;		// GUI Player's progress bar
	std::unique_ptr<gui::MiniMap> minimap;					// GUI Minimap

	// Initialization functions 
	void initView();         // Initialize view
	void initTileMap();      // Initialize tile map
	void initTileMapData();  // Initialize tile map data
	void registerItems();    // Register items
	void initPlayer();       // Initialize player
	void initEntitys();      // Initialize entities

	// GUI INITS
	void intGUI();								// Initialize GUI
	void initPauseMenu(sf::Vector2f res);		// Initialize pause menu
	void initGUIInventory(sf::Vector2f res);	// Initialize Inventory GUI
	void initMiniMap(sf::Vector2f res);			// Initialize minimap
	void initGUIBars(sf::Vector2f res);			// Initialize GUI bars

	const bool loadGameData(); // Load game data
	const bool saveGameData(); // Save game data

public:
	Process(StateData* state_data, const bool defaultLoad); // Constructor
	virtual ~Process();                                     // Destructor

	// Update functions
	void updateTileMap(const float& delta_time);      // Update tile map
	void updateEntitys(const float& delta_time);      // Update entities
	void updateInput(const float& delta_time);        // Update input
	void updatePlayerInputs(const float& delta_time); // Update player inputs
	void updateGUI(const float& delta_time);          // Update GUI
	void updateDebug(const float& delta_time);        // Update debug
	void updateSounds(const float& delta_time);       // Update sounds
	void update(const float& delta_time);             // Update state

	// Render functions
	void renderPlayer(sf::RenderTarget& target);   // Render player
	void renderGUI(sf::RenderTarget& target);      // Render GUI
	void renderTileMap(sf::RenderTarget& target);  // Render tile map
	void renderEntities(sf::RenderTarget& target); // Render entities
	// Main render function
	void render(sf::RenderWindow& target);
};
#endif /* PROCESS */