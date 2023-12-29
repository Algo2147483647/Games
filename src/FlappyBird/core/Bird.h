#ifndef FLAPPY_BIRD_BIRD_H
#define FLAPPY_BIRD_BIRD_H

#include <utility>
#include "Pillars.h"
using namespace std;


class Bird {
public:
    float g;
    float up_speed;
    float speed;
    float delta_time;
    pair<int, int> windows_size;
    pair<float, float> position;

    Bird(pair<int, int>& windows_size_, float g_, float up_speed_, float delta_time_) :
        windows_size(windows_size_),
        g(g_),
        up_speed(up_speed_),
        delta_time(delta_time_)
    {
        position = { windows_size.first / 4.0, windows_size.second / 2.0 };
        speed = 0;
    }

    inline void updateState(bool action) {
        if (action) {
            speed = up_speed;
        }
        position.second += speed * delta_time - 0.5 * g * delta_time * delta_time;
        speed -= g * delta_time;
    }

    inline bool isDied(Pillars& pillars) {
        if (position.second <= 0 || 
            position.second >= windows_size.second)
            return true;

        for (auto& e : pillars.pillarHoles) {
            if (position.first >= e.first &&
                position.first <= e.first + pillars.pillar_width &&
                (position.second <= e.second - pillars.hole_size_half ||
                 position.second >= e.second + pillars.hole_size_half)) {
                return true;
            }
        }
        return false;
    }
};
#endif