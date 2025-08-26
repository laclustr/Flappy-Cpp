#pragma once

#include "Pipe.hpp"

#include <SFML/Graphics.hpp>

class PipePair {
    public:
        PipePair();
        ~PipePair();

        void update(float dt);
        void render(sf::RenderWindow& window);

        bool isOffScreen() const;
        bool hasPassed(sf::FloatRect bounds) const;
        bool collidesWith(const sf::FloatRect& bounds) const;
        
        bool collidesWithOptimized(const sf::FloatRect& bounds, const sf::FloatRect& topBounds, const sf::FloatRect& bottomBounds) const;

        sf::FloatRect getTopBounds() const;
        sf::FloatRect getBottomBounds() const;

    private:
        Pipe topPipe;
        Pipe bottomPipe;

        mutable bool passed;
};