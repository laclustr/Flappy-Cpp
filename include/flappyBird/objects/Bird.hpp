#pragma once

#include <SFML/Graphics.hpp>

#include <set>

class Bird {
    public:
        Bird(int playerNum, sf::Keyboard::Key jumpKey);
        ~Bird();

        void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt);
        void render(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;

        bool collides(sf::Sprite other);
        bool hits_bottom();
        bool above_screen();

        bool is_alive() const;
        void kill();

    private:
        void jump();

        sf::Sprite sprite;
        sf::Texture texture;

        sf::Keyboard::Key jumpKey;

        int playerNum;
        bool isAlive;
        long long score;

        float velocity;
        float gravity;
};
