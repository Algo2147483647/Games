#ifndef CHESS_STATE_H
#define CHESS_STATE_H

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>

using namespace std;

namespace Chess {
#define BOARD_SIZE 8
#define BOARD_PIECE_NUM  (BOARD_SIZE * BOARD_SIZE)

    // Chess Piece
    enum { BLACK = 1, WHITE = -1 };
    typedef char Color;

    enum { EMPTY = 0, KING, QUEEN, BISHOP, ROOK, KNIGHT, PAWN };
    typedef char Piece;

    inline void initBoard(array<Piece, BOARD_PIECE_NUM>& board) {
        board = { {
            ROOK, KNIGHT, BISHOP, QUEEN, KING, BISHOP, KNIGHT, ROOK,
            PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN, PAWN,
            EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
            EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
            -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN, -PAWN,
            -ROOK, -KNIGHT, -BISHOP, -QUEEN, -KING, -BISHOP, -KNIGHT, -ROOK
        } };
    }

    class State {
    public:
        int action = -1;
        Color player = WHITE;

        array<Piece, BOARD_PIECE_NUM> board;
        unordered_map<int, int> action_set;

        // Special Rule Flag
        char king_move = 0;
        char rook_move = 0;
        char pawn_move_two = -1;

        State() {
            board.fill(EMPTY);
            initBoard(board);
        }

        inline bool isLegalAction(int st, int ed_x, int ed_y) {
            if (ed_x < 0 || ed_x >= BOARD_SIZE ||
                ed_y < 0 || ed_y >= BOARD_SIZE)
                return false;
            if (getBoard(ed_x, ed_y) * board[st] > 0)
                return false;
            return true;
        }

        inline Piece& getBoard(int x, int y) {
            return board[x * BOARD_SIZE + y];
        }

        inline bool setBoard(int x, int y, Piece v) {
            if (x < 0 || x >= BOARD_SIZE ||
                y < 0 || y >= BOARD_SIZE)
                return false;

            board[x * BOARD_SIZE + y] = v;
            return true;
        }

        inline bool setActionSet(int st, int ed_x, int ed_y, int v) {
            if(!isLegalAction(st, ed_x, ed_y))
                return false;

            action_set[st * BOARD_PIECE_NUM + ed_x * BOARD_SIZE + ed_y] = v;
            return true;
        }
    };
}
#endif