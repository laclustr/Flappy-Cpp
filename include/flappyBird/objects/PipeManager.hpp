#pragma once

#include "PipePair.hpp"

#include <vector>

class PipeManager {
    public:
        PipeManager();
        ~PipeManager();

        void update(float dt);
    private:
        std::vector<PipePair> pipes;

        float spawnTimer;
};
