#include "PauseMenu.hpp"

PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font): font(font) {
    this->background.setSize(sf::Vector2f(window.getSize()));
    this->background.setFillColor(sf::Color(20,20,20,100));

    this->container.setSize(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y - 60.f));
    this->container.setFillColor(sf::Color(20,20,20,200));
    this->container.setPosition(window.getSize().x / 2.f - this->container.getSize().x / 2.f, 30.f);

    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color(255, 255, 255, 200));
    this->text.setCharacterSize(60);
    this->text.setString("Paused");
    this->text.setPosition(
            this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
            this->container.getPosition().y + 20.f);
}

PauseMenu::~PauseMenu() {
    for (auto &it: this->buttons) {
        delete it.second;
    }
}

std::map<std::string, gui::Button *> &PauseMenu::getButtons() {
    return this->buttons;
}

void PauseMenu::addButton(const std::string key, float x, float y, const std::string text) {
    sf::Color idle(70, 70, 70, 200);
    sf::Color hover(150, 150, 150, 255);
    sf::Color pressed(70, 70, 70, 255);
    float margin_x = 150.f;
    float offset_x = this->container.getPosition().x + margin_x;
    float width = this->container.getSize().x - margin_x * 2;
    this->buttons[key] = new gui::Button(x + offset_x, y + 200.f, width, 100, &this->font, text, idle, hover, pressed);
}

const bool PauseMenu::isButtonPressed(const std::string key) {
    return this->buttons[key]->isPressed();
}

void PauseMenu::update(const sf::Vector2i &mousePosWindow) {
    for (auto &it: this->buttons) {
        it.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget &target) {
    target.draw(this->background);
    target.draw(this->container);
    target.draw(this->text);

    for (auto &it: this->buttons) {
        it.second->render(target);
    }
}
