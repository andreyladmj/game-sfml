#include "SettingsState.hpp"

SettingsState::SettingsState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initGui();
    this->initText();
}

SettingsState::~SettingsState() {
    for (auto & button : this->buttons)
        delete button.second;

    for (auto & element : this->dropDownList)
        delete element.second;
}

void SettingsState::initVariables() {
    this->modes = sf::VideoMode::getFullscreenModes();
}

void SettingsState::initBackground() {
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    this->backgroundTexture.loadFromFile("../resources/images/backgrounds/settings.jpeg");

    this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts() {
    if (!this->font.loadFromFile("../fonts/28 Days Later.ttf")) {
        throw("COULD NOT LOAD FONTS");
    }
}

void SettingsState::initKeybinds() {
    std::ifstream ifs("../Config/keybinds.ini");

    if (ifs.is_open()) {
        std::string key = "";
        std::string key2 = "";

        while(ifs >> key >> key2) {
            this->keybinds[key] = this->supportedKeys->at(key2);
        }
    }

    ifs.close();
}

void SettingsState::initGui() {
    sf::Color idle = sf::Color(70, 70, 70, 200);
    sf::Color hover = sf::Color(150, 150, 150, 255);
    sf::Color pressed = sf::Color(70, 70, 70, 255);

    this->buttons["BACK"] = new gui::Button(100, 900, 250, 100, &this->font, "Back", idle, hover, pressed);
    this->buttons["APPLY"] = new gui::Button(1500, 900, 250, 100, &this->font, "Apply", idle, hover, pressed);

    std::vector<std::string> modes_str;
    for (auto &i: this->modes) {
        modes_str.push_back(std::to_string(i.width) + "x" + std::to_string(i.height));
    }
    this->dropDownList["RESOLUTION"] = new gui::DropDownList(500, 100, 250, 100, font, modes_str.data(), modes_str.size());
}

void SettingsState::initText() {
    this->optionsTest.setFont(this->font);
    this->optionsTest.setPosition(100.f, 100.f);
    this->optionsTest.setCharacterSize(64);
    this->optionsTest.setFillColor(sf::Color(200,200,200,200));

    this->optionsTest.setString(
        "Resolution \n\nFullscreen \n\nVsync \n\nAntialiasing \n\n"
    );
}

void SettingsState::updateGui(const float &dt) {
    for (auto &it: this->buttons) {
        it.second->update(this->mousePosWindow);
    }
    for (auto &it: this->dropDownList) {
        it.second->update(this->mousePosWindow, dt);
    }

    if (this->buttons["BACK"]->isPressed()) {
        this->endState();
    }

    if (this->buttons["APPLY"]->isPressed()) {
        this->stateData->gfxSettings->resolution = this->modes[this->dropDownList["RESOLUTION"]->getActiveElementId()];
        this->stateData->gfxSettings->safeToFile();
        this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title, sf::Style::Default);
    }
}

void SettingsState::updatePlayerInput(const float &dt) {
//    this->checkForQuit();
}

void SettingsState::update(const float &dt) {
    this->updateMousePosition();
    this->updatePlayerInput(dt);
    this->updateGui(dt);

}

void SettingsState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderGui(*target);

    target->draw(this->optionsTest);
}

void SettingsState::renderGui(sf::RenderTarget &target) {
    for (auto &it: this->buttons) {
        it.second->render(target);
    }
    for (auto &it: this->dropDownList) {
        it.second->render(target);
    }
}