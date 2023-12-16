#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

namespace Chess {
#define BOARDSIZE 8
#define BLACK  1
#define WHITE -1

    // Chess Piece
    enum { KING = 1, QUEEN, BISHOP, ROOK, KNIGHT, PAWN };
    typedef char Piece;
}

class State {
public:
    short action = -1;
    char  player = -1;

    Mat<Piece> board{ BOARDSIZE , BOARDSIZE };
    unordered_map<int, int> actionSet;

    State* parent = NULL;

    // Special Rule Flag
    int king_move_black = 0,
        king_move_white = 0,
        rook_move_black = 0,
        rook_move_white = 0,
        pawn_move_two = -1;

    State() {
        board.zero(BOARDSIZE, BOARDSIZE);
    }

    State& operator=(State& x) {
        action = x.action;
        player = x.player;

        board = x.board;
        actionSet = x.actionSet;

        parent = x.parent;

        king_move_black = x.king_move_black;
        king_move_white = x.king_move_white;
        rook_move_black = x.rook_move_black;
        rook_move_white = x.rook_move_white;
        pawn_move_two = x.pawn_move_two;

        return *this;
    }
};