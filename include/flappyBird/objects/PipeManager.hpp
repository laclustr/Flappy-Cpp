#pragma once

#include "PipePair.hpp"

#include <vector>

class PipeManager {
    public:
        PipeManager();
        ~PipeManager();

        void update(float dt);
        bool collidesWith(const sf::FloatRect& bounds) const;
        bool hasPassed(const sf::FloatRect& bounds);
    private:
        std::vector<PipePair> pipes;

        float spawnTimer;
};
