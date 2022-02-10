#include "EditorState.hpp"

EditorState::EditorState(StateData *state_data) : State(state_data) {
    this->initVariables();
    this->initView();
    this->initBackground();
    this->initFonts();
    this->initTexts();
    this->initKeybinds();
    this->initTileMap();
    this->initPauseMenu(window);
    this->initButtons();
    this->initGui();
}

EditorState::~EditorState() {
    for (auto &it: this->buttons) {
        delete it.second;
    }
    delete this->pmenu;
    delete this->tileMap;
    delete this->textureSelector;
}

void EditorState::initVariables() {
    this->collision = false;
    this->type = TileTypes::DEFAULT;

//    this->textureRect = sf::IntRect(0, 0, static_cast<int>(this->stateData->gridSize), static_cast<int>(this->stateData->gridSize));
    this->textureRect = sf::IntRect(0, 0, this->tileSize, this->tileSize);
}

void EditorState::initView() {
    this->view.setSize(sf::Vector2f(this->stateData->gfxSettings->resolution.width, this->stateData->gfxSettings->resolution.height));
    this->view.setCenter(this->stateData->gfxSettings->resolution.width / 2.f, this->stateData->gfxSettings->resolution.height / 2.f);
}


void EditorState::initBackground() {
}

void EditorState::initGui() {
    this->sidebar.setSize(sf::Vector2f(
            140,
            static_cast<float>(this->stateData->gfxSettings->resolution.height)
            ));
    this->sidebar.setFillColor(sf::Color(50,50,50,100));
    this->sidebar.setOutlineThickness(1.f);
    this->sidebar.setOutlineColor(sf::Color::White);

    this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
    this->selectorRect.setFillColor(sf::Color(255,255,255,150));
    this->selectorRect.setOutlineThickness(1.f);
    this->selectorRect.setOutlineColor(sf::Color::Cyan);

    this->selectorRect.setTexture(this->tileMap->getTileSheet());
    this->selectorRect.setTextureRect(this->textureRect);

    // 626x659
    this->textureSelector = new gui::TextureSelector(120.f, 20.f, 1500.f, 1500.f, 19, 20, 32.f, this->tileMap->getTileSheet(), this->font);
}

void EditorState::initFonts() {
    if (!this->font.loadFromFile("../fonts/28 Days Later.ttf")) {
        throw("COULD NOT LOAD FONTS");
    }
}

void EditorState::initTexts() {
    this->cursorText.setPosition(this->mousePosView.x, this->mousePosView.y - 50.f);
    this->cursorText.setFont(this->font);
    this->cursorText.setCharacterSize(12);
    std::stringstream ss;
    ss << this->mousePosView.x << ", " << this->mousePosView.y << "\n" << this->textureRect.left << " " << this->textureRect.top;
    this->cursorText.setString(ss.str());
}

void EditorState::initKeybinds() {
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

void EditorState::initPauseMenu(sf::RenderWindow *window) {
    this->pmenu = new PauseMenu(*window, this->font);
    this->pmenu->addButton("RESUME_GAME", 0, 0, "Resume");
    this->pmenu->addButton("SAVE", 0, 150, "SAVE");
    this->pmenu->addButton("LOAD", 0, 300, "LOAD");
    this->pmenu->addButton("QUIT", 0, 450, "Quit");
}

void EditorState::initButtons() {
}

void EditorState::initTileMap() {
    this->tileMap = new TileMap(this->stateData->gridSize, 256, 256, "../resources/sprites/03125630010daeacd577b7aae6dc964e.png");
}

void EditorState::endState() {
    this->quit = true;
}

void EditorState::updatePlayerInput(const float &dt) {
}

void EditorState::updateInput(const float &dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeyTime()) {
        if(!this->pause) {
            this->pauseState();
        } else {
            this->unpauseState();
        }
    }
}

void EditorState::updateEditorInput(const float &dt) {
    float cameraSpeed = 1000.f * dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->view.move(cameraSpeed, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->view.move(-cameraSpeed, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        this->view.move(0.f, -cameraSpeed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        this->view.move(0.f, cameraSpeed);


    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosView))) {
            if (!this->textureSelector->getActive()) {
                this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
            } else {
                this->textureRect = this->textureSelector->getTextureRect();
            }
        }

    } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

        if (!this->sidebar.getGlobalBounds().contains(sf::Vector2f(this->mousePosView))) {
            if (!this->textureSelector->getActive()) {
                this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
            }
        }
    }
}

void EditorState::updatePauseMenuButtons(const float &dt) {
    if (this->pmenu->isButtonPressed("RESUME_GAME")) {
        this->unpauseState();
    }
    if (this->pmenu->isButtonPressed("QUIT")) {
        this->endState();
    }
    if (this->pmenu->isButtonPressed("SAVE") && this->getKeyTime()) {
        this->tileMap->saveToFile("../resources/maps/map1.ini");
        this->unpauseState();
    }
    if (this->pmenu->isButtonPressed("LOAD") && this->getKeyTime()) {
        this->tileMap->loadFromFile("../resources/maps/map1.ini");
        this->unpauseState();
    }
}

void EditorState::updateButtons() {
    for (auto &it: this->buttons) {
        it.second->update(this->mousePosWindow);
    }
}

void EditorState::updateGui() {
    if (!this->textureSelector->getActive()) {
        this->selectorRect.setTextureRect(this->textureRect);
        this->selectorRect.setPosition(this->mousePosGrid.x * this->stateData->gridSize, this->mousePosGrid.y * this->stateData->gridSize);
    }

    this->textureSelector->update(this->mousePosWindow);
}

void EditorState::update(const float &dt) {
    this->updateMousePosition(&this->view);
    this->updateKeyTime(dt);
    this->updateInput(dt);

    if (!this->pause) {
        this->updateButtons();
        this->updatePlayerInput(dt);
        this->updateGui();
        this->updateEditorInput(dt);
    } else {
        this->pmenu->update(this->mousePosWindow);
        this->updatePauseMenuButtons(dt);
    }
}

void EditorState::renderButtons(sf::RenderTarget &target) {
    for (auto &it: this->buttons) {
        it.second->render(target);
    }
}

void EditorState::renderGui(sf::RenderTarget &target) {
    if (!this->textureSelector->getActive()) {
        target.setView(this->view);
        target.draw(this->selectorRect);
    }
    target.setView(this->window->getDefaultView());
    this->textureSelector->render(target);
    target.draw(this->sidebar);
}

void EditorState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;

    target->setView(this->view);
    this->tileMap->render(*target);

    target->setView(this->window->getDefaultView());

    if (this->pause) {
        target->setView(this->window->getDefaultView());
        this->pmenu->render(*target);
    } else {
        this->renderButtons(*target);
        this->renderGui(*target);
    }
}