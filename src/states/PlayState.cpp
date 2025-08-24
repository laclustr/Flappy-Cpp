#include "PlayState.hpp"

#include "flappyBird/utils/config.h"
#include "flappyBird/objects/PipeManager.hpp"


PlayState::PlayState(StateMachine* stateMachine) {
    this->stateMachine = stateMachine;
    pipeManager = new PipeManager();
}

PlayState::~PlayState() {}

void PlayState::update(const std::set<sf::Keyboard::Key>& keysDown, const float dt) {
    pipeManager->update(dt);

    if (keysDown.find(sf::Keyboard::Key::P) != keysDown.end()) {
        stateMachine->changeState(State::PAUSED);
    }

    for (auto bird : stateMachine->getBirds()) {
        bird->update(keysDown, dt);
    }
}

void PlayState::render() {
    
}
