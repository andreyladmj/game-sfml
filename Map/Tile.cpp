#include <iostream>
#include "Tile.hpp"

Tile::Tile() {
    this->collision = false;
    this->type = 0;
}

Tile::Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture &texture, const sf::IntRect &texture_rect,
           bool collision, short type) {
    this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
//    this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
    this->shape.setTexture(&texture);
    this->shape.setTextureRect(texture_rect);

    this->collision = collision;
    this->type = type;
}

Tile::~Tile() {

}

const bool & Tile::getCollision() const {
    return this->collision;
}

const std::string Tile::getAsString() const {
    std::stringstream ss;
    ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " ";
    ss << this->collision << " " << this->type;
    return ss.str();
}

const sf::Vector2f &Tile::getPosition() const {
    return this->shape.getPosition();
}

sf::Vector2f Tile::getSize() {
    return this->shape.getSize();
}

void Tile::update() {

}

void Tile::render(sf::RenderTarget &target) {
    target.draw(this->shape);
}
