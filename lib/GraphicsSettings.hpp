#ifndef TANKS_GRAPHICSSETTINGS_HPP
#define TANKS_GRAPHICSSETTINGS_HPP

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <fstream>

class GraphicsSettings {
public:
    GraphicsSettings();

    std::string pathToFile;
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    void safeToFile();
    void loadFromFile();
    void setPathToFile(const std::string path);
    void apply();
};


#endif //TANKS_GRAPHICSSETTINGS_HPP
