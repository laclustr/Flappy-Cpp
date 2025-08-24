#pragma once

#include "Pipe.hpp"

#include <SFML/Graphics.hpp>

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