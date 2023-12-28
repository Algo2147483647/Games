#ifndef FLAPPY_BIRD_PILLARS_H
#define FLAPPY_BIRD_PILLARS_H

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
        speed_x = windows_size.first / 50;

        pillarHoles.resize(num_pillars);
        pillarHoles[0] = { windows_size.first, int(randDouble_01() * windows_size.second) };
    }

    inline void updateState() {
        for (auto& e : pillarHoles) {
            e.first -= speed_x;
            if (e.first < -pillar_width) {
                e.first = windows_size.first + pillar_width;
                e.second = int(randDouble_01() * windows_size.second);
            }
        }
    }
};
#endif