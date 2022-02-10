#ifndef TANKS_GAMESTATE_HPP
#define TANKS_GAMESTATE_HPP

#include "../lib/State.hpp"
#include "../GUI/PauseMenu.hpp"
#include "../Map/TileMap.hpp"
#include <math.h>

class GameState: public State {
private:
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    PauseMenu *pmenu;
    Entity *player;

    TileMap *tileMap;

    sf::Sprite sprite;

protected:
    void initDeferredRender();
    void initView();
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initPauseMenu(sf::RenderWindow *window);
    void initPlayers();
    void initTileMap();

public:
    GameState(StateData *state_data);
    virtual ~GameState();

    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget *target = nullptr);
};


#endif //TANKS_GAMESTATE_HPP
