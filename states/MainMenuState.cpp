#include "MainMenuState.hpp"

MainMenuState::MainMenuState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initBackground();
    this->initFonts();
    this->initKeybinds();
    this->initButtons();
}

MainMenuState::~MainMenuState() {
    for (auto &it: this->buttons) {
        delete it.second;
    }
}

void MainMenuState::initVariables() {
}

void MainMenuState::initBackground() {
    this->background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));

    this->backgroundTexture.loadFromFile("../resources/images/backgrounds/main-menu.jpeg");

    this->background.setTexture(&this->backgroundTexture);
}

void MainMenuState::initFonts() {
    if (!this->font.loadFromFile("../fonts/28 Days Later.ttf")) {
        throw("COULD NOT LOAD FONTS");
    }
}

void MainMenuState::initKeybinds() {
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

void MainMenuState::initButtons() {
    sf::Color idle = sf::Color(70, 70, 70, 200);
    sf::Color hover = sf::Color(150, 150, 150, 255);
    sf::Color pressed = sf::Color(70, 70, 70, 255);

    this->buttons["GAME_STATE"] = new gui::Button(100, 100, 250, 100, &this->font, "New Game", idle, hover, pressed);
    this->buttons["SETTINGS_STATE"] = new gui::Button(100, 300, 250, 100, &this->font, "Settings", idle, hover, pressed);
    this->buttons["EDITOR_STATE"] = new gui::Button(100, 500, 250, 100, &this->font, "Editor", idle, hover, pressed);
    this->buttons["QUIT_STATE"] = new gui::Button(100, 700, 250, 100, &this->font, "Quit", idle, hover, pressed);

}

void MainMenuState::endState() {
    this->quit = true;
}

void MainMenuState::updatePlayerInput(const float &dt) {
//    this->checkForQuit();
}

void MainMenuState::updateButtons() {
    for (auto &it: this->buttons) {
        it.second->update(this->mousePosWindow);
    }

    if (this->buttons["GAME_STATE"]->isPressed()) {
        this->states->push(new GameState(this->stateData));
    }

    if (this->buttons["SETTINGS_STATE"]->isPressed()) {
        this->states->push(new SettingsState(this->stateData));
    }

    if (this->buttons["EDITOR_STATE"]->isPressed()) {
        this->states->push(new EditorState(this->stateData));
    }

    if (this->buttons["QUIT_STATE"]->isPressed()) {
        this->endState();
    }
}

void MainMenuState::update(const float &dt) {
    this->updateMousePosition();
    this->updatePlayerInput(dt);
    this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;

    target->draw(this->background);

    this->renderButtons(*target);
}

void MainMenuState::renderButtons(sf::RenderTarget &target) {
    for (auto &it: this->buttons) {
        it.second->render(target);
    }
}
