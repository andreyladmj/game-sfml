#include "TileMap.hpp"

void TileMap::clear() {
    for (int i=0; i<this->maxSizeWorldGrid.x; ++i) {
        for (int j=0; j<this->maxSizeWorldGrid.y; j++) {
            for(int l=0; l<this->layers; ++l) {
                if (this->map[i][j][l] != nullptr) {
                    delete this->map[i][j][l];
                    this->map[i][j][l] = nullptr;
                }
            }
            this->map[i][j].clear();
        }
        this->map[i].clear();
    }

    this->map.clear();
}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file) {
    std::cout << "gridSize: " << gridSize << "\n";
    this->gridSizeF = gridSize;
    this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
    this->maxSizeWorldGrid.x = width;
    this->maxSizeWorldGrid.y = height;
    this->maxSizeWorld.x = static_cast<float>(width) * this->gridSizeF;
    this->maxSizeWorld.y = static_cast<float>(height) * this->gridSizeF;
    this->layers = 1;
    this->textureFile = texture_file;

    this->map.resize(this->maxSizeWorldGrid.x,std::vector<std::vector<Tile*>>());
    for (int i=0; i<this->maxSizeWorldGrid.x; ++i) {
        for (int j=0; j<this->maxSizeWorldGrid.y; j++) {
            this->map[i].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
            for(int l=0; l<this->layers; ++l) {
                this->map[i][j].resize(this->layers, nullptr);
            }
        }
    }

    this->tileSheet.loadFromFile(this->textureFile);
    this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
    this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
    this->collisionBox.setOutlineThickness(1.f);
    this->collisionBox.setOutlineColor(sf::Color(255, 0, 0, 150));
}

TileMap::~TileMap() {
    this->clear();
}

const sf::Texture *TileMap::getTileSheet() const {
    return &this->tileSheet;
}

void TileMap::update() {

}

void TileMap::render(sf::RenderTarget &target) {
    for (auto &x: this->map) {
        for (auto &y: x) {
            for (auto *z: y) {
                if (z != nullptr) {
                    z->render(target);

                    if (z->getCollision()) {
                        this->collisionBox.setPosition(z->getPosition());
                        target.draw(this->collisionBox);
                    }
                }
            }
        }
    }
}

void TileMap::updateCollision(Entity *entity) {
    if (entity->getPosition().x < 0.f) {
        entity->setPosition(0.f, entity->getPosition().y);
    } else if (entity->getPosition().x + entity->getGlobalBounds().width > this->maxSizeWorld.x) {
        entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
    }

    if (entity->getPosition().y < 0.f) {
        entity->setPosition(entity->getPosition().x, 0.f);
    } else if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y) {
        entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - entity->getGlobalBounds().height);
    }

//    for (int i=0; i<this->maxSizeWorldGrid.x; ++i) {
//        for (int j=0; j<this->maxSizeWorldGrid.y; j++) {
//            for(int l=0; l<this->layers; ++l) {
//                if(this->map[i][j][l] != nullptr && this->map[i][j][l]->getCollision()) {
//                    if (entity->getGlobalBounds().contains(this->map[i][j][l]))
//                }
//            }
//        }
//    }

}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect &texture_rect) {
    if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && x >= 0 & y >= 0 && z < this->layers && z >= 0) {
        if (this->map[x][y][z] == nullptr) {
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect);
        }
    }
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z) {
    if (x < this->maxSizeWorldGrid.x && y < this->maxSizeWorldGrid.y && x >= 0 & y >= 0 && z < this->layers && z >= 0) {
        if (this->map[x][y][z] != nullptr) {
            delete this->map[x][y][z];
            this->map[x][y][z] = nullptr;
        }
    }
}

void TileMap::saveToFile(std::string filename) {
    std::ofstream out_file;

    out_file.open(filename);

    if (out_file.is_open()) {
        out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
        << this->gridSizeU << "\n"
        << this->layers << "\n"
        << this->textureFile << "\n";

        for (int i=0; i<this->maxSizeWorldGrid.x; ++i) {
            for (int j=0; j<this->maxSizeWorldGrid.y; j++) {
                for(int l=0; l<this->layers; ++l) {
                    if(this->map[i][j][l] != nullptr) {
                        out_file << i << " " << j << " " << l << " " << this->map[i][j][l]->getAsString() << " ";
                    }
                }
            }
        }
    } else {
        std::cout << "ERROR: Could not open file for saving, file: " << filename << "\n";
    }

    std::cout << "Map saved: " << filename << "\n";
    out_file.close();
}

void TileMap::loadFromFile(std::string filename) {
    std::ifstream in_file;

    in_file.open(filename);

    if (in_file.is_open()) {
        sf::Vector2u size;
        unsigned gridSize = 0;
        unsigned layers = 0;
        std::string texture_file = "";
        unsigned x = 0, y = 0, z = 0;
        unsigned trX = 0, trY = 0;
        bool collision = false;
        short type = 0;

        in_file >> size.x >> size.y >> gridSize >> layers >> texture_file;

        std::cout << "gridSize: " << gridSize << "\n";

        this->gridSizeF = static_cast<float>(gridSize);
        this->gridSizeU = gridSize;
        this->maxSizeWorldGrid.x = size.x;
        this->maxSizeWorldGrid.y = size.y;
        this->layers = layers;
        this->textureFile = texture_file;

        this->clear();

        this->map.resize(this->maxSizeWorldGrid.x,std::vector<std::vector<Tile*>>());
        for (int i=0; i<this->maxSizeWorldGrid.x; ++i) {
            for (int j=0; j<this->maxSizeWorldGrid.y; j++) {
                this->map[i].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());
                for(int l=0; l<this->layers; ++l) {
                    this->map[i][j].resize(this->layers, nullptr);
                }
            }
        }

        this->tileSheet.loadFromFile(texture_file);

        while (in_file >> x >> y >> z >> trX >> trY >> collision >> type) {
            this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, 32, 32), collision, type);
        }

    } else {
        std::cout << "ERROR: Could not open file for saving, file: " << filename << "\n";
    }

    in_file.close();
}
