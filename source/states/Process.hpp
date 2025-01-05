#ifndef CPP_PROCESS_CORESTATE_HPP
#define CPP_PROCESS_CORESTATE_HPP

#include "../Content/ItemsStuff/Inventory.hpp"
#include "../Content/Map/TileMap.hpp"
#include "../GUI/GUISYS.hpp"
#include "../core/header.h"
#include "../entitys/Enemys/slime.hpp"
#include "../entitys/player.hpp"
#include "../math/ProcessGenerationNoice.hpp"
#include "PauseMenu.hpp"
#include "State.hpp"

// The Process class represents the main game state
class Process : public State {
private:
    // View and window variables
    sf::View view;
    sf::View playerView;
    PauseMenu* pausemenu;
    sf::Sprite renderSprite;
    sf::RenderTexture renderTexture;

    // Game elements
    std::shared_ptr<Inventory> t_inventory; // Inventory
    // std::unique_ptr<InventoryHUD> t_inventoryHUD; // Inventory HUD
    std::shared_ptr<Player> player; // Player
    std::shared_ptr<TileMap> mapTiles; // Tile map
    mmath::noiceData noicedata; // Noise data
    std::vector<Entity*> entitys; // Entities
    ProcessGenerationNoice* myGN; // Noise generation
    sf::Shader shader; // Shader

    // GUI
    std::map<std::string, gui::ProgressBar*> playerBar; // Player's progress bar
    gui::MiniMap* minimap; // Minimap

    // Initialization functions that don't use loaded data
    void initKeybinds(); // Initialize key bindings
    void initPauseMenu(); // Initialize pause menu
    void initView(); // Initialize view
    void initTileMap(); // Initialize tile map
    void initTileMapData(); // Initialize tile map data
    void registerItems(); // Register items
    void initPlayer(); // Initialize player
    void initEntitys(); // Initialize entities
    void initMiniMap(); // Initialize minimap

    void intGUI(); // Initialize GUI

    const bool loadGameData(); // Load game data
    const bool saveGameData(); // Save game data

public:
    Process(StateData* state_data, const bool defaultLoad); // Constructor
    virtual ~Process(); // Destructor

    // Update functions
    void updateTileMap(const float& delta_time); // Update tile map
    void updateEntitys(const float& delta_time); // Update entities
    void updateInput(const float& delta_time); // Update input
    void updatePlayerInputs(const float& delta_time); // Update player inputs
    void updateGUI(const float& delta_time); // Update GUI
    void updateDebug(const float& delta_time); // Update debug
    void updateSounds(const float& delta_time); // Update sounds
    void update(const float& delta_time); // Update state

    // Render functions
    void renderPlayer(sf::RenderTarget& target); // Render player
    void renderGUI(sf::RenderTarget& target); // Render GUI
    void renderTileMap(sf::RenderTarget& target); // Render tile map
    void renderEntities(sf::RenderTarget& target); // Render entities
    // Main render function
    void render(sf::RenderWindow& target);
};
#endif