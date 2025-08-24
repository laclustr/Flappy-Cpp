#include "flappyBird/utils/GameFont.hpp"

GameFont::GameFont(const std::string& path, sf::Color color = sf::Color::White) {
    this->path = path;
    textColor = color;

    sf::Font font;
    if (!font.loadFromFile(path)) {
        throw std::runtime_error("Failed to load font: " + path);
    }

    fontSizes[30] = font;
    currFontSize = 30;

}

GameFont::~GameFont() {}

void render(sf::RenderWindow& window, const std::string& text, float x, float y) {
    sf::Text drawableText;
    drawableText.setFont(fontSizes[currFontSize]);
    drawableText.setString(text);
    drawableText.setCharacterSize(currFontSize);
    drawableText.setFillColor(textColor);
    drawableText.setPosition(x, y);
    window.draw(drawableText);
}

void addSize(int size) {
    sf::Font font;
    if (!font.loadFromFile(path)) {
        throw std::runtime_error("Failed to load font: " + path);
    }
    fontSizes[size] = font;
}

void setFontSize(const int size) {
    if (fontSizes.find(size) != fontSizes.end()) {
        currFontSize = size;
    }
}

void setColor(const sf::Color& color) {
    textColor = color;
}

const int getSize() const {
    return currFontSize;
}

const sf::Color& getColor() const {
    return &textColor;
}
