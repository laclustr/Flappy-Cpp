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

const std::string PIPE_PATH = "assets/pipe.png";
const int PIPE_SPAWN_INTERVAL = 200;
const int PIPE_SPEED = 300;

const int BIRD_GRAVITY = 980;
const int BIRD_JUMP_HEIGHT = 350;

const std::string BIRD_ASSET_PATH = "assets/bird.png";