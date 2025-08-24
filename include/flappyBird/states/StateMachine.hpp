#pragma once

#include "PlayState.hpp"
#include "BaseState.hpp"

#include "../objects/Bird.hpp"
#include "../utils/GameFont.hpp"
#include "../utils/config.h"

#include <SFML/Graphics.hpp>

#include <set>
#include <vector>
#include <string>
#include <unordered_map>

class StateMachine {
    public:
        StateMachine(sf::RenderWindow& window);
        ~StateMachine();

        void changeState(State newState);
        void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt);
        void render();

        void singlePlayer();
        void multiPlayer();

        std::vector<Bird*>& getBirds();
    private:
        sf::RenderWindow* window;
        std::set<sf::Keyboard::Key> keysDown;

        std::vector<Bird*> birds;

        GameFont font;

        std::unordered_map<State, BaseState*> states;

        BaseState* currentState;

};
