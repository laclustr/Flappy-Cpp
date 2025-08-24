#pragma once

#include <SFML/Graphics.hpp>

class Pipe {
    public:
        Pipe(float x, float y, bool isTop);
        ~Pipe();

        void update(float dt);
        void render(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;
    private:
        sf::Sprite sprite;
        sf::Texture texture;
};