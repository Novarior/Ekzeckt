#include "EditorState.hpp"
#include "../core/tools/MemoryUsageMonitor.hpp"
#include "../core/tools/staticFPSMetter.hpp"
#include "../localisation/helperText.hpp"
#include "../math/mymath.hpp"

void EditorState::initKeybinds()
{
    IKeyBinds.lock()->at("CLOSE") = this->IKeySupports.lock()->at("Escape");
    IKeyBinds.lock()->at("TAB_MENU") = this->IKeySupports.lock()->at("Tab");
    IKeyBinds.lock()->at("KEY_Q") = this->IKeySupports.lock()->at("Q");
    IKeyBinds.lock()->at("KEY_W") = this->IKeySupports.lock()->at("W");
    IKeyBinds.lock()->at("KEY_E") = this->IKeySupports.lock()->at("E");
    IKeyBinds.lock()->at("KEY_R") = this->IKeySupports.lock()->at("R");
    IKeyBinds.lock()->at("KEY_SLASH") = IKeySupports.lock()->at("Slash");
}

void EditorState::initTabMenu()
{ // tab menu
    this->tabShape.setPosition(sf::Vector2f(mmath::p2pX(70, this->IstateData->sd_Window.lock()->getSize().x), 0));
    this->tabShape.setSize(sf::Vector2f(mmath::p2pX(30, this->IstateData->sd_Window.lock()->getSize().x), this->IstateData->sd_Window.lock()->getSize().y));
    // half transparent gray
    this->tabShape.setFillColor(sf::Color(150, 150, 150, 200));
    this->tabShape.setOutlineThickness(5.f);
    this->tabShape.setOutlineColor(sf::Color(100, 100, 100, 192));
    this->showTabmenu = false;
}

void EditorState::initButtons()
{ // init buttons
    this->buttons["G_NOICE"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x, this->tabShape.getPosition().y + mmath::p2pX(90, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sd_Window.lock()->getSize().y)),
        "Gen Noice", gui::styles::buttons::btn_editor, gui::type::BUTTON);

    this->buttons["G_TREE"] = new gui::Button(
        sf::Vector2f(this->tabShape.getPosition().x + this->tabShape.getSize().x / 2, this->tabShape.getPosition().y + mmath::p2pX(90, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(this->tabShape.getSize().x / 2, mmath::p2pX(10, this->IstateData->sd_Window.lock()->getSize().y)),
        "Gen Tree", gui::styles::buttons::btn_editor, gui::type::BUTTON);

    this->buttons["SAVE_GENDATA"] = new gui::Button(
        sf::Vector2f(
            this->tabShape.getPosition().x,
            this->tabShape.getPosition().y +
                mmath::p2pX(80, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x / 2,
            mmath::p2pX(10, this->IstateData->sd_Window.lock()->getSize().y)),
        "Save", gui::styles::buttons::btn_editor, gui::type::BUTTON);

    this->buttons["LOAD_GENDATA"] = new gui::Button(
        sf::Vector2f(
            this->tabShape.getPosition().x + this->tabShape.getSize().x / 2,
            this->tabShape.getPosition().y +
                mmath::p2pX(80, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x / 2,
            mmath::p2pX(10, this->IstateData->sd_Window.lock()->getSize().y)),
        "Load", gui::styles::buttons::btn_editor, gui::type::BUTTON);
}

void EditorState::initSelectors()
{ // init static selector in tab menu
    this->staticSelector["OCTAVES"] = new gui::StaticSelector(
        sf::Vector2f(this->tabShape.getPosition()),
        sf::Vector2f(
            this->tabShape.getSize().x,
            mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        this->IstateData->sd_GameFont_basic,
        this->IstateData->sd_characterSize_game_big, 0, 10, 1.f, true,
        "Octaves: ");

    this->staticSelector["FREQUENCY"] = new gui::StaticSelector(
        sf::Vector2f(
            this->tabShape.getPosition().x,
            this->tabShape.getPosition().y +
                mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x,
            mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        this->IstateData->sd_GameFont_basic,
        this->IstateData->sd_characterSize_game_big, 0, 10, 0.1f, true,
        "Frequency: ");

    this->staticSelector["PERSISTENCE"] = new gui::StaticSelector(
        sf::Vector2f(
            this->tabShape.getPosition().x,
            this->tabShape.getPosition().y +
                mmath::p2pX(14, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x,
            mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        this->IstateData->sd_GameFont_basic,
        this->IstateData->sd_characterSize_game_big, 0, 5, 0.1f, true,
        "Persistence: ");

    this->staticSelector["AMPLIFIRE"] = new gui::StaticSelector(
        sf::Vector2f(
            this->tabShape.getPosition().x,
            this->tabShape.getPosition().y +
                mmath::p2pX(21, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x,
            mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        this->IstateData->sd_GameFont_basic,
        this->IstateData->sd_characterSize_game_big, 0, 10, 0.1f, true,
        "Amplifire: ");

    std::vector<std::string> list = {"Linear", "Cosine", "Cubic", "Quintic",
                                     "Quartic", "Quadratic", "Hermite"};

    this->selector = new gui::Selector(
        sf::Vector2f(
            this->tabShape.getPosition().x,
            this->tabShape.getPosition().y +
                mmath::p2pX(28, this->IstateData->sd_Window.lock()->getSize().y)),
        sf::Vector2f(
            this->tabShape.getSize().x,
            mmath::p2pX(7, this->IstateData->sd_Window.lock()->getSize().y)),
        this->IstateData->sd_GameFont_basic,
        this->IstateData->sd_characterSize_game_big, list.data(), list.size(), 0);

    // set default value for static selector
    this->staticSelector["OCTAVES"]->setCurrentValue(
        this->m_NoiceViewer->getNoiceData().octaves);
    this->staticSelector["FREQUENCY"]->setCurrentValue(
        this->m_NoiceViewer->getNoiceData().frequency);
    this->staticSelector["AMPLIFIRE"]->setCurrentValue(
        this->m_NoiceViewer->getNoiceData().amplifire);
    this->staticSelector["PERSISTENCE"]->setCurrentValue(
        this->m_NoiceViewer->getNoiceData().persistence);
}

void EditorState::initNoice()
{
    this->m_noiceData.octaves = 8;
    std::srand(std::time(nullptr));
    this->m_noiceData.seed = std::rand();
    this->m_noiceData.frequency = 8;
    this->m_noiceData.amplifire = 1;
    this->m_noiceData.persistence = 0.6f;

    this->m_noiceData.gridSize = this->IstateData->sd_gridSize;
    this->m_noiceData.RenderWindowX =
        this->IstateData->sd_gfxSettings.lock()->resolution.size.x;
    this->m_noiceData.RenderWindowY =
        this->IstateData->sd_gfxSettings.lock()->resolution.size.y;
    this->m_noiceData.mapSizeX =
        this->IstateData->sd_gfxSettings.lock()->resolution.size.x;
    this->m_noiceData.mapSizeY =
        this->IstateData->sd_gfxSettings.lock()->resolution.size.y;
    this->m_noiceData.smoothMode = 0;

    // init data for noice viewer
    this->m_NoiceViewer = new NoiceViewer(this->m_noiceData);
    this->m_NoiceViewer->generateNoice();
}

void EditorState::initDebugText()
{ // init debug text
    this->Itext.setFont(this->IstateData->sd_debugFont);
    this->Itext.setCharacterSize(this->IstateData->sd_characterSize_debug);
    this->Itext.setPosition(sf::Vector2f(0, 0));
    this->Itext.setFillColor(sf::Color::White);
    this->Itext.setOutlineColor(sf::Color::Black);
    this->Itext.setOutlineThickness(2.f);
}

EditorState::EditorState(StateData *statedata) : State(statedata)
{
    // init logger
    Logger::logStatic("Start initilization EditorState",
                      "EditorState::EditorState()");
    // init keybinds
    this->initKeybinds();
    this->initTabMenu();
    this->initButtons();
    this->initNoice();
    this->initSelectors();
    this->initDebugText();

    // init LSystem
    this->myLS = new LSystem();
    this->myLS->setRule('d', "qd");
    this->myLS->setRule('s', "d[[-qqs]qs]+qqs[+q|]-q|");
    this->myLS->setOffsetPos(
        sf::Vector2f(this->IstateData->sd_Window.lock()->getSize().x / 2,
                     this->IstateData->sd_Window.lock()->getSize().y * 0.90));
    this->myLS->generate();

    Logger::logStatic("End initilization EditorState",
                      "EditorState::EditorState()");
}

EditorState::~EditorState()
{
    Logger::logStatic("Start destruction EditorState",
                      "EditorState::~EditorState()");

    // FIXME: add save noice data to file
    // ParserJson::saveNoiceData(this->m_NoiceViewer->getNoiceData());

    for (auto &it : this->buttons)
        delete it.second;

    for (auto &it : this->staticSelector)
        delete it.second;

    delete this->m_NoiceViewer;

    delete this->selector;

    delete this->myLS;
}

sf::IntRect EditorState::findNonTransparentRect(const sf::Image &image)
{
    // this function find non transparent pixels
    // and return IntRect without this pixels
    sf::Vector2u size = image.getSize();
    sf::Rect<unsigned> mrect({size.x, size.y}, {0, 0});

    for (unsigned int x = 0; x < size.x; x++)
        for (unsigned int y = 0; y < size.y; y++)
            if (image.getPixel({x, y}) != sf::Color::Transparent)
            {
                if (x < mrect.position.x)
                    mrect.position.x = x;
                if (y < mrect.position.y)
                    mrect.position.y = y;
                if (x > mrect.size.x)
                    mrect.size.x = x;
                if (y > mrect.size.y)
                    mrect.size.y = y;
            }

    return sf::Rect<int>(mrect);
}

void EditorState::saveTreeAsImage(sf::RenderWindow &window)
{
    // create texture with window size
    sf::Texture texture(sf::Vector2u(window.getSize().x, window.getSize().y));

    // get array shape
    std::vector<sf::RectangleShape> shapes;
    shapes.insert(shapes.end(), this->myLS->internalArray(),
                  this->myLS->internalArray() + this->myLS->getSizeArray());

    // Очищаем окно и рисуем все фигуры на текстуре
    window.clear(sf::Color::Transparent);
    for (auto &it : shapes)
        window.draw(it);

    // update
    texture.update(window);

    // get snapshoot
    sf::Image image = texture.copyToImage();

    // find Transparent pixels
    sf::IntRect mrect = findNonTransparentRect(image);

    // create newe image on mrect base
    sf::Image simg(sf::Vector2u(mrect.size.x - mrect.position.x,
                                mrect.size.y - mrect.position.y),
                   sf::Color::Black);

    // copy pixels from original image
    for (unsigned int x = mrect.position.x; x < mrect.size.x; x++)
        for (unsigned int y = mrect.position.y; y < mrect.size.x; y++)
            simg.setPixel(sf::Vector2u(x - mrect.position.x, y - mrect.position.y),
                          image.getPixel({x, y}));

    // create name for image file
    // add time to name for unique name
    std::stringstream ss;
    ss << ApplicationsFunctions::getDocumentsAppFolder() << "/tree/"
       << std::to_string(std::time(nullptr)) << ".png";

    // save image
    if (!simg.saveToFile(ss.str()))
        Logger::logStatic("Image" + ss.str() + " has be corrupt and dosent saved!",
                          "EditorState::saveTreeAsImage()", logType::ERROR);
}

void EditorState::updateInput(const float &delta_time)
{
    // if pressed key ESC then end state
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("CLOSE"))) &&
        this->getKeytime())
        this->endState();

    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("KEY_SLASH"))) &&
        this->getKeytime())
        this->Idebud = !this->Idebud;

    // switch tab menu
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("TAB_MENU"))) &&
        this->getKeytime())
        this->showTabmenu = !this->showTabmenu;

    // update currentViewGenerator in a range from 0 to 2
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("KEY_Q"))) &&
        this->getKeytime())
        this->m_NoiceViewer->swithNoiceModel();

    // switch noice model
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("KEY_W"))) &&
        this->getKeytime())
        this->m_NoiceViewer->swithColorMode();

    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("KEY_E"))) &&
        this->getKeytime())
    {
        if (this->current_View_Generator < 2)
            this->current_View_Generator++;
        else
            this->current_View_Generator = 0;
    }
    // switch noice smooth mode (fast mode)
    if (sf::Keyboard::isKeyPressed(
            sf::Keyboard::Scancode(IKeyBinds.lock()->at("KEY_R"))) &&
        this->getKeytime())
        this->m_noiceData.fastMode = !this->m_noiceData.fastMode;
}

void EditorState::updateDebugText(const float &delta_time)
{
    // collect all data for debug text and update it
    double fps = 1.0f / delta_time;
    this->IstringStream << "FPS:\t" << fps << "\nCurrent memory usage:\t"
                        << MemoryUsageMonitor::formatMemoryUsage(
                               MemoryUsageMonitor::getCurrentMemoryUsage())
                        << "Navigation:\n\t\t['/'] Togle info menu"
                        << "\n\t\t['Q'] Switch Noice generator"
                        << "\n\t\t['W'] Switch color mode"
                        << "\n\t\t['E'] Change current viewport of generators"
                        << "\n\t\t['R'] switch fast mode noices (not simplex)"
                        << "\nCurent view generator:\t"
                        << this->current_View_Generator
                        << "\nCurent noice view mode:\t"
                        << this->m_NoiceViewer->getNoiceModelName() << ":\t"
                        << this->m_NoiceViewer->getNoiceModel()
                        << "\nCurent noice color mode:\t"
                        << this->m_NoiceViewer->getColorModeName() << ":\t"
                        << this->m_NoiceViewer->getColorMode();
    if (this->m_NoiceViewer->getNoiceModel() == noiceType::PERLIN_NOICE_V2)
        this->IstringStream << "\nCurent noice smooth mode:\t"
                            << this->m_NoiceViewer->getNoiceSmouthName() << ":\t"
                            << this->m_NoiceViewer->getNoiceData().smoothMode
                            << "\nSeed:\t"
                            << this->m_NoiceViewer->getNoiceData().seed
                            << "\nFastMode"
                            << this->m_NoiceViewer->getNoiceData().fastMode
                            << "\nHeigth on Cursor: "
                            << this->m_NoiceViewer->getHeightMap(
                                   this->ImousePosWindow);
    this->IstringStream << "\nTree Data:"
                        << "\n\tTreeSize:\t" << this->myLS->getSizeTree()
                        << "\n\tTreeAxiom\t" << this->myLS->getAxiomSize()
                        << "\nPause:\t" << this->Ipaused;

    // update debug text
    this->Itext.setString(this->IstringStream.str());
    // clear string stream
    this->IstringStream.str("");
}

void EditorState::updateButtons(const float &delta_time)
{
    for (auto &it : this->buttons)
        it.second->update(this->ImousePosWindow);

    for (auto &it : this->staticSelector)
        it.second->update(delta_time, this->ImousePosWindow);

    this->selector->update(delta_time, this->ImousePosWindow);

    // update buttons using switch case for each button
    switch (this->current_View_Generator)
    {
    case 0: // noice case
        if (this->staticSelector["OCTAVES"]->isValueChanged())
        {
            this->m_noiceData.octaves =
                this->staticSelector["OCTAVES"]->getCurrentValue();
            this->staticSelector["OCTAVES"]->closeChangeValue();
        }
        if (this->staticSelector["FREQUENCY"]->isValueChanged())
        {
            this->m_noiceData.frequency =
                this->staticSelector["FREQUENCY"]->getCurrentValue();
            this->staticSelector["FREQUENCY"]->closeChangeValue();
        }
        if (this->staticSelector["PERSISTENCE"]->isValueChanged())
        {
            this->m_noiceData.persistence =
                this->staticSelector["PERSISTENCE"]->getCurrentValue();
            this->staticSelector["PERSISTENCE"]->closeChangeValue();
        }
        if (this->staticSelector["AMPLIFIRE"]->isValueChanged())
        {
            this->m_noiceData.amplifire =
                this->staticSelector["AMPLIFIRE"]->getCurrentValue();
            this->staticSelector["AMPLIFIRE"]->closeChangeValue();
        }
        if (this->buttons["G_NOICE"]->isPressed())
        {
            this->m_NoiceViewer->generateNoice();
        }
        if (this->buttons["SAVE_GENDATA"]->isPressed())
        {
            // fixme: add save noice data to file
        }
        if (this->buttons["LOAD_GENDATA"]->isPressed())
        {
            // fixme: add load noice data from file
            this->staticSelector["OCTAVES"]->setCurrentValue(
                this->m_noiceData.octaves);
            this->staticSelector["FREQUENCY"]->setCurrentValue(
                this->m_noiceData.frequency);
            this->staticSelector["AMPLIFIRE"]->setCurrentValue(
                this->m_noiceData.amplifire);
            this->staticSelector["PERSISTENCE"]->setCurrentValue(
                this->m_noiceData.persistence);
            this->selector->setActiveElement(this->m_noiceData.smoothMode);
        }
        this->m_NoiceViewer->setNoiceData(this->m_noiceData);
        break;
    case 1: // tree case
        if (this->buttons["G_TREE"]->isPressed())
        {
            this->myLS->generate();
            this->saveTreeAsImage(*this->IstateData->sd_Window.lock());
        }
        break;
    default: // default case
        break;
    }
    this->selector->update(delta_time, this->ImousePosWindow);
    this->m_noiceData.smoothMode = this->selector->getActiveElementID();
}

void EditorState::updateSounds(const float &delta_time) {}

void EditorState::update(const float &delta_time)
{
    // update keytime for next function used it for keypress delay
    this->updateKeytime(delta_time);
    this->updateInput(delta_time);
    this->updateMousePositions();

    this->myLS->update(delta_time);
    // if tab menu is open then update buttons
    if (this->showTabmenu)
        this->updateButtons(delta_time);

    // update debug text
    if (this->Idebud)
        this->updateDebugText(delta_time);
}

void EditorState::renderTabMenu(sf::RenderTarget &target)
{
    target.draw(this->tabShape);

    for (auto &it : this->staticSelector)
        it.second->render(target);

    for (auto &it : this->buttons)
        target.draw(*it.second);

    this->selector->render(target);
}

void EditorState::render(sf::RenderWindow &target)
{
    // layer 0 - noice render and tree render
    switch (this->current_View_Generator)
    {
    case 0: // call noice render
        if (this->m_NoiceViewer != nullptr)
            this->m_NoiceViewer->render(target);
        break;
    case 1: // call tree render
        if (this->myLS != nullptr)
            this->myLS->render(target);
        break;
    default:
        break;
    }
    // layer 1 - tab menu render
    if (this->showTabmenu)
        this->renderTabMenu(target);

    // layer 2 - debug text render
    // render debug text
    if (this->Idebud)
        target.draw(this->Itext);
}
