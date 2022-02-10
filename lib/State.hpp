#ifndef TANKS_STATE_HPP
#define TANKS_STATE_HPP

#include "../entities/Player.hpp"
#include "../gui-components/gui.hpp"
#include "GraphicsSettings.hpp"

class State;


class StateData {
public:
    StateData() {};

    float gridSize;
    sf::RenderWindow *window;
    GraphicsSettings *gfxSettings;
    std::map<std::string, int>* supportedKeys;
    std::stack<State*>* states;
};


class State {
protected:
    StateData *stateData;
    std::stack<State*>* states;

    sf::RenderWindow *window;
    std::map<std::string, int>* supportedKeys;
    std::map<std::string, int> keybinds;
    bool quit;
    bool pause = false;
    float keyTime, keyTimeMax;
    float gridSize;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    sf::Vector2u mousePosGrid;

    std::map<std::string, sf::Texture> textures;

    virtual void initKeybinds() = 0;

public:
    State(StateData *state_data);
    virtual ~State();
    const bool getKeyTime();

    const bool& getQuit() const;
    void pauseState();
    void unpauseState();
    virtual void endState(); // called before delete state

    // pure virtual functions
    // it has to be defined in inherited classes
    virtual void updateMousePosition(sf::View *view = nullptr);
    virtual void updateKeyTime(const float &dt);
    virtual void updatePlayerInput(const float& dt) = 0;
    virtual void update(const float& dt) = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
};


#endif //TANKS_STATE_HPP
