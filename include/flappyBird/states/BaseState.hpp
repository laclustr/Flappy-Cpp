#pragma once

#include "StateMachine.hpp"

#include <SFML/Graphics.hpp>

#include <set>

class BaseState {
    public:
        virtual ~BaseState() = default;

        virtual void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt) = 0;
        virtual void render(sf::RenderWindow& window) = 0;
};
