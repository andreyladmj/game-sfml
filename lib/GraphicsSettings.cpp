#include "GraphicsSettings.hpp"

GraphicsSettings::GraphicsSettings() {
    this->resolution = sf::VideoMode::getDesktopMode();
    this->frameRateLimit = 120;
    this->fullscreen = false;
    this->verticalSync = false;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
    this->title = "Game";
}

void GraphicsSettings::setPathToFile(const std::string path) {
    this->pathToFile = path;
}

void GraphicsSettings::safeToFile() {
    std::ofstream ofs(this->pathToFile);

    if (ofs.is_open()) {
        ofs << this->title << "\n";
        ofs << this->resolution.width << " " << this->resolution.height << "\n";
        ofs << fullscreen << "\n";
        ofs << this->frameRateLimit << "\n";
        ofs << this->verticalSync << "\n";
        ofs << this->contextSettings.antialiasingLevel;
    }

    ofs.close();
}

void GraphicsSettings::loadFromFile() {
    std::ifstream ifs(this->pathToFile);

    if (ifs.is_open()) {
        std::getline(ifs, this->title);
        ifs >> this->resolution.width >> this->resolution.height;
        ifs >> fullscreen;
        ifs >> this->frameRateLimit;
        ifs >> this->verticalSync;
        ifs >> this->contextSettings.antialiasingLevel;
    }

    ifs.close();
}

void GraphicsSettings::apply() {

}
