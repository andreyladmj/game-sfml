#include "MovementComponent.hpp"

MovementComponent::MovementComponent(sf::Sprite &sprite,
     float maxVelocity, float acceleration, float deceleration)
     : sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration) {

    this->radianVelocity = 0;
}

MovementComponent::~MovementComponent() {

}

const sf::Vector2f &MovementComponent::getVelocity() const {
    return this->velocity;
}

const bool MovementComponent::idle() const {
    return this->velocity.x == 0.f && this->velocity.y == 0.f;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float &dt) {
    this->sprite.setRotation(this->sprite.getRotation() + dir_x);
    this->radianVelocity += this->acceleration * dir_y;
//    float angle = (this->sprite.getRotation()) * PI / 180;
//    this->velocity.x += this->acceleration * dir_y * sin((this->sprite.getRotation() - 90) * PI / 180);
//    this->velocity.y += this->acceleration * dir_y * cos((this->sprite.getRotation() - 90) * PI / 180);
//    this->velocity.x += this->acceleration * dir_y * cos(angle);
//    this->velocity.y += this->acceleration * dir_y * sin(angle);

}

void MovementComponent::update(const float &dt) {

    if (this->radianVelocity > 0.f) {
        if (this->radianVelocity > this->maxVelocity)
            this->radianVelocity = this->maxVelocity;

        this->radianVelocity -= this->deceleration;

        if (this->radianVelocity < 0.f)
            this->radianVelocity = 0.f;

    } else if (this->radianVelocity < 0.f) {
        if (this->radianVelocity < -this->maxVelocity)
            this->radianVelocity = -this->maxVelocity;

        this->radianVelocity += this->deceleration;

        if (this->radianVelocity > 0.f)
            this->radianVelocity = 0.f;
    }

    float angle = (this->sprite.getRotation() + 90) * PI / 180;
//    this->velocity.x += this->acceleration * dir_y * sin((this->sprite.getRotation() - 90) * PI / 180);
//    this->velocity.y += this->acceleration * dir_y * cos((this->sprite.getRotation() - 90) * PI / 180);

    this->velocity.x = this->radianVelocity * cos(angle);
    this->velocity.y = this->radianVelocity * sin(angle);

    this->sprite.move(this->getVelocity() * dt);
}

void MovementComponent::update2(const float &dt) {

    if (this->velocity.x > 0.f) {
        if (this->velocity.x > this->maxVelocity)
            this->velocity.x = this->maxVelocity;

        this->velocity.x -= this->deceleration;

        if (this->velocity.x < 0.f)
            this->velocity.x = 0;

    } else if (this->velocity.x < 0.f) {
        if (this->velocity.x < -this->maxVelocity)
            this->velocity.x = -this->maxVelocity;

        this->velocity.x += this->deceleration;

        if (this->velocity.x > 0.f)
            this->velocity.x = 0;
    }

    if (this->velocity.y > 0.f) {
        if (this->velocity.y > this->maxVelocity) {
            this->velocity.y = this->maxVelocity;
        }

        this->velocity.y -= this->deceleration;

        if (this->velocity.y < 0.f)
            this->velocity.y = 0;

    } else if (this->velocity.y < 0.f) {
        if (this->velocity.y < -this->maxVelocity) {
            this->velocity.y = -this->maxVelocity;
        }

        this->velocity.y += this->deceleration;

        if (this->velocity.y > 0.f)
            this->velocity.y = 0;
    }

    this->sprite.move(this->getVelocity() * dt);
}
