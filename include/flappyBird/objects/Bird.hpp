#pragma once

#include <SFML/Graphics.hpp>

#include <set>

class Bird {
    public:
        Bird(int playerNum, sf::Keyboard::Key jumpKey);
        ~Bird();

        void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt);
        void render(sf::RenderWindow& window);

        void collides(sf::Sprite other);
        void hits_bottom();
        void above_screen();

    private:
        void _jump();

        sf::Sprite sprite;
        sf::Texture texture;

        sf::Keyboard::Key jumpKey;

        int playerNum;
        bool isAlive;
        long long score;

        float velocity;
        float gravity;
};
