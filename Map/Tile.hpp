#ifndef TANKS_TILE_HPP
#define TANKS_TILE_HPP

#include <sstream>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

enum TileTypes {
    DEFAULT = 0,
    OBSTACLE,
};

class Tile {
protected:
    sf::RectangleShape shape;
    bool collision;
    short type;

public:
    Tile();
    Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect,
         bool collision = false, short type = TileTypes::DEFAULT);
    virtual ~Tile();

    const bool &getCollision() const;

    const std::string getAsString() const;
    const sf::Vector2f &getPosition() const;
    sf::Vector2f getSize();

    void update();
    void render(sf::RenderTarget &target);
};


#endif //TANKS_TILE_HPP
