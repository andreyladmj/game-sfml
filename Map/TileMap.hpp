#ifndef TANKS_TILEMAP_HPP
#define TANKS_TILEMAP_HPP

#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

#include "Tile.hpp"
#include "../entities/Entity.hpp"

class TileMap {
private:
    float gridSizeF;
    unsigned gridSizeU;
    unsigned layers;
    std::string textureFile;
    sf::Vector2u maxSizeWorldGrid;
    sf::Vector2f maxSizeWorld;
    std::vector<std::vector<std::vector<Tile*>>> map;
    sf::Texture tileSheet;

    sf::RectangleShape collisionBox;

    void clear();

    unsigned fromX;
    unsigned toX;
    unsigned fromY;
    unsigned toY;

protected:
public:
    TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file);
    virtual ~TileMap();

    const sf::Texture *getTileSheet() const;

    void update();
    void render(sf::RenderTarget &target);

    void saveToFile(std::string filename);
    void loadFromFile(std::string filename);

    void updateCollision(Entity* entity);

    void addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect);
    void removeTile(const unsigned x, const unsigned y, const unsigned z);
};


#endif //TANKS_TILEMAP_HPP
