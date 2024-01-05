#include "FlappyBird.h"

FlappyBird::FlappyBird(int windows_width, int windows_height) {
    num_pillars = 1;
    windows_size = { windows_width , windows_height };
    init();
}

bool FlappyBird::play(bool action) {
    bird->updateState(action);
    pillars->updateState();

    return !isTermination();
}

bool FlappyBird::isTermination() {
    if (bird->isDied(*pillars))
        return true;
    return false;
}

void FlappyBird::init() {
    if(bird != NULL) 
        delete bird;
    if (pillars != NULL)
        delete pillars;

    bird = new Bird(windows_size, 10.0, 40.0, 0.4);
    pillars = new Pillars(windows_size, num_pillars, windows_size.first / 100.0);
}
