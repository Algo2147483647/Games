#ifndef FLAPPY_BIRD_H
#define FLAPPY_BIRD_H

#include "Bird.h"
#include "Pillars.h"

using namespace std;

class FlappyBird {
public:
    int num_pillars;
    pair<int, int> windows_size;
    Bird* bird;
    Pillars* pillars;

    FlappyBird(int windows_width, int windows_height);

    bool play(bool action);
    bool isTermination();
    void init();
};

#endif // FLAPPY_BIRD_H
