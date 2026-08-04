#include "Process.hpp"

#include "../Content/ItemsStuff/ItemEntity/entity_item.hpp"
#include "../Content/ItemsStuff/Items/all_items.hpp"
#include "../entitys/Enemys/slime.hpp"
#include "../localisation/helperText.hpp"

std::map<int, std::shared_ptr<Item>> ItemRegistry::items = {};

const bool Process::loadGameData() {
	// load noice config
	// if (ParserJson::loadNoiceData( noicedata))
	//  printf("LERROR::PROCESS::LOAD::NOICEDATA::COULD_NOT_LOAD\n  %s\n",
	//     AppFiles::config_noicedata);
	// else {
	//  noicedata.mapSizeX = 1000;
	//  noicedata.mapSizeY = 1000;
	//  noicedata.RenderWindowX =
	//    IstateData->sd_gfxSettings.lock()->resolution.size.x;
	//  noicedata.RenderWindowY =
	//    IstateData->sd_gfxSettings.lock()->resolution.size.y;
	//  noicedata.gridSize = IstateData->sd_gridSize;
	// }
	return true;
}

const bool Process::saveGameData() {
	// save player to JSON file
	// if (ParserJson::savePlayer( player.get()))
	//  Logger::logStatic("Parser::savePlayer()::LERROR::",
	//           "Process::saveGameData()", logType::LERROR);
	// // save inventory to JSON file
	// // if (ParserJson::saveInventory(t_inventory))
	// //  Logger::logStatic("Parser::saveInventory()::LERROR::",
	// //           "Process::saveGameData()", logType::LERROR);
	// // save entitys pos and other data
	// if (ParserJson::saveEntitys( entitys))
	//  Logger::logStatic("Parser::saveEntitys()::LERROR::",
	//           "Process::saveGameData()", logType::LERROR);

	return true;
}


void Process::initTileMapData() { // Defauld Init Data
	noicedata = new NoiceData();

	noicedata->mapSizeX = 620;
	noicedata->mapSizeY = 430;
	noicedata->seed = std::time(0);
	noicedata->offsetSeed = 0;
	noicedata->gridSize = IstateData->sd_gridSize;
	noicedata->octaves = 9;
	noicedata->frequency = 8;
	noicedata->persistence = 0.6f;
	noicedata->amplifire = 0.7f;
	noicedata->fastMode = 1;
	noicedata->smoothMode = 1;
	noicedata->RenderWindowX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	noicedata->RenderWindowY = IstateData->sd_gfxSettings.lock()->resolution.size.y;
}


void Process::initTileMap() {
	myGN = new ProcessGenerationNoice(noicedata);
	mapTiles = new TileMap(noicedata, myGN);
}

void Process::intGUI() { // init GUI
	const sf::Vector2f res = {(float)IstateData->sd_gfxSettings.lock()->resolution.size.x,
							(float)IstateData->sd_gfxSettings.lock()->resolution.size.y};

	noicedata->RenderWindowX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	noicedata->RenderWindowY = IstateData->sd_gfxSettings.lock()->resolution.size.y;

	initPauseMenu(res);
	initMiniMap(res);
	initGUIInventory(res);
	initGUIBars(res);
}

void Process::initPauseMenu(sf::Vector2f res) {
	auto charsize = mmath::calcCharSize(res.x, res.y);
	auto& font = *FontManager::getFont(FontID::FONT_GAMEF_01);

	pausemenu = std::make_unique<PauseMenu>(res, font, helperText::GamePlayText::TEXT_PAUSE);
	pausemenu->addButton(75.f, {13.f,6.f}, charsize, "EXIT_BUTTON", helperText::Button::BUTTON_EXIT);
	pausemenu->addButton(20.f, {75.f,6.f}, charsize, "GEN", helperText::Button::BUTTON_PM_GENERATE);
}


void Process::initGUIInventory(sf::Vector2f res) {	// create GUI for inventory
	auto& font = *FontManager::getFont(FontID::FONT_GAMEF_01);

	inventoryGUI = new gui::InventoryGUI(res, font, player->e_getInventory());
	//player->e_getInventory(), // get player inventory for watch for him
	//sf::Vector2f(res),
	//IstateData->sd_GameFont_basic, 64.0f,
	//IstateData->sd_characterSize_game_small);

	appfn::Logger::logStatic("Inventory GUI initialized", "Process::initInventoryGUI()");
}

void Process::initMiniMap(sf::Vector2f res) { // init minimap
	sf::IntRect worldBounds({0, 0}, mapTiles->getMapSizeOnInt());
	minimap = std::make_unique<gui::MiniMap>(
		sf::Vector2f(mmath::p2pX(75.f, res.x), mmath::p2pX(10.f, res.y)),
		sf::Vector2f(mmath::p2pX(20.f, res.x), mmath::p2pX(20.f, res.y)), worldBounds);

	minimap->setImage(mapTiles->getMinimapImage());
}

void Process::initGUIBars(sf::Vector2f res) {
	auto& font = *FontManager::getFont(FontID::FONT_GAMEF_01);

	// init player HP bar on top right on screen math position using mmath::p2pX/X
	playerBar["HP_BAR"] = std::make_unique<gui::ProgressBar>(
		sf::Vector2f(mmath::p2pX(75.f, res.x), mmath::p2pX(3.f, res.y)), sf::Vector2f(mmath::p2pX(20.f, res.x), mmath::p2pX(3.f, res.y)),
		IstateData->sd_characterSize_game_small, font, helperText::GamePlayText::TEXT_BAR_HP);

	playerBar["MP_BAR"] = std::make_unique<gui::ProgressBar>(
		sf::Vector2f(mmath::p2pX(75.f, res.x), mmath::p2pX(7.f, res.y)), sf::Vector2f(mmath::p2pX(20.f, res.x), mmath::p2pX(3.f, res.y)),
		IstateData->sd_characterSize_game_small, font, helperText::GamePlayText::TEXT_BAR_MP);
}

void Process::initView() {
	sf::Vector2f halfSize = sf::Vector2f(static_cast<float>(IstateData->sd_Window.lock()->getSize().x) / 2.f, static_cast<float>(IstateData->sd_Window.lock()->getSize().y) / 2.f);

	view.setSize(halfSize);
	view.setCenter(halfSize);
	playerView.setSize(halfSize);
	playerView.setCenter(halfSize);

	if (!renderTexture.resize({IstateData->sd_Window.lock()->getSize().x, IstateData->sd_Window.lock()->getSize().y}))
		sf::RenderTexture _buffRenderTexture({IstateData->sd_Window.lock()->getSize().x, IstateData->sd_Window.lock()->getSize().y});

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(
		{0, 0}, sf::Vector2i(IstateData->sd_Window.lock()->getSize().x,
		IstateData->sd_Window.lock()->getSize().y)));
}

void Process::initPlayer() {
	// get array with posible spawn positions
	std::vector<sf::Vector2f> spawnPosArray = mapTiles->getSpawnPosArray();
	// set player position to random position getting from spawnPosArray
	player = new Player(spawnPosArray[rand() % spawnPosArray.size()]);

	Item stoneItem = Items::Stone(); // 64 - это gridSizeI

	// add item like stone to player inventory
	player->e_getInventory()->addItem(stoneItem);

	// add item like a from registry
	player->e_getInventory()->addItem(ItemRegistry::getItem(2));

	// add test item to player inventory
	player->e_getInventory()->addItem(ItemRegistry::getItem(99));
}

void Process::initEntitys() {
	// get random position from map array
	std::vector<sf::Vector2f> spawnPosArray = mapTiles->getSpawnPosArray();

	// call function to get random position
	for (size_t i = 0; i < 1; i++)
		entitys.push_back(new Slime(spawnPosArray[rand() % spawnPosArray.size()].x, spawnPosArray[rand() % spawnPosArray.size()].y, player));

	Slime sl(spawnPosArray[rand() % spawnPosArray.size()].x, spawnPosArray[rand() % spawnPosArray.size()].y, player);

	// add item like stone to world
	entitys.push_back(new EntityItem(ItemRegistry::getItem(1)));
}

void Process::registerItems() { // register items to registry
	ItemRegistry::registerItem(0, Items::Item_NULL());
	ItemRegistry::registerItem(1, Items::Stone());
	ItemRegistry::registerItem(2, Items::PoisonSmallRegeneration());
	ItemRegistry::registerItem(3, Items::Wood());
	ItemRegistry::registerItem(4, Items::IronSword());
	ItemRegistry::registerItem(5, Items::Bread());
	ItemRegistry::registerItem(6, Items::LeatherArmor());
	ItemRegistry::registerItem(7, Items::HealthPotion());
	ItemRegistry::registerItem(8, Items::GoldCoin());
	ItemRegistry::registerItem(99, Items::TestItem()); // Регистрация тестового предмета

	appfn::Logger::logStatic("Items has been registered", "Process::registerItems()");
	appfn::Logger::logStatic("Items count: " + std::to_string(ItemRegistry::getAllItems().size()), "Process::registerItems()");
}

Process::Process(StateData* state_data, const bool defaultLoad)
	: State(state_data), renderSprite(TextureManager::getTexture("texture_null"))

{ // init Parser
	if (defaultLoad)
		loadGameData();
	else
		initTileMapData();

	initView();
	registerItems();
	initTileMap();
	initPlayer();
	initEntitys();

	intGUI();

	appfn::Logger::logStatic("End initilization process", "Process::Process()");
}

Process::~Process() {
	if (saveGameData())
		appfn::Logger::logStatic("Game Data has be saved", "Process::~Process()::saveGameData()");
	else
		appfn::Logger::logStatic("Game Data has not be saved", "Process::~Process()::saveGameData()", logType::LERROR);

	delete myGN;
	delete mapTiles;
	delete player;
	delete noicedata;
	delete inventoryGUI;

	pausemenu.reset();
	minimap.reset();
	playerBar.clear();

	for (auto& it : entitys)
		delete it;
	entitys.clear();
}

void Process::resetGUI() {
	pausemenu.reset();
	minimap.reset();
	playerBar.clear();

	initView();
	intGUI();
}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// sub update functions
void Process::updateInput(const float& delta_time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) && getKeytime())
		inventoryGUI->toggleVisible();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && getKeytime())
		Ipaused = !Ipaused;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash) && getKeytime())
		Idebud = !Idebud;
}

void Process::updatePlayerInputs(const float& delta_time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) player->e_move(-1.f, 0.f, delta_time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) player->e_move(1.f, 0.f, delta_time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) player->e_move(0.f, 1.f, delta_time);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) player->e_move(0.f, -1.f, delta_time);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && getKeytime()) {
		for (auto& it : entitys)
			player->e_attack(it, delta_time);
	}
}

void Process::updateTileMap(const float& delta_time) { // update tilemap
	mapTiles->updateRenderArea(player->e_getGridPositionInt(int(std::floorf(IgridSize))));
	mapTiles->update(*player, delta_time);

	// update entitys collision
	for (size_t i = 0; i < entitys.size(); i++)
		mapTiles->update(*entitys[i], delta_time);
}

void Process::updateEntitys(const float& delta_time) { // update entitys
	for (size_t i = 0; i < entitys.size(); i++) {
		entitys[i]->e_update(delta_time);

		if (!entitys[i]->getAttributes())
			if (!entitys[i]->e_isAlive())
				entitys.erase(entitys.begin() + i);
	}
}

void Process::updateGUI(const float& delta_time) {
	// update player GUI inventory
	if (inventoryGUI->isVisible())
		inventoryGUI->update(ImousePosWindow);
	// update minimap
	if (minimap != nullptr)
		minimap->update(player->e_getPosition(), entitys[0]->e_getPosition());

	// Обновляем полоски здоровья и маны
	playerBar["HP_BAR"]->update(player->getAttributes()->getAttributes().health, player->getAttributes()->getAttributes().max_health);
	playerBar["MP_BAR"]->update(player->getAttributes()->getAttributes().mana, player->getAttributes()->getAttributes().max_mana);
}

// main update function
void Process::update(const float& delta_time) {
	// always update mouse position, inputs, and keyTime
	updateMousePositions(&view);
	updateKeytime(delta_time);
	updateInput(delta_time);


	if (Ipaused) { // update pause
		pausemenu->update(sf::Vector2f(ImousePosWindow));

		if (pausemenu->isButtonPressed("EXIT_BUTTON") && getKeytime())
			endState();
		if (pausemenu->isButtonPressed("GEN") && getKeytime()) {
			mapTiles->regenerateMap();

			reCaclulateCharacterSize();
			initTileMapData();
			initTileMap();

			minimap->setImage(mapTiles->getMinimapImage());
		}
	} else {
		if (inventoryGUI->isVisible())
			inventoryGUI->update(ImousePosScreen);


		updateEntitys(delta_time);
		updatePlayerInputs(delta_time);
		player->e_update(delta_time);
		if (player->e_isAlive() == false)
			endState();
		updateGUI(delta_time);
	}
	updateTileMap(delta_time);

	if (Idebud) {
		updateDebugTextBase(delta_time);
		updateDebugTextState(delta_time);
		updateDebugText();
	}
}

void Process::updateDebugTextState(const float& delta_time) {

	IstringStream
		<< "\nPlayer:\nComponents:\n\tvelX: " << player->e_getVelocity().x << "\n\tvelY: " << player->e_getVelocity().y
		<< "\nPosition:\n\tx: " << player->e_getPosition().x << "\n\ty: " << player->e_getPosition().y
		<< "\n\tgrid x: " << player->e_getGridPositionFloat(IgridSize).x
		<< "\n\tgrid y: " << player->e_getGridPositionFloat(IgridSize).y
		<< "\nMap Size: " << mapTiles->getMapSizeOnTiles().x << ' x ' << mapTiles->getMapSizeOnTiles().y
		<< "\nMap Area Render: "
		<< mapTiles->getRenderArea().fromX << ' ' << mapTiles->getRenderArea().fromY << ' '
		<< mapTiles->getRenderArea().toX << ' ' << mapTiles->getRenderArea().toY
		<< "\nPause:\t" << Ipaused
		<< "\nMemory Usage: "
		<< "\n\tPlayer: " << sizeof(*player) << " = " << sizeof(Player) << " bytes"
		<< "\n\tEntitys: " << entitys.size() << " x " << sizeof(Entity) << " = " << entitys.size() * sizeof(Entity) << " bytes"
		<< "\n\tTotal Entitys: " << Entity::count_entitys << "\n\tEntity[0] Data:"
		<< "\n\t\tmovDir: " << entitys[0]->getMovement()->getDirectionVec().x << ' ' << entitys[0]->getMovement()->getDirectionVec().y
		<< "\n\t\tmovVel: " << entitys[0]->getMovement()->getVelocity().x << ' ' << entitys[0]->getMovement()->getVelocity().y
		<< "\n\tTileMap: " << sizeof(*mapTiles) << " bytes"
		<< "\n\tPauseMenu: " << sizeof(*pausemenu) << " bytes"
		<< "\n\tTotal usage: "		<< sizeof(*player) + (entitys.size() * sizeof(Entity)) +	sizeof(mapTiles) + sizeof(*pausemenu)
		<< " bytes\nGenerator data:\n\tSeed:\t"
		<< noicedata->seed << "\n\tOctaves:\t"
		<< noicedata->octaves << "\n\tFrequency:\t"
		<< noicedata->frequency << "\n\tAmplifire:\t"
		<< noicedata->amplifire << "\n\tPersistence:\t"
		<< noicedata->persistence << "\n\tNoiceSizeBYWindowX:\t"
		<< noicedata->RenderWindowX << "\n\tNoiceSizeBYWindowY:\t"
		<< noicedata->RenderWindowY << "\n\tNoiceSizeMapX:\t"
		<< noicedata->mapSizeX << "\n\tNoiceSizeMapY:\t"
		<< noicedata->mapSizeY;
}

void Process::updateSounds(const float& delta_time) {}

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// sub render functions
void Process::renderGUI(sf::RenderTarget& target) {
	if (Idebud) // debuging text render
		target.draw(Itext);

	for (auto& it : playerBar) // render player bars
		target.draw(*it.second);

	if (minimap != nullptr) // Minimap Render
		minimap->render(target);

	if (inventoryGUI->isVisible() && inventoryGUI)
		target.draw(*inventoryGUI);

	if (Ipaused && pausemenu != nullptr) // Pause menu render
		pausemenu->render(target);
}

void Process::renderTileMap(sf::RenderTarget& target) {
	mapTiles->render(&target);
}

void Process::renderEntities(sf::RenderTarget& target) {
	for (auto& enemy : entitys)
		enemy->e_render(target, Idebud);
}

void Process::renderPlayer(sf::RenderTarget& target) {
	player->e_render(target, Idebud);
	playerView.setCenter(player->e_getPosition());
}

// main render function
void Process::render(sf::RenderWindow& target) {
	// CLEAR pre rendered texture
	renderTexture.clear();
	renderTexture.setView(playerView);
	// render scne in custom view
	renderTileMap(renderTexture);
	renderEntities(renderTexture);
	renderPlayer(renderTexture);
	// reset view
	renderTexture.setView(renderTexture.getDefaultView());
	// render GUI elements
	renderGUI(renderTexture);
	// final render
	renderTexture.display();
	target.draw(renderSprite);
}