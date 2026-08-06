#include "EditorState.hpp"

#include "../core/math/mymath.hpp"

#include "../localisation/helperText.hpp"


void EditorState::initGUI() {
	IGUILayout.resize(vCount);
	staticSelector.resize(vCount);
	staticSelectorUInt.resize(vCount);
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

	IGUILayout[cViewGen::vAll]["SAVE_GENDATA"] = new gui::Button(
		sf::Vector2f(tabPos.x, tabPos.y + tabSize.y - btnOffsetY * 2.f),
		btnSize2, "Save");

	IGUILayout[cViewGen::vAll]["LOAD_GENDATA"] = new gui::Button(
		sf::Vector2f(tabPos.x + btnSize2.x, tabPos.y + tabSize.y - btnOffsetY * 2.f),
		btnSize2, "Load");

	IGUILayout[cViewGen::vAll]["G_SEED"] = new gui::Button(
		sf::Vector2f(tabPos.x, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "New Seed");

	IGUILayout[cViewGen::vNoice]["G_NOICE"] = new gui::Button(
		sf::Vector2f(tabPos.x + btnSize3.x, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "Gen Noice");

	IGUILayout[cViewGen::vSpiral]["G_SPIRAL"] = new gui::Button(
		sf::Vector2f(tabPos.x + btnSize3.x, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "Gen Spiral");

	IGUILayout[cViewGen::vLSystem]["G_TREE"] = new gui::Button(
		sf::Vector2f(tabPos.x + btnSize3.x * 2.f, tabPos.y + tabSize.y - btnOffsetY),
		btnSize3, "Gen Tree");

}

void EditorState::initSelectors() { // init static selector in tab menu
	auto& font = *FontManager::getFont(FontID::FONT_GAMEF_01);
	//gui::SliderFloat sl(pos, size, font, charsize,baseVal, min, max, name);
	sf::Vector2f tbPos = tabShape.getPosition();
	sf::Vector2f tbSize = tabShape.getSize();
	sf::Vector2f btnSize = sf::Vector2f(tabShape.getSize().x, mmath::p2pX(6.f, tbSize.y));
	auto& ndata = m_noiceData;

	staticSelectorUInt[cViewGen::vNoice]["OCTAVES"] = new gui::SliderUInt(
		tbPos, btnSize, font, IstateData->sd_characterSize_game_small, ndata->octaves, 1U, 10U, "Octaves: ");

	staticSelector[cViewGen::vNoice]["FREQUENCY"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(6.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->frequency, 0.f, 15.f, "Frequency: ");

	staticSelector[cViewGen::vNoice]["PERSISTENCE"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(12.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->persistence, 0.f, 2.0f, "Persistence: ");

	staticSelector[cViewGen::vNoice]["AMPLIFIRE"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(18.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, ndata->amplifire, 0.f, 3.f, "Amplifire: ");

	std::vector<std::string> list = {"Linear", "Cosine", "Cubic", "Quintic", "Quartic", "Quadratic", "Hermite"};

	selector = new gui::Selector(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(28.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, list.data(), list.size(), 0);

	//// set default value for static selector
	//staticSelectorUInt[cViewGen::vNoice]["OCTAVES"]->setCurrentValue(m_noiceData->octaves);
	//staticSelector[cViewGen::vNoice]["FREQUENCY"]->setCurrentValue(m_noiceData->frequency);
	//staticSelector[cViewGen::vNoice]["AMPLIFIRE"]->setCurrentValue(m_noiceData->amplifire);
	//staticSelector[cViewGen::vNoice]["PERSISTENCE"]->setCurrentValue(m_noiceData->persistence);

	auto& sData = spiralData;

	staticSelector[cViewGen::vSpiral]["SPR_GALX_RAD"] = new gui::SliderFloat(
		tbPos, btnSize, font, IstateData->sd_characterSize_game_small, sData.galaxyRadius, 1000.f, 5000.f, "Galaxy Radius: ");

	staticSelectorUInt[cViewGen::vSpiral]["SPR_ARMS"] = new gui::SliderUInt(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(6.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.spiralArms, 1U, 30U, "Spiral Arms: ");

	staticSelector[cViewGen::vSpiral]["SPR_ARMS_CURVE"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(12.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.spiralArmCurvature, 0.f, 90.f, "Spiral Arms Curve: ");

	staticSelector[cViewGen::vSpiral]["SPR_CORE_RAD"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(18.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.CoreRadius, 0.f, 1000.0f, "Core Radius: ");

	staticSelector[cViewGen::vSpiral]["SPR_CORE_BRNTH"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(24.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.CoreBrightness, 0.f, 100.f, "Core Brightness: ");

	staticSelector[cViewGen::vSpiral]["SPR_DENS_DUST"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(30.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.DustDensity, 0, 1000, "Density of Dust: ");

	staticSelector[cViewGen::vSpiral]["SPR_DENS_GAS"] = new gui::SliderFloat(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(36.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.GasDensity, 0U, 10000U, "Density of Gas: ");

	staticSelectorUInt[cViewGen::vSpiral]["SPR_STAR_COUNT"] = new gui::SliderUInt(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(42.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.starCount, 1000U, 30000U, "Star Cound: ");

	staticSelectorUInt[cViewGen::vSpiral]["SPR_ARM_LEN"] = new gui::SliderUInt(
		sf::Vector2f(tbPos.x, tbPos.y + mmath::p2pX(48.f, tbSize.y)),
		btnSize, font, IstateData->sd_characterSize_game_small, sData.spiralArmCount, 1000U, 30000U, "Spiral Arm Length: ");
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

void EditorState::initMathMoodels() {
	initSpiralMathModel();
	initLSystemMathModel();
}

void EditorState::initSpiralMathModel() {
	spiralModel = new SpiralModel(&spiralData, Iwindow.lock()->getSize());
}

void EditorState::initLSystemMathModel() {	// init LSystem
	myLS = new LSystem();
	myLS->setRule('d', "qd");
	myLS->setRule('s', "d[[-qqs]qs]+qqs[+q|]-q|");
	myLS->setOffsetPos(sf::Vector2f(IstateData->sd_Window.lock()->getSize().x / 2, IstateData->sd_Window.lock()->getSize().y * 0.90));
	myLS->generate();
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
	IStateName = "EditorState";

	appfn::Logger::logStatic("Start initilization EditorState", "EditorState::EditorState()");

	strCurrentViewGen = {"vNoice", "vLSystem","vSpiral","vAll"};

	initNoice();
	initMathMoodels();
	initGUI();

	appfn::Logger::logStatic("End initilization EditorState", "EditorState::EditorState()");
}

EditorState::~EditorState() {
	appfn::Logger::logStatic("Start destruction EditorState", "EditorState::~EditorState()");

	// FIXME: add save noice data to file
	// ParserJson::saveNoiceData( m_NoiceViewer->getNoiceData());


	for (auto& lay : IGUILayout)
		for (auto& it : lay)
			delete it.second;
	IGUILayout.clear();

	for (auto& lay : staticSelector)
		for (auto& it : lay)
			delete it.second;

	for (auto& lay : staticSelectorUInt)
		for (auto& it : lay)
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
		<< "\nCurent view generator:\t" << strCurrentViewGen[current_View_Generator] << ": " << current_View_Generator;
	switch (current_View_Generator) {
	case cViewGen::vNoice:
		IstringStream << "\nCurent noice view mode:\t" << m_NoiceViewer->getNoiceModelName() << ":\t" << m_NoiceViewer->getNoiceModel()
			<< "\nCurent noice color mode:\t" << m_NoiceViewer->getColorModeName() << ":\t" << m_NoiceViewer->getColorMode()
			<< "\nNoiceData:\nSeed:\t" << m_NoiceViewer->getNoiceData()->seed
			<< "\n\tOctaaves: " << m_noiceData->octaves
			<< "\n\tFrequency: " << m_noiceData->frequency
			<< "\n\tPersistence: " << m_noiceData->persistence
			<< "\n\tAmplifire: " << m_noiceData->amplifire
			<< "\n\tOffSet: " << m_noiceData->offsetSeed
			<< "\nCurent noice smooth mode:\t" << m_NoiceViewer->getNoiceSmouthName() << ":\t" << m_NoiceViewer->getNoiceData()->smoothMode
			<< "\nFastMode" << m_NoiceViewer->getNoiceData()->fastMode
			<< "\nHeigth on Cursor: " << m_NoiceViewer->getHeightMap(ImousePosWindow);
		break;
	case cViewGen::vLSystem:
		IstringStream << "\nTree Data:\n\tTreeSize:\t" << myLS->getSizeTree()
			<< "\n\tTreeAxiom\t" << myLS->getAxiomSize();
		break;
	case cViewGen::vSpiral:
		IstringStream << "\nGalaxy Parameters:\n\tSeed: " << spiralData.seed
			<< "\n\tRadius: " << spiralData.galaxyRadius
			<< "\n\tCount Stars: " << spiralData.starCount
			<< "\n\tArms: " << spiralData.spiralArms
			<< "\n\tArms Length: " << spiralData.spiralArmCount
			<< "\n\tArms Curvature: " << spiralData.spiralArmCurvature
			<< "\n\tCore Radius: " << spiralData.CoreRadius
			<< "\n\tCore Brightness: " << spiralData.CoreBrightness
			<< "\n\tDensity Dust: " << spiralData.DustDensity
			<< "\n\tDensity Gas: " << spiralData.GasDensity;
		break;
	}
}

void EditorState::resetGUI() {
	IGUILayout.clear();
	for (auto& lay : staticSelector)
		for (auto& it : lay)
			delete it.second;

	for (auto& lay : staticSelectorUInt)
		for (auto& it : lay)
			delete it.second;

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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E) && getKeytime()) {
		if (current_View_Generator < static_cast<int>(cViewGen::vSpiral))
			current_View_Generator++;
		else
			current_View_Generator = cViewGen::vNoice;
	}

	// safe from overlapping keybinds
	switch (current_View_Generator) {
	case cViewGen::vNoice:
		// switch noice smooth mode (fast mode)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R) && getKeytime())
			m_noiceData->fastMode = !m_noiceData->fastMode;
		// switch noice model
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && getKeytime())
			m_NoiceViewer->swithColorMode();
		// update currentViewGenerator in a range from 0 to 2
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q) && getKeytime())
			m_NoiceViewer->swithNoiceModel();
		break;
	case cViewGen::vLSystem:
		break;
	case cViewGen::vSpiral:
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::G) && getKeytime())
			spiralModel->regenerateSpiral();

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift))
			zoomView();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			resetView();
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
			moveView();




		break;
	}
}



void EditorState::updateButtons(const float& delta_time) {
	sf::Vector2f mouseF(ImousePosWindow);

	for (auto& it : IGUILayout[cViewGen::vAll])
		it.second->update(mouseF);

	for (auto& it : IGUILayout[current_View_Generator])
		it.second->update(mouseF);

	for (auto& it : staticSelectorUInt[current_View_Generator])
		it.second->update(mouseF);

	for (auto& it : staticSelector[current_View_Generator])
		it.second->update(mouseF);

	selector->update(delta_time, mouseF);

	// global btns
	// update buttons using switch case for each button
	if (IGUILayout[cViewGen::vAll]["SAVE_GENDATA"]->isPressed()) {
		// fixme: add save noice data to file
	}
	if (IGUILayout[cViewGen::vAll]["LOAD_GENDATA"]->isPressed()) {
		// fixme: add load noice data from file
		staticSelectorUInt[cViewGen::vNoice]["OCTAVES"]->setCurrentValue(m_noiceData->octaves);
		staticSelector[cViewGen::vNoice]["FREQUENCY"]->setCurrentValue(m_noiceData->frequency);
		staticSelector[cViewGen::vNoice]["AMPLIFIRE"]->setCurrentValue(m_noiceData->amplifire);
		staticSelector[cViewGen::vNoice]["PERSISTENCE"]->setCurrentValue(m_noiceData->persistence);
		selector->setActiveElement(m_noiceData->smoothMode);
	}
	if (IGUILayout[cViewGen::vAll]["G_SEED"]->isPressed() && getKeytime()) {
		uint64_t ns = mmath::splitmix64(std::rand());;
		m_noiceData->seed = ns;
		spiralData.seed = ns;
	}
	//scope butons

	auto& ssui = staticSelectorUInt[cViewGen::vNoice];
	auto& ssf = staticSelector[cViewGen::vNoice];
	switch (current_View_Generator) {
	case cViewGen::vNoice: // noice case 
		if (ssui["OCTAVES"]->isValueChanged()) {
			m_noiceData->octaves = ssui["OCTAVES"]->getValue();
		}
		if (ssf["FREQUENCY"]->isValueChanged()) {
			m_noiceData->frequency = ssf["FREQUENCY"]->getValue();
		}
		if (ssf["PERSISTENCE"]->isValueChanged()) {
			m_noiceData->persistence = ssf["PERSISTENCE"]->getValue();
		}
		if (ssf["AMPLIFIRE"]->isValueChanged()) {
			m_noiceData->amplifire = ssf["AMPLIFIRE"]->getValue();
		}
		if (IGUILayout[cViewGen::vNoice]["G_NOICE"]->isPressed() && getKeytime()) {
			m_NoiceViewer->generateNoice();
		}

		m_NoiceViewer->setNoiceData(m_noiceData);
		break;
	case cViewGen::vLSystem: // tree case
		if (IGUILayout[cViewGen::vLSystem]["G_TREE"]->isPressed()) {
			myLS->generate();
			saveTreeAsImage(*IstateData->sd_Window.lock());
		}
		break;
	case cViewGen::vSpiral:
		if (IGUILayout[cViewGen::vSpiral]["G_SPIRAL"]->isPressed() && getKeytime()) {
			spiralModel->regenerateSpiral();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_GALX_RAD"]->isValueChanged()) {
			spiralData.galaxyRadius = staticSelector[cViewGen::vSpiral]["SPR_GALX_RAD"]->getValue();
		}
		if (staticSelectorUInt[cViewGen::vSpiral]["SPR_ARMS"]->isValueChanged()) {
			spiralData.spiralArms = staticSelectorUInt[cViewGen::vSpiral]["SPR_ARMS"]->getValue();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_ARMS_CURVE"]->isValueChanged()) {
			spiralData.spiralArmCurvature = staticSelector[cViewGen::vSpiral]["SPR_ARMS_CURVE"]->getValue();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_CORE_RAD"]->isValueChanged()) {
			spiralData.CoreRadius = staticSelector[cViewGen::vSpiral]["SPR_CORE_RAD"]->getValue();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_CORE_BRNTH"]->isValueChanged()) {
			spiralData.CoreBrightness = staticSelector[cViewGen::vSpiral]["SPR_CORE_BRNTH"]->getValue();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_DENS_DUST"]->isValueChanged()) {
			spiralData.DustDensity = staticSelector[cViewGen::vSpiral]["SPR_DENS_DUST"]->getValue();
		}
		if (staticSelector[cViewGen::vSpiral]["SPR_DENS_GAS"]->isValueChanged()) {
			spiralData.GasDensity = staticSelector[cViewGen::vSpiral]["SPR_DENS_GAS"]->getValue();
		}
		if (staticSelectorUInt[cViewGen::vSpiral]["SPR_STAR_COUNT"]->isValueChanged()) {
			spiralData.starCount = staticSelectorUInt[cViewGen::vSpiral]["SPR_STAR_COUNT"]->getValue();
		}
		if (staticSelectorUInt[cViewGen::vSpiral]["SPR_ARM_LEN"]->isValueChanged()) {
			spiralData.spiralArmCount = staticSelectorUInt[cViewGen::vSpiral]["SPR_ARM_LEN"]->getValue();
		}
		break;
	default: // default case
		break;
	}
	selector->update(delta_time, mouseF);
	m_noiceData->smoothMode = selector->getActiveElementID();
}

void EditorState::updateSounds(const float& delta_time) {}

void EditorState::update(const float& delta_time) {
	// update keytime for next function used it for keypress delay
	updateKeytime(delta_time);
	updateInput(delta_time);
	updateMousePositions(&IView);

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

	for (auto& it : staticSelector[current_View_Generator])
		target.draw(*it.second);

	for (auto& it : staticSelectorUInt[current_View_Generator])
		target.draw(*it.second);

	for (auto& it : IGUILayout[cViewGen::vAll])
		target.draw(*it.second);
	for (auto& it : IGUILayout[current_View_Generator])
		target.draw(*it.second);

	if (current_View_Generator == cViewGen::vNoice)
		selector->render(target);
}

void EditorState::render(sf::RenderWindow& target) {
	// layer 0 - math models (noice, trees, etc)

	IRenderTexture.clear();
	IRenderTexture.setView(IView);

	switch (current_View_Generator) {
	case cViewGen::vAll: break; // cannot contain any generators in "all layout" 
	case cViewGen::vNoice: // call noice render
		if (m_NoiceViewer != nullptr)
			m_NoiceViewer->render(IRenderTexture);
		break;
	case cViewGen::vLSystem: // call tree render
		if (myLS != nullptr)
			myLS->render(IRenderTexture);
		break;
	case cViewGen::vSpiral:
		IRenderTexture.draw(*spiralModel);
		break;
	default:
		break;
	}

	IRenderTexture.setView(IRenderTexture.getDefaultView());
	// layer 1 - tab menu render
	if (showTabmenu)
		renderTabMenu(IRenderTexture);

	// layer 2 - debug text render
	// render debug text
	if (Idebud)
		IRenderTexture.draw(Itext);


	IRenderTexture.display();
	target.draw(IRenderSprite);
}
