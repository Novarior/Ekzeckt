#include "State.hpp"

/**
 * @brief Construct a new State:: State object
 *
 * @param state_data
 */
State::State(StateData* state_data)
	: IstateData(state_data),
	Itext(*FontManager::getFont(FontID::FONT_DEBUG), "",
		  IstateData->sd_characterSize_debug),
	IRenderSprite(TextureManager::getTexture(TextureID::TEXTURE_NULL)) {
	// write log message what im here doing something
	appfn::Logger::logStatic("Start initilization state", "State::State()");

	// init variabless from state_data to curent state

	Iwindow = state_data->sd_Window;
	Istates = state_data->sd_States;
	IKeySupports = state_data->sd_KeySupports;
	// IKeyboard = state_data->sd_keyboard_prt;
	Iquit = false;
	Ipaused = false;
	Ikeytime = 0.f;
	IkeytimeMax = 0.3f;
	IgridSize = state_data->sd_gridSize;
	// get access to volume manager from global state data like a shared pointer

	IstringStream.str("");
	Idebud = __MDEBUG__;
	auto& font = *FontManager::getFont(FontID::FONT_DEBUG);

	Itext.setFont(font);
	Itext.setOutlineThickness(1);
	Itext.setOutlineColor(sf::Color::Black);

	appfn::Logger::logStatic("End initilization state", "State::State()");
	initBuffer();
	initRenderDefines();
	resetView();
}

State::~State() { appfn::Logger::logStatic("destroy state", "State::~State()"); }

// Accessors
const bool State::getKeytime() {
	if (Ikeytime >= IkeytimeMax) {
		Ikeytime = 0.f;
		return true;
	}
	return false;
}
void State::updateDebugTextBase(const float& delta_time) {
	float deltaF = 1 / delta_time;
	IstringStream
		<< "\nver:\t" << CMAKE_PROJECT_VERSION << "\nCurrent memory usage:\t"
		<< appfn::MemoryUsageMonitor::formatMemoryUsage(appfn::MemoryUsageMonitor::getCurrentMemoryUsage())
		<< "\nDelta Time:\t" << delta_time
		<< "\nFPS delta:\t" << deltaF
		<< "\nFPS Clock:\t" << appfn::FPS::getFPS()
		<< "\nFPS limit:\t" << IstateData->sd_gfxSettings.lock()->frameRateLimit
		<< "\nSD_WIN_Size:\t" << IstateData->sd_Window.lock()->getSize().x << " x " << IstateData->sd_Window.lock()->getSize().y
		<< "\nSD_WIN_View_Size:\t" << IstateData->sd_Window.lock()->getView().getSize().x << " x " << IstateData->sd_Window.lock()->getView().getSize().y
		<< "\nSD_WIN_Center:\t" << IstateData->sd_Window.lock()->getView().getCenter().x << " x " << IstateData->sd_Window.lock()->getView().getCenter().y
		<< "\nWIN_Size:\t" << Iwindow.lock()->getSize().x << " x " << Iwindow.lock()->getSize().y
		<< "\nWIN_View_Size:\t" << Iwindow.lock()->getView().getSize().x << " x " << Iwindow.lock()->getView().getSize().y
		<< "\nWIN_Center:\t" << Iwindow.lock()->getView().getCenter().x << " x " << Iwindow.lock()->getView().getCenter().y
		<< "\nrViev_Size:\t" << view.getSize().x << " x " << view.getSize().y
		<< "\nrSprite_Size:\t" << IRenderSprite.getTextureRect().size.x << " x " << IRenderSprite.getTextureRect().size.y
		<< "\nrSprite_Texture_Size:\t" << IRenderSprite.getTexture().getSize().x << " x " << IRenderSprite.getTexture().getSize().y
		<< "\n"
		<< "\nAntialiasing:\t" << IstateData->sd_Window.lock()->getSettings().antiAliasingLevel
		<< "\nvSync:\t" << IstateData->sd_gfxSettings.lock()->verticalSync
		<< "\nMouse Pos:\t" << ImousePosWindow.x << " x " << ImousePosWindow.y;
}

void State::updateDebugText() {
	Itext.setString(IstringStream.str());
	IstringStream.str("");
}
///////////////////////////////////////////
///////////		INITS		////////////
///////////////////////////////////////////

void State::initRenderDefines() {
	auto ws = Iwindow.lock()->getSize();
	if (!IRenderTexture.resize({ws}))
		appfn::Logger::logStatic("renderTexture cannot be resize", "MainMenu::initRenderDefines()", logType::LERROR);

	IRenderTexture.setSmooth(true);
	IRenderSprite.setTextureRect(sf::IntRect({0, 0}, {static_cast<int>(IRenderTexture.getSize().x), static_cast<int>(IRenderTexture.getSize().y)}));
	IRenderSprite.setTexture(IRenderTexture.getTexture());
}

void State::resetView() {
	view.setSize(sf::Vector2f(
		static_cast<float>(IstateData->sd_Window.lock()->getSize().x),
		static_cast<float>(IstateData->sd_Window.lock()->getSize().y)));

	view.setCenter(sf::Vector2f(
		static_cast<float>(IstateData->sd_Window.lock()->getSize().x) / 2,
		static_cast<float>(IstateData->sd_Window.lock()->getSize().y) / 2));

	IstateData->sd_Window.lock()->setView(view);
	Iwindow.lock()->setView(view);
}

// create shared maps with sounds and categoty, buffers and categoty
void State::initBuffer() {
	IsoundsMap = std::map<std::string, sf::Sound>();
	IsoundBufferMap = std::unordered_map<gfx::SoundCategory, std::map<std::string, sf::SoundBuffer>>();
}

// load sound to buffer
bool State::loadSoundtoBuffer(gfx::SoundCategory _soundcategory, std::filesystem::path _namepath, std::string _typename) {
	sf::SoundBuffer buffer;
	auto bf = appfn::PathTool::getPathResourcesDir() += _namepath;
	if (!buffer.loadFromFile(bf)) {
		appfn::Logger::logStatic("Failed to load sound buffer", "State::loadSoundtoBuffer()", logType::LERROR);
		return false;
	}

	IsoundBufferMap[_soundcategory][_typename] = buffer;
	return true;
}

void State::updateKeytime(const float& delta_time) {
	if (Ikeytime < IkeytimeMax) Ikeytime += delta_time;
}



void State::reCaclulateCharacterSize() {
	auto ws = Iwindow.lock()->getSize();
	IstateData->sd_characterSize_debug = mmath::calcCharSize(ws.x, ws.y, 200U);
	IstateData->sd_characterSize_game_big = mmath::calcCharSize(ws.x, ws.y, 100U);
	IstateData->sd_characterSize_game_medium = mmath::calcCharSize(ws.x, ws.y, 120U);
	IstateData->sd_characterSize_game_small = mmath::calcCharSize(ws.x, ws.y, 150U);
}

void State::updateMousePositions(sf::View* view) {

	ImousePosScreen = sf::Mouse::getPosition();
	ImousePosWindow = sf::Mouse::getPosition(*Iwindow.lock());

	if (view)
		Iwindow.lock()->setView(*view);

	ImousePosView = Iwindow.lock()->mapPixelToCoords(sf::Mouse::getPosition(*Iwindow.lock()));
	ImousePosGrid = sf::Vector2i(
		static_cast<int>(ImousePosView.x) / static_cast<int>(IgridSize),
		static_cast<int>(ImousePosView.y) / static_cast<int>(IgridSize));

	Iwindow.lock()->setView(Iwindow.lock()->getDefaultView());
}

void State::setVolume(gfx::SoundCategory _category, const float _newVal) // Set volume for all categories
{
	IstateData->sd_VolumeCollector.lock()->setCategoryVolume(_category, _newVal);
	for (auto& it : IsoundsMap)
		it.second.setVolume(IstateData->sd_VolumeCollector.lock()->getCategoryVolume(_category));
}