#include "Entity.hpp"

Entity::Entity() {
    this->initVariables();
}

Entity::~Entity() {
    if (this->movementComponent)
        delete this->movementComponent;

    if (this->animationComponent)
        delete this->animationComponent;

    if (this->hitboxComponent)
        delete this->hitboxComponent;
}

void Entity::initVariables() {
    this->hitboxComponent = nullptr;
    this->movementComponent = nullptr;
    this->animationComponent = nullptr;
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height) {
    this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(float maxVelocity, float acceleration, float deceleration) {
    this->movementComponent = new MovementComponent(this->sprite, maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture &texture_sheet) {
    this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::setTexture(sf::Texture &texture) {
    this->sprite.setTexture(texture);
    this->sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

const sf::Vector2f &Entity::getPosition() const {
    if (this->hitboxComponent) {
        return this->hitboxComponent->getPosition();
    }
    return this->sprite.getPosition();
}

const sf::FloatRect Entity::getGlobalBounds() const {
    if (this->hitboxComponent) {
        return this->hitboxComponent->getGlobalBounds();
    }
    return this->sprite.getGlobalBounds();
}

void Entity::setPosition(const float x, const float y) {
    if (this->hitboxComponent) {
        this->hitboxComponent->setPosition(x, y);
    } else {
        this->sprite.setPosition(x, y);
    }
}


void Entity::move(const float dir_x, const float dir_y, const float& dt) {
    if (this->movementComponent) {
        this->movementComponent->move(dir_x, dir_y, dt);
    }
}

void Entity::update(const float& dt) {
//    if (this->movementComponent)
//        this->movementComponent->update(dt);
}

void Entity::render(sf::RenderTarget &target) {
    target.draw(this->sprite);

    if (this->hitboxComponent) {
        this->hitboxComponent->render(target);
    }
}
