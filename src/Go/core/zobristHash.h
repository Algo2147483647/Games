#ifndef GO_ZOBRISTHASH_H
#define GO_ZOBRISTHASH_H

#include <random>
#include "include.h"
using namespace std;

namespace Go {
    static array<array<uint64_t, BOARD_SIZE * BOARD_SIZE>, 3> zobristTable;

    inline uint64_t randuint64() {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<uint64_t> dis;
        return dis(gen);
    }

    inline void zobrist_init() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < BOARD_SIZE * BOARD_SIZE; j++) {
                zobristTable[i][j] = randuint64();
            }
        }
    };

    inline uint64_t& zobrist_hash(uint64_t& hashValue, int p, Color color) {
        hashValue ^= zobristTable[color + 1][p];
        return hashValue;
    }
}
#endif