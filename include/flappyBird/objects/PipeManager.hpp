#pragma once

#include "PipePair.hpp"

#include <vector>
#include <utility>

class PipeManager {
    public:
        PipeManager();
        ~PipeManager();

        void update(float dt);
        bool collidesWith(const sf::FloatRect& bounds) const;
        bool hasPassed(const sf::FloatRect& bounds);
        
        // Combined check to reduce iterations - returns {collided, passed}
        std::pair<bool, bool> checkBirdInteraction(const sf::FloatRect& bounds) const;
        
        // Optimized version that only checks relevant pipes near the bird
        std::pair<bool, bool> checkBirdInteractionOptimized(const sf::FloatRect& bounds) const;
    private:
        std::vector<PipePair> pipes;

        float spawnTimer;
};
