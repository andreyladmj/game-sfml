#ifndef TANKS_MOVEMENTCOMPONENT_HPP
#define TANKS_MOVEMENTCOMPONENT_HPP

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <vector>
#include <math.h>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

const float PI = 3.14159265358979323846264;

class MovementComponent {
private:
    sf::Sprite &sprite;

    float maxVelocity;
    float acceleration;
    float deceleration;

    float radianVelocity;
    sf::Vector2f velocity;

public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity, float acceleration, float deceleration);
    virtual ~MovementComponent();

    const sf::Vector2f &getVelocity() const;

    const bool idle() const;

    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);
    void update2(const float &dt);
};


#endif //TANKS_MOVEMENTCOMPONENT_HPP
