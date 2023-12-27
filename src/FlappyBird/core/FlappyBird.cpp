#include "FlappyBird.h"

FlappyBird::FlappyBird(int windows_width, int windows_height) {
    num_pillars = 1;
    windows_size = { windows_width , windows_height };
    bird = new Bird(windows_size);
    pillars = new Pillars(windows_size, num_pillars);
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
    delete bird;
    delete pillars;

    bird = new Bird(windows_size);
    pillars = new Pillars(windows_size, num_pillars);
}
