#ifndef TANKS_ANIMATIONCOMPONENT_HPP
#define TANKS_ANIMATIONCOMPONENT_HPP

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class AnimationComponent {
private:
    class Animation {
    public:
        sf::Sprite &sprite;
        sf::Texture &textureSheet;
        float animationTimer;
        float timer;
        int width, height;
        sf::IntRect startRect;
        sf::IntRect currentRect;
        sf::IntRect endRect;

        Animation(sf::Sprite &sprite, sf::Texture &texture_sheet, float animation_timer,
                  int start_frame_x, int start_frame_y, int frames_x, int frames_y, int width, int height):
                sprite(sprite), textureSheet(texture_sheet) {
            this->timer = 0.f;
            this->animationTimer = animation_timer;
            this->width = width;
            this->height = height;
            this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height, width, height);
            this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

            this->currentRect = this->startRect;
            this->sprite.setTexture(this->textureSheet, true);
            this->sprite.setTextureRect(this->startRect);
        };

        void play(const float &dt) {
            this->timer += 100.f * dt;
            if (this->timer >= this->animationTimer) {
                this->timer = 0.f;

                if (this->currentRect != this->endRect) {
                    this->currentRect.left += this->width;
                } else {
                    this->currentRect.left = this->startRect.left;
                }

                this->sprite.setTextureRect(this->currentRect);
            }
        }
        void reset() {
            this->timer = this->animationTimer;
            this->currentRect = this->startRect;
        }
    };

    sf::Sprite &sprite;
    sf::Texture &textureSheet;

    std::map<std::string, Animation*> animations;

public:
    AnimationComponent(sf::Sprite &sprite, sf::Texture &texture_sheet);
    virtual ~AnimationComponent();

    void addAnimation(const std::string key, float animation_timer, int start_frame_x, int start_frame_y,
                      int frames_x, int frames_y, int width, int height);
    void play(const std::string key, const float &dt);

};


#endif //TANKS_ANIMATIONCOMPONENT_HPP
