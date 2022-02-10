#ifndef TANKS_PAUSEMENU_HPP
#define TANKS_PAUSEMENU_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"
#include "../gui-components/gui.hpp"

class PauseMenu {
private:
    sf::Font &font;
    sf::Text text;
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, gui::Button*> buttons;

public:
    PauseMenu(sf::RenderWindow &window, sf::Font &font);
    virtual ~PauseMenu();

    std::map<std::string, gui::Button*> &getButtons();

    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float x, float y, const std::string text);
    void update(const sf::Vector2i &mousePosWindow);
    void render(sf::RenderTarget &target);
};


#endif //TANKS_PAUSEMENU_HPP
