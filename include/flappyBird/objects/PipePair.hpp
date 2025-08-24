#pragma once

#include <SFML/Graphics.hpp>

class Pipe {
    public:
        Pipe(float x, float y, bool isTop);
        ~Pipe();

        void update(float dt);
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
    
    private:
        Pipe topPipe;
        Pipe bottomPipe;

        bool passed;
};