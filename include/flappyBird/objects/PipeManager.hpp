#pragma once

#include "PipePair.hpp"

#include <vector>
#include <utility>

class PipeManager {
    public:
        PipeManager();
        ~PipeManager();

        void update(float dt);
        void render(sf::RenderWindow& window);

        bool collidesWith(const sf::FloatRect& bounds) const;
        bool hasPassed(const sf::FloatRect& bounds);
        
        std::pair<bool, bool> checkBirdInteraction(const sf::FloatRect& bounds) const;
        
        std::pair<bool, bool> checkBirdInteractionOptimized(const sf::FloatRect& bounds) const;
    private:
        std::vector<PipePair> pipes;

        float spawnTimer;
};
