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

    auto it = pipes.begin();
    while (it != pipes.end()) {
        it->update(dt);
        if (it->isOffScreen()) {
            it = pipes.erase(it);
        } else {
            ++it;
        }
    }
}

bool PipeManager::collidesWith(const sf::FloatRect& bounds) const {
    for (const auto& pipe : pipes) {
        if (pipe.getTopBounds().findIntersection(bounds).has_value() || pipe.getBottomBounds().findIntersection(bounds).has_value()) {
            return true;
        }
    }
    return false;
}

bool PipeManager::hasPassed(const sf::FloatRect& bounds) {
    for (const PipePair& pipe : pipes) {
        if (pipe.hasPassed(bounds)) {
            return true;
        }
    }
    return false;
}

std::pair<bool, bool> PipeManager::checkBirdInteraction(const sf::FloatRect& bounds) const {
    bool collided = false;
    bool passed = false;
    
    for (const auto& pipe : pipes) {
        if (!collided) {
            if (pipe.getTopBounds().findIntersection(bounds).has_value() || pipe.getBottomBounds().findIntersection(bounds).has_value()) {
                collided = true;
                return {true, false};
            }
        }
        
        if (!passed && pipe.hasPassed(bounds)) {
            passed = true;
        }
    }
    
    return {collided, passed};
}

std::pair<bool, bool> PipeManager::checkBirdInteractionOptimized(const sf::FloatRect& bounds) const {
    bool collided = false;
    bool passed = false;
    
    const float birdLeft = bounds.position.x;
    const float birdRight = bounds.position.x + bounds.size.x;
    
    for (const auto& pipe : pipes) {
        const sf::FloatRect topBounds = pipe.getTopBounds();
        const sf::FloatRect bottomBounds = pipe.getBottomBounds();
        
        const float pipeLeft = topBounds.position.x;
        const float pipeRight = topBounds.position.x + topBounds.size.x;
        
        if (pipeLeft > birdRight + 50.0f) {
            continue;
        }
        
        if (pipeRight < birdLeft - 50.0f) {
            if (!passed && pipe.hasPassed(bounds)) {
                passed = true;
            }
            continue;
        }
        
        if (!collided) {
            if (topBounds.findIntersection(bounds).has_value() || bottomBounds.findIntersection(bounds).has_value()) {
                collided = true;
                return {true, false};
            }
        }
        
        if (!passed && pipe.hasPassed(bounds)) {
            passed = true;
        }
    }
    
    return {collided, passed};
}