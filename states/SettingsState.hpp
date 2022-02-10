#ifndef TANKS_SETTINGSSTATE_HPP
#define TANKS_SETTINGSSTATE_HPP

#include "../lib/State.hpp"
#include "../lib/GraphicsSettings.hpp"

class SettingsState: public State {
private:
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;
    std::map<std::string, gui::DropDownList*> dropDownList;

    sf::Text optionsTest;

    std::vector<sf::VideoMode> modes;

protected:
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

public:
    SettingsState(StateData *state_data);
    virtual ~SettingsState();

//    void endState();
    void updatePlayerInput(const float& dt);
    void updateGui(const float &dt);
    void update(const float& dt);
    void renderGui(sf::RenderTarget &target);
    void render(sf::RenderTarget *target = nullptr);
};


#endif //TANKS_SETTINGSSTATE_HPP
