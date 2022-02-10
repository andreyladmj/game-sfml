#ifndef TANKS_HITBOXCOMPONENT_HPP
#define TANKS_HITBOXCOMPONENT_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"


class HitboxComponent {
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    sf::FloatRect nextPosition;

    float offsetX, offsetY;

public:
    HitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);
    virtual ~HitboxComponent();

    const sf::Vector2f &getPosition() const;
    const sf::FloatRect getGlobalBounds() const;
    const sf::FloatRect &getNextPosition(const sf::Vector2f &velocity);


    void setPosition(const sf::Vector2f &position);
    void setPosition(const float x, const float y);

    bool intersects(const sf::FloatRect &frect);

    void update();
    void render(sf::RenderTarget &target);
};


#endif //TANKS_HITBOXCOMPONENT_HPP
