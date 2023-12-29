#ifndef FLAPPY_BIRD_PILLARS_H
#define FLAPPY_BIRD_PILLARS_H

#include <random>
using namespace std;

class Pillars {
public:
    float pillar_width;
    float hole_size_half;
    float speed;
    pair<int, int> windows_size;
    vector<pair<float, float>> pillarHoles;

    std::mt19937_64 gen;
    std::uniform_real_distribution<double> dis;

    Pillars(pair<int, int>& windows_size_, int num_pillars, float speed_) : windows_size(windows_size_), dis(0.0, 1.0), speed(speed_) {
        std::random_device rd;
        gen = std::mt19937_64(rd());

        pillar_width = windows_size.first / 6.0;
        hole_size_half = windows_size.second / 6.0;

        for (int i = 0; i < num_pillars; i++) {
            pillarHoles.emplace_back(
                windows_size.first + i * (windows_size.first + pillar_width) / num_pillars - pillar_width, 
                randDouble_01() * (windows_size.second - 2 * hole_size_half) + hole_size_half
            );
        }
    }

    inline double randDouble_01() {
        return dis(gen);
    }

    inline void updateState() {
        for (auto& e : pillarHoles) {
            e.first -= speed;
            if (e.first < -pillar_width) {
                e = {
                    windows_size.first, randDouble_01() * (windows_size.second - 2 * hole_size_half) + hole_size_half
                };
            }
        }
    }
};
#endif
