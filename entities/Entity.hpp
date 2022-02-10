#ifndef TANKS_ENTITY_HPP
#define TANKS_ENTITY_HPP

#include "../components/HitboxComponent.hpp"
#include "../components/MovementComponent.hpp"
#include "../components/AnimationComponent.hpp"

class Entity {
private:
    void initVariables();

protected:
    sf::Sprite sprite;

    HitboxComponent *hitboxComponent;
    MovementComponent *movementComponent;
    AnimationComponent *animationComponent;

public:
    Entity();
    virtual ~Entity();

    void setTexture(sf::Texture &texture);
    void createHitboxComponent(sf::Sprite &sprite, float offset_x, float offset_y, float width, float height);
    void createMovementComponent(float maxVelocity, float acceleration, float deceleration);
    void createAnimationComponent(sf::Texture &texture_sheet);

    virtual const sf::Vector2f &getPosition() const;
    virtual const sf::FloatRect getGlobalBounds() const;

//    bool HitboxComponent::intersects(const sf::FloatRect &frect) {
//        return this->hitbox.getGlobalBounds().intersects(frect);
//    }
    // Functions
    virtual void setPosition(const float x, const float y);
    virtual void move(const float dir_x, const float dir_y, const float& dt);
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget &target);
};


#endif //TANKS_ENTITY_HPP
