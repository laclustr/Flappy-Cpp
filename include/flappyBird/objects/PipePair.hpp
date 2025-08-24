#pragma once

#include "flappyBird/objects/Bird.hpp"

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

class PipePair {
    public:
        PipePair();
        ~PipePair();

        void update(float dt);

        bool isOffScreen() const;
        bool hasPassed(sf::FloatRect bounds);
        bool collidesWith(const sf::FloatRect& bounds) const;

        sf::FloatRect getTopBounds() const;
        sf::FloatRect getBottomBounds() const;

    private:
        Pipe topPipe;
        Pipe bottomPipe;

        bool passed;
};