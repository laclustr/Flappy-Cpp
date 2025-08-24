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

bool PipeManager::collidesWith(const sf::FloatRect& bounds) const {
    for (const auto& pipe : pipes) {
        std::optional<sf::FloatRect> topIntersection = pipe.getTopBounds().findIntersection(bounds);
        std::optional<sf::FloatRect> bottomIntersection = pipe.getBottomBounds().findIntersection(bounds);
        if (topIntersection.has_value() || bottomIntersection.has_value()) {
            return true;
        }
    }
    return false;
}

bool PipeManager::hasPassed(const sf::FloatRect& bounds) const {
    for (const PipePair pipe : pipes) {
        if (pipe.hasPassed(bounds)) {
            return true;
        }
    }
    return false;
}