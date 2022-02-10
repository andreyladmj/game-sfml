#include "GameState.hpp"

GameState::GameState(StateData *state_data): State(state_data) {
    this->initDeferredRender();
    this->initView();
    this->initKeybinds();
    this->initFonts();
    this->initTextures();
    this->initPauseMenu(window);
    this->initPlayers();
    this->initTileMap();
}

GameState::~GameState() {
    delete this->player;
    delete this->pmenu;
    delete this->tileMap;
}

void GameState::initDeferredRender() {
    this->renderTexture.create(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    this->renderSprite.setTextureRect(sf::IntRect(0,0,this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
}

void GameState::initView() {
    this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
    this->view.setCenter(this->stateData->gfxSettings->resolution.width / 2.f, this->stateData->gfxSettings->resolution.height / 2.f);
}

void GameState::initFonts() {
    if (!this->font.loadFromFile("../fonts/28 Days Later.ttf")) {
        throw("COULD NOT LOAD FONTS");
    }
}

void GameState::initKeybinds() {
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

void GameState::initTextures() {
    if (!this->textures["PLAYER_IDLE"].loadFromFile("../resources/sprites/tanks/E-100_1.png"))
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";

    if (!this->textures["FIRE_HEAVY_GUN_1"].loadFromFile("../resources/sprites/fires/fire-heavy-gun.png"))
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";

    if (!this->textures["EXPLOSION"].loadFromFile("../resources/sprites/explosions/nuke-ani.gif"))
        throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";

//    this->sprite.setTexture(this->textures["EXPLOSION"]);
//    this->sprite.setPosition(500, 500);
}

void GameState::initPauseMenu(sf::RenderWindow *window) {
    this->pmenu = new PauseMenu(*window, this->font);
    this->pmenu->addButton("RESUME_GAME", 0, 0, "Resume");
    this->pmenu->addButton("QUIT", 0, 150, "Quit");
}

void GameState::initPlayers() {
    this->player = new Player(500, 500, this->textures["PLAYER_IDLE"]);
}
void GameState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 256, 256, "../resources/sprites/03125630010daeacd577b7aae6dc964e.png");
    this->tileMap->loadFromFile("../resources/maps/map1.ini");
}

void GameState::updatePlayerInput(const float &dt) {
    float dir_x = 0.f;
    float dir_y = 0.f;

    // update player input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TURN_LEFT")))) {
        dir_x = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("TURN_RIGHT")))) {
        dir_x = 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_FORWARD")))) {
        dir_y = -1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_BACKWARD")))) {
        dir_y = 1.0f;
    }

    this->player->move(dir_x, dir_y, dt);
}

void GameState::updateView(const float &dt) {
    this->view.setCenter(floor(this->player->getPosition().x), floor(this->player->getPosition().y));
}

void GameState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
        if(!this->pause) {
            this->pauseState();
        } else {
            this->unpauseState();
        }
    }
}

void GameState::updatePauseMenuButtons() {
    if (this->pmenu->isButtonPressed("RESUME_GAME")) {
        this->unpauseState();
    }
    if (this->pmenu->isButtonPressed("QUIT")) {
        this->endState();
    }
}

void GameState::updateTileMap(const float& dt) {
    this->tileMap->update();
    this->tileMap->updateCollision(this->player);
}

void GameState::update(const float &dt) {
    this->updateMousePosition(&this->view);
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if (!this->pause) {
        this->updateView(dt);
        this->updatePlayerInput(dt);
        this->player->update(dt);
        this->updateTileMap(dt);
    } else {
        this->pmenu->update(static_cast<sf::Vector2i>(this->mousePosView));
        this->updatePauseMenuButtons();
    }
}

void GameState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;

    // CLEAR
    this->renderTexture.clear();

    this->renderTexture.setView(this->view);
    this->tileMap->render(this->renderTexture);

    this->player->render(this->renderTexture);

    if (this->pause) {
        this->renderTexture.setView(this->renderTexture.getDefaultView());
        this->pmenu->render(this->renderTexture);
    }

//    this->renderTexture.draw(this->sprite);

    // FINAL RENDER
    this->renderTexture.display();
    this->renderSprite.setTexture(this->renderTexture.getTexture());
    target->draw(this->renderSprite);
}

