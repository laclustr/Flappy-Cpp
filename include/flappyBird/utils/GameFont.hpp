#pragma once

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

class GameFont {
    public:
        GameFont(const std::string& path, sf::Color color = sf::Color::White);
        ~GameFont();

        void addSize(int size);
        void setFontSize(const int size);
        void setColor(const sf::Color& color);

        void render(sf::RenderWindow& window, const std::string& text, float x, float y);

        int getSize() const;
        const sf::Color& getColor() const;

    private:
        std::string path;
        std::unordered_map<int, sf::Font> fontSizes;

        sf::Color textColor;
        int currFontSize;
};