#ifndef TANKS_GAME_HPP
#define TANKS_GAME_HPP
#include "State.hpp"
#include "../states/GameState.hpp"
#include "../states/MainMenuState.hpp"
#include "GraphicsSettings.hpp"


class Game {
private:
    GraphicsSettings gfxSettings;
    StateData stateData;
    sf::RenderWindow *window;
    sf::Event sfEvent;

    sf::Clock dtClock;
    float dt;
    float gridSize;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    void initVariables();
    void initStateData();
    void initGraphicsSettings();
    void initWindow();
    void initStates();
    void initKeys();

public:
    Game();
    virtual ~Game();

    void endApplication();

    // Functions
    void updateDt();
    void updateSFMLEvents();
    void update();
    void render();
    void run();
};


#endif //TANKS_GAME_HPP
