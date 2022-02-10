#include "State.hpp"

State::State(StateData *state_data) {
    this->stateData = state_data;
    this->window = this->stateData->window;
    this->states = this->stateData->states;
    this->supportedKeys = this->stateData->supportedKeys;
    this->gridSize = this->stateData->gridSize;
    this->quit = false;
    this->keyTime = 0.f;
    this->keyTimeMax = 10.f;
}

State::~State() {

}

const bool &State::getQuit() const {
    return this->quit;
}

void State::pauseState() {
    this->pause = true;
}

void State::unpauseState() {
    this->pause = false;
}

void State::updateMousePosition(sf::View *view) {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);

    if (view != nullptr) {
        this->window->setView(*view);
    }

    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
    this->mousePosGrid = sf::Vector2u(
            static_cast<unsigned>(this->mousePosView.x) / static_cast<unsigned>(this->gridSize),
            static_cast<unsigned>(this->mousePosView.y) / static_cast<unsigned>(this->gridSize)
            );

    this->window->setView(this->window->getDefaultView());
}

const bool State::getKeyTime() {
    if (this->keyTime >= this->keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }

    return false;
}

void State::updateKeyTime(const float &dt) {
    if (this->keyTime < this->keyTimeMax) {
        this->keyTime += 10.f * dt;
    }
}

void State::endState() {
    this->quit = true;
}
