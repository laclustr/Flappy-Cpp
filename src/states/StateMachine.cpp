#include "flappyBird/states/StateMachine.hpp"

#include "flappyBird/states/PlayState.hpp"

#include "flappyBird/objects/Bird.hpp"
#include "flappyBird/utils/GameFont.hpp"
#include "flappyBird/utils/config.h"

#include <SFML/Graphics.hpp>

StateMachine::StateMachine(sf::RenderWindow& window) : font("assets/fonts/FlappyFont.ttf", sf::Color::White) {
    this->window = &window;

    states = {
        {State::PLAYING , new PlayState(this)}
    };

    currentState = states[State::PLAYING];
}

StateMachine::~StateMachine() {
    delete currentState;
}

void StateMachine::changeState(State newState) {
    delete currentState;
    currentState = states[newState];
}

void StateMachine::update(const std::set<sf::Keyboard::Key>& keysDown, const float dt) {
    if (currentState) {
        currentState->update(keysDown, dt);
    }
}

void StateMachine::render() {
    if (currentState) {
        currentState->render();
    }
}

void StateMachine::singlePlayer() {
    birds.clear();
    birds.push_back(new Bird(1, sf::Keyboard::Key::Space));
}

void StateMachine::multiPlayer() {
    birds.clear();
    birds.push_back(new Bird(1, sf::Keyboard::Key::Space));
    birds.push_back(new Bird(2, sf::Keyboard::Key::Enter));
}

std::vector<Bird*>& StateMachine::getBirds() {
    return birds;
}