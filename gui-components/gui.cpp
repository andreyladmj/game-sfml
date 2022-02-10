#include <iostream>
#include "gui.hpp"

gui::Button::Button(float x, float y, float width, float height, sf::Font *font, std::string text, sf::Color idleColor,
               sf::Color hoverColor, sf::Color activeColor, short unsigned id, int characterSize) {

    this->button_state = BTN_IDLE;
    this->id = id;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(characterSize);
    this->text.setPosition(
            this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
            this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
            );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

gui::Button::~Button() {

}

void gui::Button::update(const sf::Vector2i &mousePosWindow) {
    this->button_state = BTN_IDLE;

    if (this->shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
        this->button_state = BTN_HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->button_state = BTN_PRESSED;
        }
    }

    switch (this->button_state) {
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVER:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_PRESSED:
            this->shape.setFillColor(this->activeColor);
            break;
    }
}

void gui::Button::render(sf::RenderTarget &target) {
    target.draw(this->shape);
    target.draw(this->text);
}

const bool gui::Button::isPressed() const {
    return this->button_state == BTN_PRESSED;
}

const std::string gui::Button::getText() const {
    return this->text.getString();
}

const short unsigned &gui::Button::getId() const {
    return this->id;
}

void gui::Button::setText(const std::string text) {
    this->text.setString(text);
}

void gui::Button::setId(const unsigned short id) {
    this->id = id;
}

// ================================================ DropDownList ================================================

gui::DropDownList::DropDownList(float x, float y, float width, float height, sf::Font &font, std::string list[],
                                unsigned nrOfElements, unsigned default_index):
    font(font), showList(false) {

    this->keyTimeMax = 1.f;
    this->keyTime = 0.f;

    sf::Color idle(70, 70, 70, 200);
    sf::Color hover(150, 150, 150, 255);
    sf::Color pressed(70, 70, 70, 255);

//    unsigned nrOfElements = sizeof(list) / sizeof(std::string);
    this->activeElement = new Button(x, y, width, height, &this->font, list[default_index], idle, hover, pressed);

    for (size_t i = 0; i< nrOfElements; ++i) {
        this->list.push_back(new Button(x, y + (i+1)*height, width, height, &this->font, list[i], idle, hover, pressed, i));
    }

}

gui::DropDownList::~DropDownList() {
    delete this->activeElement;
    for (int i=0;i<this->list.size(); ++i) {
        delete this->list[i];
    }
//    for (auto &i: this->list)
//        delete i;
}

const bool gui::DropDownList::getKeyTime() {
    if (this->keyTime >= this->keyTimeMax) {
        this->keyTime = 0.f;
        return true;
    }

    return false;
}

void gui::DropDownList::updateKeyTime(const float &dt) {
    if (this->keyTime < this->keyTimeMax)
        this->keyTime += 10.f * dt;
}

const short unsigned &gui::DropDownList::getActiveElementId() const {
    return this->activeElement->getId();
}

void gui::DropDownList::update(const sf::Vector2i &mousePosWindow, const float &dt) {
    this->updateKeyTime(dt);

    this->activeElement->update(mousePosWindow);

    if (this->activeElement->isPressed() && this->getKeyTime()) {
        this->showList = !this->showList;
    }

    if (this->showList) {
        for (auto &i: this->list) {
            i->update(mousePosWindow);

            if (i->isPressed() && this->getKeyTime()) {
                this->showList = false;
                this->activeElement->setText(i->getText());
                this->activeElement->setId(i->getId());
            }
        }
    }


}

void gui::DropDownList::render(sf::RenderTarget &target) {
    if (this->showList) {
        for (auto &i: this->list) {
            i->render(target);
        }
    }

    this->activeElement->render(target);
}



// ================================================ TextureSelector ================================================

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, int nXTiles, int nYTiles, float originalTileSize, const sf::Texture *texture_sheet, sf::Font &font) {
    this->originalTileSize = originalTileSize;
    this->nXTiles = nXTiles;
    this->nYTiles = nYTiles;
    this->gridSizeX = width / this->nXTiles;
    this->gridSizeY = height / this->nYTiles;
    this->active = false;
    this->hidden = false;
    this->scaleX = this->gridSizeX / this->originalTileSize;
    this->scaleY = this->gridSizeY / this->originalTileSize;

    this->bound.setSize(sf::Vector2f(width, height));
    this->bound.setPosition(x, y);
    this->bound.setFillColor(sf::Color(50, 50, 50, 100));
    this->bound.setOutlineThickness(1.f);
    this->bound.setOutlineColor(sf::Color(255, 255, 255, 200));

    this->sheet.setTexture(texture_sheet);
    this->sheet.setPosition(x, y);
    this->sheet.setSize(sf::Vector2f(width, height));

    if (this->sheet.getGlobalBounds().width > this->bound.getGlobalBounds().width) {
        this->sheet.setTextureRect(sf::IntRect(0,0, this->bound.getGlobalBounds().width, this->sheet.getGlobalBounds().height));
    }
    if (this->sheet.getGlobalBounds().height > this->bound.getGlobalBounds().height) {
        this->sheet.setTextureRect(sf::IntRect(0,0, this->sheet.getGlobalBounds().width, this->bound.getGlobalBounds().height));
    }

    this->selector.setPosition(x, y);
    this->selector.setSize(sf::Vector2f(this->gridSizeX, this->gridSizeY));
    this->selector.setFillColor(sf::Color::Transparent);
    this->selector.setOutlineThickness(1.f);
    this->selector.setOutlineColor(sf::Color::White);

    this->textureRect.width = static_cast<int>(this->gridSizeX / this->scaleX);
    this->textureRect.height = static_cast<int>(this->gridSizeY / this->scaleY);

    sf::Color idle = sf::Color(70, 70, 70, 200);
    sf::Color hover = sf::Color(150, 150, 150, 255);
    sf::Color pressed = sf::Color(70, 70, 70, 255);
    this->hide_btn = new gui::Button(x - 100, y, 100, 50, &font, "TS", idle, hover, pressed, 0, 20);
}

gui::TextureSelector::~TextureSelector() {
    delete this->hide_btn;
}

const bool &gui::TextureSelector::getActive() const {
    return this->active;
}

const sf::IntRect &gui::TextureSelector::getTextureRect() const {
    std::cout << "this->textureRect: " << this->textureRect.left << ", " << this->textureRect.top << ", width: " << this->textureRect.width << "\n";
    return this->textureRect;
}

void gui::TextureSelector::update(const sf::Vector2i &mousePosWindow) {
    this->hide_btn->update(mousePosWindow);

    if (this->hide_btn->isPressed()) {
        this->hidden = !this->hidden;
        sf::sleep(sf::milliseconds(300));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
        this->hidden = !this->hidden;
        this->active = !this->active;
        sf::sleep(sf::milliseconds(300));
    }

    if (!this->hidden) {
        if (this->bound.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow))) {
            this->active = true;
        } else {
            this->active = false;
        }

        if (this->active) {
            this->mousePosGrid.x = ((mousePosWindow.x - static_cast<int>(this->bound.getPosition().x)) / static_cast<unsigned>(this->gridSizeX));
            this->mousePosGrid.y = ((mousePosWindow.y - static_cast<int>(this->bound.getPosition().y)) / static_cast<unsigned>(this->gridSizeY));

            this->selector.setPosition(
                    this->bound.getPosition().x + this->mousePosGrid.x * this->gridSizeX,
                    this->bound.getPosition().y + this->mousePosGrid.y * this->gridSizeY
            );

            this->textureRect.left = static_cast<int>((this->selector.getPosition().x - this->bound.getPosition().x) / this->scaleX);
            this->textureRect.top = static_cast<int>((this->selector.getPosition().y - this->bound.getPosition().y) / this->scaleY);

            int ix = ceil(this->textureRect.left / this->originalTileSize);
            int iy = ceil(this->textureRect.top / this->originalTileSize);
            this->textureRect.left = ix * this->originalTileSize + ix * 1;
            this->textureRect.top = iy * this->originalTileSize + iy * 1;
//            std::cout << "this->selector.getPosition().x: " << this->selector.getPosition().x << "\n";
//            std::cout << "this->selector.getPosition().x: " << this->selector.getPosition().x << "\n";
//            std::cout << "this->textureRect.left: " << this->textureRect.left << "\n";
        }
    }
}

void gui::TextureSelector::render(sf::RenderTarget &target) {
    if (!this->hidden) {
        target.draw(this->bound);
        target.draw(this->sheet);
        target.draw(this->selector);
    }

    this->hide_btn->render(target);
}