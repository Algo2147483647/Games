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
#define BOARD_PIECE_NUM  BOARD_SIZE * BOARD_SIZE
#define BLACK  1
#define WHITE -1

    // Chess Piece
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
        short action = -1;
        char  player = -1;

        array<Piece, BOARD_PIECE_NUM> board;
        unordered_map<int, int> action_set;

        // Special Rule Flag
        int king_move = 0,
            rook_move = 0,
            pawn_move_two = -1;

        State() {
            board.fill(EMPTY);
        }

        inline bool isLegalAction(int i, int x, int y) {
            if (x < 0 || x >= BOARD_SIZE ||
                y < 0 || y >= BOARD_SIZE)
                return false;
            if (getBoard(x, y) * board[i] > 0)
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

        inline bool setActionSet(int i, int x, int y, int v) {
            if(!isLegalAction(i, x, y))
                return false;

            action_set[i * BOARD_PIECE_NUM + x * BOARD_SIZE + y] = v;
            return true;
        }
    };
}
#endif