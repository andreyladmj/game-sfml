#ifndef TANKS_EDITORSTATE_HPP
#define TANKS_EDITORSTATE_HPP

#include "../lib/State.hpp"
#include "../GUI/PauseMenu.hpp"
#include "../Map/TileMap.hpp"

class EditorState : public State {
private:
    sf::View view;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu *pmenu;
    std::map<std::string, gui::Button*> buttons;

    gui::TextureSelector *textureSelector;
    sf::RectangleShape sidebar;

    TileMap *tileMap;
    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;

    int tileSize = 32;
    int nTileX = 17;
    int nTileY = 16;

    bool collision;
    short type;

protected:
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initTexts();
    void initKeybinds();
    void initPauseMenu(sf::RenderWindow *window);
    void initButtons();
    void initGui();
    void initTileMap();

public:
    EditorState(StateData *state_data);
    virtual ~EditorState();

    void endState();
    void updatePlayerInput(const float& dt);
    void updateInput(const float &dt);
    void updateEditorInput(const float &dt);
    void updatePauseMenuButtons(const float& dt);
    void updateButtons();
    void updateGui();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget &target);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};


#endif //TANKS_EDITORSTATE_HPP
