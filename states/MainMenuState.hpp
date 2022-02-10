#ifndef TANKS_GAMEMENUSTATE_HPP
#define TANKS_GAMEMENUSTATE_HPP

#include "../lib/State.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"
#include "GameState.hpp"
#include "../lib/GraphicsSettings.hpp"

class MainMenuState : public State {
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

protected:
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(StateData *state_data);
    virtual ~MainMenuState();

    void endState();
    void updatePlayerInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButtons(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};


#endif //TANKS_GAMEMENUSTATE_HPP
