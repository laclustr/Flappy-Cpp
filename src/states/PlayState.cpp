#include "flappyBird/states/PlayState.hpp"

#include "flappyBird/utils/config.h"
#include "flappyBird/objects/PipeManager.hpp"
#include "flappyBird/objects/Bird.hpp"


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

    for (Bird* bird : stateMachine->getBirds()) {
        bird->update(keysDown, dt);
        if (bird->hits_bottom()) {
            bird->kill();
            stateMachine->changeState(State::LOST);
        }

        // Use optimized combined check instead of separate collision and passing checks
        // This reduces iterations from 2N to N where N is the number of pipes
        auto [collided, passed] = pipeManager->checkBirdInteractionOptimized(bird->getBounds());
        
        if (collided) {
            bird->kill();
            stateMachine->changeState(State::LOST);
        }

        if (bird->above_screen() && passed) {
            bird->kill();
            stateMachine->changeState(State::LOST);
        }
    }
}

void PlayState::render() {
    
}
