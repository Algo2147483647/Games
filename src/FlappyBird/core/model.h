#ifndef FLAPPY_BIRD_MODEL_H
#define FLAPPY_BIRD_MODEL_H

#include <utility>
#include <random>
using namespace std;

inline double randDouble_01() {
    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0);
    return dis(gen);
}

class Pillars {
public:
    int pillar_width;
    int hole_size;
    int speed_x;
    pair<int, int> windows_size;
    vector<pair<int, int>> pillarHoles;

    Pillars(pair<int, int>& windows_size_, int num_pillars) : windows_size(windows_size_) {
        pillar_width = windows_size.first / 10;
        hole_size = windows_size.second / 10;
        speed_x = windows_size.first / 100;

        pillarHoles.resize(num_pillars);
        pillarHoles[0] = { windows_size.first, int(randDouble_01() * windows_size.second) };
    }

    inline void updateState() {
        for (auto& e : pillarHoles) {
            e.first += speed_x;
            if (e.first < -pillar_width) {
                e.first = windows_size.first + pillar_width;
                e.second = int(randDouble_01() * windows_size.second);
            }
        }
    }
};

class Bird {
public:
    int speed_y;
    pair<int, int> windows_size;
    pair<int, int> position;

    Bird(pair<int, int>& windows_size_) : windows_size(windows_size_) {
        position = { windows_size.first / 5, windows_size.second / 2 };
        speed_y = windows_size.second / 100;
    }

    inline void updateState(bool action) {
        if (action) {
            position.second += 3 * speed_y;
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