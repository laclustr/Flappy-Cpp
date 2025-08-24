#pragma once

const int DISP_WIDTH = 800;
const int DISP_HEIGHT = 600;

enum State {
    MENU,
    COUNTDOWN,
    PLAYING,
    PAUSED,
    LOST,
    HIGH_SCORE
};

const int PIPE_SPAWN_INTERVAL = 200;