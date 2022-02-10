#include "Game.hpp"

void Game::initVariables() {
    this->window = nullptr;
    this->dt = 0.f;
    this->gridSize = 75.f;
}

void Game::initGraphicsSettings() {
    gfxSettings.setPathToFile("../Config/window.ini");
    gfxSettings.loadFromFile();
}

void Game::initStateData() {
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->gfxSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initWindow() {
    if (this->gfxSettings.fullscreen)
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Fullscreen, this->gfxSettings.contextSettings);
    else
        this->window = new sf::RenderWindow(this->gfxSettings.resolution, this->gfxSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gfxSettings.contextSettings);

    this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->gfxSettings.verticalSync);
}

void Game::initStates() {
    this->states.push(new MainMenuState(&this->stateData));
}

void Game::initKeys() {
    this->supportedKeys["Escape"] = sf::Keyboard::Key::Escape;
    this->supportedKeys["A"] = sf::Keyboard::Key::A;
    this->supportedKeys["D"] = sf::Keyboard::Key::D;
    this->supportedKeys["W"] = sf::Keyboard::Key::W;
    this->supportedKeys["S"] = sf::Keyboard::Key::S;
    this->supportedKeys["Q"] = sf::Keyboard::Key::Q;
    this->supportedKeys["E"] = sf::Keyboard::Key::E;
    this->supportedKeys["F"] = sf::Keyboard::Key::F;
    this->supportedKeys["Left"] = sf::Keyboard::Key::Left;
    this->supportedKeys["Right"] = sf::Keyboard::Key::Right;
    this->supportedKeys["Up"] = sf::Keyboard::Key::Up;
    this->supportedKeys["Down"] = sf::Keyboard::Key::Down;
    this->supportedKeys["Space"] = sf::Keyboard::Key::Space;
}

Game::Game() {
    this->initVariables();
    this->initGraphicsSettings();
    this->initWindow();
    this->initStateData();
    this->initKeys();
    this->initStates();
}
Game::~Game() {
    delete this->window;

    while (!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

// functions

void Game::endApplication() {

}

void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)) {

        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();

    }
}

void Game::update() {
    this->updateSFMLEvents();


    if (!this->states.empty()) {
//        if (this->window->hasFocus()) {
        this->states.top()->update(this->dt);

        if (this->states.top()->getQuit()) {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
//        }
    } else {
        // close game if all states was closed
        this->endApplication();
        this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    if (!this->states.empty()) {
        this->states.top()->render();
    }

    this->window->display();
}

void Game::run() {
    while(this->window->isOpen()) {
        this->updateDt();
        this->update();
        this->render();
    }
}
