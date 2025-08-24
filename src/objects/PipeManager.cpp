#include "flappyBird/objects/PipeManager.hpp"

#include "flappyBird/utils/config.h"

PipeManager::PipeManager() {
    spawnTimer = PIPE_SPAWN_INTERVAL;
}

PipeManager::~PipeManager() {
}

void PipeManager::update(float dt) {
    spawnTimer -= dt;
    if (spawnTimer <= 0.f) {
        pipes.push_back(PipePair());
        spawnTimer = PIPE_SPAWN_INTERVAL;
    }

    for (auto& pipe : pipes) {
        pipe.update(dt);
        if (pipe.isOffScreen()) {
            pipes.erase(pipes.begin());
            delete &pipe;
        }
    }
}