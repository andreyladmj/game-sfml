#ifndef TANKS_GUI_HPP
#define TANKS_GUI_HPP

#include <math.h>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

enum button_states{BTN_IDLE = 0, BTN_HOVER, BTN_PRESSED};

namespace gui {
    class Button {
    private:
        short unsigned button_state;
        short unsigned id;

        sf::RectangleShape shape;
        sf::Font *font;
        sf::Text text;

        sf::Color idleColor;
        sf::Color hoverColor;
        sf::Color activeColor;

    public:
        Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, short unsigned id=0, int characterSize=56);
        virtual ~Button();

        const bool isPressed() const;
        const std::string getText() const;
        const short unsigned &getId() const;

        void setText(const std::string text);
        void setId(const short unsigned id);

        void update(const sf::Vector2i &mousePosWindow);
        void render(sf::RenderTarget &target);
    };

    class DropDownList {
    private:
        float keyTime, keyTimeMax;

        sf::Font &font;
        gui::Button *activeElement;
        std::vector<gui::Button*> list;
        bool showList;

    public:
        DropDownList(float x, float y, float width, float height, sf::Font &font, std::string list[], unsigned nrOfElements, unsigned default_index = 0);
        virtual ~DropDownList();

        const short unsigned &getActiveElementId() const;

        const bool getKeyTime();
        void updateKeyTime(const float &dt);
        void update(const sf::Vector2i &mousePosWindow, const float &dt);
        void render(sf::RenderTarget &target);
    };

    class TextureSelector {
        sf::RectangleShape bound;
        sf::RectangleShape sheet;
        sf::RectangleShape selector;
        sf::Vector2u mousePosGrid;
        sf::IntRect textureRect;

        bool hidden;
        gui::Button *hide_btn;

        float gridSizeX, gridSizeY;
        int nXTiles, nYTiles;
        float originalTileSize, scaleX, scaleY;
        bool active;

    public:
        TextureSelector(float x, float y, float width, float height, int nXTiles, int nYTiles, float originalTileSize, const sf::Texture *texture_sheet, sf::Font &font);
        ~TextureSelector();

        const bool &getActive() const;
        const sf::IntRect &getTextureRect() const;

        void update(const sf::Vector2i &mousePosWindow);
        void render(sf::RenderTarget &target);
    };
}


#endif //TANKS_GUI_HPP
