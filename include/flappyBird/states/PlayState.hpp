#pragma once

#include "BaseState.hpp"
#include "StateMachine.hpp"

#include "../objects/PipeManager.hpp"

#include <set>

class StateMachine;

class PlayState : public BaseState {
    public:
        PlayState(StateMachine* stateMachine);
        ~PlayState();

        void update(const std::set<sf::Keyboard::Key>& keysDown, const float dt) override;
        void render() override;

    private:
        StateMachine* stateMachine;

        PipeManager* pipeManager;
};
