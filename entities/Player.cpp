#include "Player.hpp"

Player::Player(float x, float y, sf::Texture &texture_sheet) {
    this->initVariables();
    this->setTexture(texture_sheet);
    this->setPosition(x, y);

//    texture_sheet.set
//    this->sprite->se

//    this->initComponents();
//    this->createHitboxComponent(this->sprite, 0.f, 0.f, this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
    this->createHitboxComponent(this->sprite, 0.f, 0.f, texture_sheet.getSize().x, texture_sheet.getSize().y);
    this->createMovementComponent(250.f, 15.f, 3.f);
//    this->createAnimationComponent(texture_sheet);
//    this->animationComponent->addAnimation("IDLE_LEFT", 5.f, 0, 0, 23, 0, 67, 171);
}

Player::~Player() {

}

void Player::initVariables() {

}

void Player::initComponents() {
}

void Player::update(const float &dt) {
//    Entity::update(dt);
    this->hitboxComponent->update();
    this->movementComponent->update(dt);

    if (this->animationComponent) {
        this->animationComponent->play("IDLE_LEFT", dt);
    }
}
