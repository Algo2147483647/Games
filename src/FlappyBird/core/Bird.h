#ifndef FLAPPY_BIRD_BIRD_H
#define FLAPPY_BIRD_BIRD_H

#include <utility>
#include "Pillars.h"
using namespace std;


class Bird {
public:
    int speed_y;
    pair<int, int> windows_size;
    pair<int, int> position;

    Bird(pair<int, int>& windows_size_) : windows_size(windows_size_) {
        position = { windows_size.first / 5, windows_size.second / 2 };
        speed_y = windows_size.second / 50;
    }

    inline void updateState(bool action) {
        if (action) {
            position.second += 4 * speed_y;
        }
        else {
            position.second += -speed_y;
        }
    }

    inline bool isDied(Pillars& pillars) {
        if (position.second <= 0 || 
            position.second >= windows_size.second)
            return true;

        for (auto& e : pillars.pillarHoles) {
            if (position.first >= e.first &&
                position.first <= e.first + pillars.pillar_width &&
                (position.second <= e.second - pillars.hole_size / 2 ||
                 position.second >= e.second + pillars.hole_size / 2)) {
                return true;
            }
        }
        return false;
    }
};
#endif