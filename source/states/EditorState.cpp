#include "EditorState.hpp"

#include "../core/math/mymath.hpp"

#include "../localisation/helperText.hpp"


void EditorState::initGUI() {
	initTabMenu();
	initButtons();
	initSelectors();
	initDebugText();
}

void EditorState::initTabMenu() { // tab menu
	tabShape.setPosition(sf::Vector2f(mmath::p2pX(70U, IstateData->sd_Window.lock()->getSize().x), 0));
	tabShape.setSize(sf::Vector2f(mmath::p2pX(30U, IstateData->sd_Window.lock()->getSize().x), IstateData->sd_Window.lock()->getSize().y));
	// half transparent gray
	tabShape.setFillColor(sf::Color(30, 40, 65, 150));
	tabShape.setOutlineThickness(5.f);
	tabShape.setOutlineColor(sf::Color(100, 100, 100, 150));
	showTabmenu = false;
}

void EditorState::initButtons() { // init buttons
	sf::Vector2f tabSize = tabShape.getSize();
	sf::Vector2f tabPos = tabShape.getPosition();
	sf::Vector2f btnSize2 = sf::Vector2f(tabSize.x / 2.f, mmath::p2pX(6.F, tabSize.y));
	sf::Vector2f btnSize3 = sf::Vector2f(tabSize.x / 3.f, mmath::p2pX(6.F, tabSize.y));
	float btnOffsetY = mmath::p2pX(6.F, tabSize.y);

	//////////////////////////////////////////////////
	// btn layout
	//	 ________________________
	//	|			|			|
	//	|___________|___________|
	//	|		|		|		|
	//	|_______|_______|_______|

	IGUILayout["SAVE_GENDATA"] = std::make_unique<gui::Button>(
		sf::Vector2f(tabPos.x, tabPos.y + tabSize.y - btnOffsetY * 2.f),
		btnSize2, "Save");

	IGUILayout["LOAD_GENDATA"] = std::make_unique<gui::Button>(
		sf::Vector2f(tabPos.x + btnSize2.x, tabPos.y + tabSize.y - btnOffsetY * 2.f),
		btnSize2, "Load");

	IGUILayout["G_SEED"] = std::make_unique<gui::Button>(
		sf::Vector2f(tabPos.x, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "New Seed");

	IGUILayout["G_NOICE"] = std::make_unique<gui::Button>(
		sf::Vector2f(tabPos.x + btnSize3.x, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "Gen Noice");

	IGUILayout["G_TREE"] = std::make_unique<gui::Button>(
		sf::Vector2f(tabPos.x + btnSize3.x * 2.f, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "Gen Tree");

}

void EditorState::initSelectors() { // init static selector in tab menu
	auto& font = *FontManager::getFont(FontID::FONT_GAMEF_01);
	sf::Vector2f btnSize = sf::Vector2f(tabShape.getSize().x, mmath::p2pX(7U, IstateData->sd_Window.lock()->getSize().y));
	//gui::SliderFloat sl(pos, size, font, charsize,baseVal, min, max, name);
	sf::Vector2f tbPos = tabShape.getPosition();
	sf::Vector2f tbSize = tabShape.getSize();
	auto& ndata = m_noiceData;

	staticSelectorUInt["OCTAVES"] = new gui::SliderUInt(
		tbPos, btnSize, font, IstateData->sd_characterSize_game_small, ndata->octaves, 1U, 10U, "Octaves: ");

	staticSelector["FREQUENCY"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(7U, IstateData->sd_Window.lock()->getSize().y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->frequency, 0.f, 15.f, "Frequency: ");

	staticSelector["PERSISTENCE"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(14U, IstateData->sd_Window.lock()->getSize().y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->persistence, 0.f, 2.0f, "Persistence: ");

	staticSelector["AMPLIFIRE"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(21U, IstateData->sd_Window.lock()->getSize().y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->amplifire, 0.f, 3.f, "Amplifire: ");

	std::vector<std::string> list = {"Linear", "Cosine", "Cubic", "Quintic", "Quartic", "Quadratic", "Hermite"};

	selector = new gui::Selector(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(28.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, list.data(), list.size(), 0);

	// set default value for static selector
	staticSelectorUInt["OCTAVES"]->setCurrentValue(m_noiceData->octaves);
	staticSelector["FREQUENCY"]->setCurrentValue(m_noiceData->frequency);
	staticSelector["AMPLIFIRE"]->setCurrentValue(m_noiceData->amplifire);
	staticSelector["PERSISTENCE"]->setCurrentValue(m_noiceData->persistence);
}

void EditorState::initNoice() {
	m_noiceData = new NoiceData();
	std::srand(std::time(nullptr));


	m_noiceData->seed = mmath::splitmix64(std::rand());
	m_noiceData->smoothMode = 0;
	m_noiceData->octaves = 6;
	m_noiceData->frequency = 6.0f;
	m_noiceData->persistence = 0.6f;
	m_noiceData->amplifire = 1.f;

	m_noiceData->gridSize = IstateData->sd_gridSize;
	m_noiceData->RenderWindowX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	m_noiceData->RenderWindowY = IstateData->sd_gfxSettings.lock()->resolution.size.y;
	m_noiceData->mapSizeX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	m_noiceData->mapSizeY = IstateData->sd_gfxSettings.lock()->resolution.size.y;

	// init data for noice viewer
	m_NoiceViewer = new NoiceViewer(m_noiceData);
	m_NoiceViewer->generateNoice();
}

void EditorState::initDebugText() { // init debug text
	//Itext.setFont(*FontManager::getFont(FontID::FONT_GAMEF_01));
	Itext.setCharacterSize(IstateData->sd_characterSize_debug);
	Itext.setPosition(sf::Vector2f(0, 0));
	Itext.setFillColor(sf::Color::White);
	Itext.setOutlineColor(sf::Color::Black);
	Itext.setOutlineThickness(2.f);
}

EditorState::EditorState(StateData* statedata): State(statedata) {
	// init logger
	appfn::Logger::logStatic("Start initilization EditorState", "EditorState::EditorState()");
	// init keybinds

	initNoice();
	initGUI();

	current_View_Generator = 0;

	// init LSystem
	myLS = new LSystem();
	myLS->setRule('d', "qd");
	myLS->setRule('s', "d[[-qqs]qs]+qqs[+q|]-q|");
	myLS->setOffsetPos(sf::Vector2f(IstateData->sd_Window.lock()->getSize().x / 2, IstateData->sd_Window.lock()->getSize().y * 0.90));
	myLS->generate();

	appfn::Logger::logStatic("End initilization EditorState", "EditorState::EditorState()");
}

EditorState::~EditorState() {
	appfn::Logger::logStatic("Start destruction EditorState", "EditorState::~EditorState()");

	// FIXME: add save noice data to file
	// ParserJson::saveNoiceData( m_NoiceViewer->getNoiceData());

	IGUILayout.clear();

	for (auto& it : staticSelector)
		delete it.second;

	for (auto& it : staticSelectorUInt)
		delete it.second;

	delete m_NoiceViewer;
	delete selector;
	delete myLS;
	delete m_noiceData;
}

void EditorState::updateDebugTextState(const float& delta_time) {
	IstringStream
		<< "\nNavigation:\n\t\t['/'] Togle LINFO menu"
		<< "\n\t\t['Q'] Switch Noice generator"
		<< "\n\t\t['W'] Switch color mode"
		<< "\n\t\t['E'] Change current viewport of generators"
		<< "\n\t\t['R'] switch fast mode noices (not simplex)"
		<< "\nCurent view generator:\t" << current_View_Generator
		<< "\nCurent noice view mode:\t" << m_NoiceViewer->getNoiceModelName() << ":\t" << m_NoiceViewer->getNoiceModel()
		<< "\nCurent noice color mode:\t" << m_NoiceViewer->getColorModeName() << ":\t" << m_NoiceViewer->getColorMode()
		<< "\nNoiceData:\nSeed:\t" << m_NoiceViewer->getNoiceData()->seed
		<< "\n\tOctaaves: " << m_noiceData->octaves
		<< "\n\tFrequency: " << m_noiceData->frequency
		<< "\n\tPersistence: " << m_noiceData->persistence
		<< "\n\tAmplifire: " << m_noiceData->amplifire
		<< "\n\tOffSet: " << m_noiceData->offsetSeed
		<< "\nCurent noice smooth mode:\t" << m_NoiceViewer->getNoiceSmouthName() << ":\t" << m_NoiceViewer->getNoiceData()->smoothMode
		<< "\nFastMode" << m_NoiceViewer->getNoiceData()->fastMode
		<< "\nHeigth on Cursor: " << m_NoiceViewer->getHeightMap(ImousePosWindow)
		<< "\nTree Data:\n\tTreeSize:\t" << myLS->getSizeTree()
		<< "\n\tTreeAxiom\t" << myLS->getAxiomSize();
}

void EditorState::resetGUI() {
	IGUILayout.clear();
	for (auto& it : staticSelector)	delete it.second;
	for (auto& it : staticSelectorUInt) delete it.second;
	delete m_NoiceViewer;
	delete selector;

	auto& gfx = *IstateData->sd_gfxSettings.lock();
	if (gfx.fullscreen)
		Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Fullscreen, gfx.contextSettings);
	else
		Iwindow.lock()->create(gfx.resolution, gfx.title, sf::State::Windowed, gfx.contextSettings);

	Iwindow.lock()->setFramerateLimit(gfx.frameRateLimit);

	initNoice();
	initGUI();
	//	initRenderDefines();
	//	resetView();

	m_noiceData->gridSize = IstateData->sd_gridSize;
	m_noiceData->RenderWindowX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	m_noiceData->RenderWindowY = IstateData->sd_gfxSettings.lock()->resolution.size.y;
	m_noiceData->mapSizeX = IstateData->sd_gfxSettings.lock()->resolution.size.x;
	m_noiceData->mapSizeY = IstateData->sd_gfxSettings.lock()->resolution.size.y;
	myLS->setOffsetPos(sf::Vector2f(IstateData->sd_Window.lock()->getSize().x / 2, IstateData->sd_Window.lock()->getSize().y * 0.90));

}

sf::IntRect EditorState::findNonTransparentRect(const sf::Image& image) {
	// this function find non transparent pixels
	// and return IntRect without this pixels
	sf::Vector2u size = image.getSize();
	sf::Rect<unsigned> mrect({size.x, size.y}, {0, 0});

	for (unsigned int x = 0; x < size.x; x++)
		for (unsigned int y = 0; y < size.y; y++)
			if (image.getPixel({x, y}) != sf::Color::Transparent) {
				if (x < mrect.position.x) mrect.position.x = x;
				if (y < mrect.position.y) mrect.position.y = y;
				if (x > mrect.size.x) mrect.size.x = x;
				if (y > mrect.size.y) mrect.size.y = y;
			}

	return sf::Rect<int>(mrect);
}

void EditorState::saveTreeAsImage(sf::RenderWindow& window) {
	sf::Texture texture(sf::Vector2u(window.getSize().x, window.getSize().y));	// create texture with window size

	// get array shape
	std::vector<sf::RectangleShape> shapes;
	shapes.insert(shapes.end(), myLS->internalArray(), myLS->internalArray() + myLS->getSizeArray());

	// fill buffer with Transparent pixels for drawing generated tree
	window.clear(sf::Color::Transparent);
	for (auto& it : shapes)
		window.draw(it);

	// update
	texture.update(window);

	// get snapshoot
	sf::Image image = texture.copyToImage();

	// find Transparent pixels
	sf::IntRect mrect = findNonTransparentRect(image);

	// create newe image on mrect base
	sf::Image simg(sf::Vector2u(mrect.size.x - mrect.position.x, mrect.size.y - mrect.position.y), sf::Color::Black);

	// copy pixels from original image
	for (unsigned int x = mrect.position.x; x < mrect.size.x; x++)
		for (unsigned int y = mrect.position.y; y < mrect.size.x; y++)
			simg.setPixel(sf::Vector2u(x - mrect.position.x, y - mrect.position.y), image.getPixel({x, y}));

	// create name for image file
	// add time to name for unique name
	std::stringstream ss;
	// ss << ApplicationsFunctions::getDocumentsAppFolder() << "/tree/" << std::to_string(std::time(nullptr)) << ".png";

	// save image
	if (!simg.saveToFile(ss.str()))
		appfn::Logger::logStatic("Image" + ss.str() + " has be corrupt and dosent saved!", "EditorState::saveTreeAsImage()", logType::LERROR);
}

void EditorState::updateInput(const float& delta_time) {
	// if pressed key ESC then end state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape) && getKeytime())
		endState();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Slash) && getKeytime())
		Idebud = !Idebud;

	// switch tab menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab) && getKeytime())
		showTabmenu = !showTabmenu;

	// update currentViewGenerator in a range from 0 to 2
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && getKeytime())
		m_NoiceViewer->swithNoiceModel();

	// switch noice model
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && getKeytime())
		m_NoiceViewer->swithColorMode();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && getKeytime()) {
		if (current_View_Generator < 2)
			current_View_Generator++;
		else
			current_View_Generator = 0;
	}
	// switch noice smooth mode (fast mode)
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && getKeytime())
		m_noiceData->fastMode = !m_noiceData->fastMode;
}



void EditorState::updateButtons(const float& delta_time) {
	for (auto& it : IGUILayout)
		it.second->update(ImousePosView);

	for (auto& it : staticSelectorUInt)
		it.second->update(ImousePosView);

	for (auto& it : staticSelector)
		it.second->update(ImousePosView);

	selector->update(delta_time, ImousePosView);

	// update buttons using switch case for each button
	switch (current_View_Generator) {
	case 0: // noice case
		if (staticSelectorUInt["OCTAVES"]->isValueChanged()) {
			m_noiceData->octaves = staticSelectorUInt["OCTAVES"]->getValue();
			staticSelectorUInt["OCTAVES"]->closeChangeValue();
		}
		if (staticSelector["FREQUENCY"]->isValueChanged()) {
			m_noiceData->frequency = staticSelector["FREQUENCY"]->getValue();
			staticSelector["FREQUENCY"]->closeChangeValue();
		}
		if (staticSelector["PERSISTENCE"]->isValueChanged()) {
			m_noiceData->persistence = staticSelector["PERSISTENCE"]->getValue();
			staticSelector["PERSISTENCE"]->closeChangeValue();
		}
		if (staticSelector["AMPLIFIRE"]->isValueChanged()) {
			m_noiceData->amplifire = staticSelector["AMPLIFIRE"]->getValue();
			staticSelector["AMPLIFIRE"]->closeChangeValue();
		}
		if (IGUILayout["G_SEED"]->isPressed() && getKeytime()) {
			m_noiceData->seed = mmath::splitmix64(std::rand());
		}
		if (IGUILayout["G_NOICE"]->isPressed() && getKeytime()) {
			m_NoiceViewer->generateNoice();
		}
		if (IGUILayout["SAVE_GENDATA"]->isPressed()) {
			// fixme: add save noice data to file
		}
		if (IGUILayout["LOAD_GENDATA"]->isPressed()) {
			// fixme: add load noice data from file
			staticSelectorUInt["OCTAVES"]->setCurrentValue(m_noiceData->octaves);
			staticSelector["FREQUENCY"]->setCurrentValue(m_noiceData->frequency);
			staticSelector["AMPLIFIRE"]->setCurrentValue(m_noiceData->amplifire);
			staticSelector["PERSISTENCE"]->setCurrentValue(m_noiceData->persistence);
			selector->setActiveElement(m_noiceData->smoothMode);
		}
		m_NoiceViewer->setNoiceData(m_noiceData);
		break;
	case 1: // tree case
		if (IGUILayout["G_TREE"]->isPressed()) {
			myLS->generate();
			saveTreeAsImage(*IstateData->sd_Window.lock());
		}
		break;
	default: // default case
		break;
	}
	selector->update(delta_time, ImousePosView);
	m_noiceData->smoothMode = selector->getActiveElementID();
}

void EditorState::updateSounds(const float& delta_time) {}

void EditorState::update(const float& delta_time) {
	// update keytime for next function used it for keypress delay
	updateKeytime(delta_time);
	updateInput(delta_time);
	updateMousePositions();

	myLS->update(delta_time);
	// if tab menu is open then update buttons
	if (showTabmenu)
		updateButtons(delta_time);

	if (Idebud) {
		updateDebugTextBase(delta_time);
		updateDebugTextState(delta_time);
		updateDebugText();
	}
}

void EditorState::renderTabMenu(sf::RenderTarget& target) {
	target.draw(tabShape);

	for (auto& it : staticSelector)
		target.draw(*it.second);

	for (auto& it : staticSelectorUInt)
		target.draw(*it.second);

	for (auto& it : IGUILayout)
		target.draw(*it.second);

	selector->render(target);
}

void EditorState::render(sf::RenderWindow& target) {
	// layer 0 - noice render and tree render
	switch (current_View_Generator) {
	case 0: // call noice render
		if (m_NoiceViewer != nullptr)
			m_NoiceViewer->render(target);
		break;
	case 1: // call tree render
		if (myLS != nullptr)
			myLS->render(target);
		break;
	default:
		break;
	}
	// layer 1 - tab menu render
	if (showTabmenu)
		renderTabMenu(target);

	// layer 2 - debug text render
	// render debug text
	if (Idebud)
		target.draw(Itext);
}
