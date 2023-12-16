#ifndef GO_ZOBRISTHASH_H
#define GO_ZOBRISTHASH_H


#include "include.h"
using namespace std;

namespace Go {
    static array<array<uint64_t, BOARD_SIZE * BOARD_SIZE>, 3> zobristTable;

    inline void zobrist_init() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < BOARD_SIZE * BOARD_SIZE; j++) {
                zobristTable[i * BOARD_SIZE + j] = randuint64();
            }
        }
    };

    inline void zobrist_hash(uint64_t hashValueOld, int x, int y, int color) {
        hashValueOld ^= zobristTable[x * BOARD_SIZE + y];
        return hashValueOld;
    }
}
#endif