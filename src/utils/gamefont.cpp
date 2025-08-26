#include "flappyBird/utils/GameFont.hpp"

GameFont::GameFont(const std::string& path, sf::Color color) {
    this->path = path;
    textColor = color;

    sf::Font font;
    if (!font.openFromFile(path)) {
        throw std::runtime_error("Failed to load font: " + path);
    }

    fontSizes[30] = font;
    currFontSize = 30;

}

GameFont::~GameFont() {}

void GameFont::render(sf::RenderWindow& window, const std::string& text, float x, float y) {
    sf::Text drawableText(fontSizes[currFontSize], text, currFontSize);
    drawableText.setFillColor(textColor);
    drawableText.setPosition({x, y});
    window.draw(drawableText);
}

void GameFont::addSize(int size) {
    sf::Font font;
    if (!font.openFromFile(path)) {
        throw std::runtime_error("Failed to load font: " + path);
    }
    fontSizes[size] = font;
}

void GameFont::setFontSize(const int size) {
    if (fontSizes.find(size) != fontSizes.end()) {
        currFontSize = size;
    }
}

void GameFont::setColor(const sf::Color& color) {
    textColor = color;
}

int GameFont::getSize() const {
    return currFontSize;
}

const sf::Color& GameFont::getColor() const {
    return textColor;
}
