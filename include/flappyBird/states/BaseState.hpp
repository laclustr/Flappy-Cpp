#pragma once

#include "StateMachine.hpp"

class BaseState {
    public:
        virtual ~BaseState();

        virtual void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt);
        virtual void render();
};
