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

    // Use iterator-based removal for efficiency and correctness
    auto it = pipes.begin();
    while (it != pipes.end()) {
        it->update(dt);
        if (it->isOffScreen()) {
            it = pipes.erase(it);  // erase returns iterator to next element
        } else {
            ++it;
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
        // Check collision first - early exit if collision detected
        if (!collided) {
            std::optional<sf::FloatRect> topIntersection = pipe.getTopBounds().findIntersection(bounds);
            std::optional<sf::FloatRect> bottomIntersection = pipe.getBottomBounds().findIntersection(bounds);
            if (topIntersection.has_value() || bottomIntersection.has_value()) {
                collided = true;
                // If collision detected, no need to check for passing
                return {true, false};
            }
        }
        
        // Check if bird has passed this pipe
        if (!passed && pipe.hasPassed(bounds)) {
            passed = true;
        }
    }
    
    return {collided, passed};
}

std::pair<bool, bool> PipeManager::checkBirdInteractionOptimized(const sf::FloatRect& bounds) const {
    bool collided = false;
    bool passed = false;
    
    // Bird's horizontal range for collision detection
    const float birdLeft = bounds.position.x;
    const float birdRight = bounds.position.x + bounds.size.x;
    
    // Only check pipes that could potentially interact with the bird
    // A pipe can interact if it's not too far to the right or completely past the bird
    for (const auto& pipe : pipes) {
        // Cache bounds to avoid multiple getBounds() calls
        const sf::FloatRect topBounds = pipe.getTopBounds();
        const sf::FloatRect bottomBounds = pipe.getBottomBounds();
        
        const float pipeLeft = topBounds.position.x;
        const float pipeRight = topBounds.position.x + topBounds.size.x;
        
        // Skip pipes that are too far ahead (no interaction possible)
        if (pipeLeft > birdRight + 50.0f) {  // 50px buffer
            continue;
        }
        
        // Skip pipes that are completely behind the bird (no collision possible, might still check for passing)
        if (pipeRight < birdLeft - 50.0f) {  // 50px buffer
            // Check if bird has passed this pipe (for scoring)
            if (!passed && pipe.hasPassed(bounds)) {
                passed = true;
            }
            continue;
        }
        
        // Check collision for pipes in interaction range using cached bounds
        if (!collided) {
            std::optional<sf::FloatRect> topIntersection = topBounds.findIntersection(bounds);
            std::optional<sf::FloatRect> bottomIntersection = bottomBounds.findIntersection(bounds);
            if (topIntersection.has_value() || bottomIntersection.has_value()) {
                collided = true;
                // If collision detected, no need to check for passing
                return {true, false};
            }
        }
        
        // Check if bird has passed this pipe
        if (!passed && pipe.hasPassed(bounds)) {
            passed = true;
        }
    }
    
    return {collided, passed};
}