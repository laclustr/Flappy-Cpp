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
        if (pipe.getTopBounds().intersects(bounds) || pipe.getBottomBounds().intersects(bounds)) {
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
            if (pipe.getTopBounds().intersects(bounds) || pipe.getBottomBounds().intersects(bounds)) {
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
    
    const float birdLeft = bounds.left;
    const float birdRight = bounds.left + bounds.width;
    
    for (const auto& pipe : pipes) {
        const sf::FloatRect topBounds = pipe.getTopBounds();
        const sf::FloatRect bottomBounds = pipe.getBottomBounds();
        
        const float pipeLeft = topBounds.left;
        const float pipeRight = topBounds.left + topBounds.width;
        
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
            if (topBounds.intersects(bounds) || bottomBounds.intersects(bounds)) {
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