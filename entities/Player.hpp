#ifndef TANKS_PLAYER_HPP
#define TANKS_PLAYER_HPP


#include "Entity.hpp"

class Player: public Entity {
private:
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture &texture_sheet);
    virtual ~Player();

    virtual void update(const float& dt);
};


#endif //TANKS_PLAYER_HPP
