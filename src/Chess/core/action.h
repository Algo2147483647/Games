#ifndef CHESS_ACTION_H
#define CHESS_ACTION_H

#include <stdio.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <algorithm>
#include "state.h"

using namespace std;

namespace Chess {
    // step of x, y
    static const int
        x_step[] = { 1,-1, 0, 0, 1,-1, 1,-1 },
        y_step[] = { 0, 0, 1,-1, 1, 1,-1,-1 };

    inline void createActionSet(State& s) {
        s.action_set.clear();

        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            if (s.board[i] * s.player <= 0)
                continue;

            int x = i / BOARD_SIZE,
                y = i % BOARD_SIZE,
                p = s.board[i];

            switch (abs(p)) {
            case KING: {
                for (int j = 0; j < 8; j++) {
                    s.setActionSet(i, x + x_step[j], y_step[j], 1);
                }
                // Castling  
                if ((p > 0 && (s.king_move & 0b01) == 0 && (s.rook_move & 0b01) == 0) ||
                    (p < 0 && (s.king_move & 0b10) == 0 && (s.rook_move & 0b10) == 0)) {
                    if (s.getBoard(x, 5) == EMPTY &&
                        s.getBoard(x, 6) == EMPTY)
                        s.setActionSet(i, x, 6, -1);

                    if (s.getBoard(x, 1) == EMPTY &&
                        s.getBoard(x, 2) == EMPTY &&
                        s.getBoard(x, 3) == EMPTY)
                        s.setActionSet(i, x, 2, -1);
                }

            } break;
            case QUEEN: case BISHOP: case ROOK: {
                int j_st = abs(p) == BISHOP ? 4 : 0,
                    j_ed = abs(p) == ROOK   ? 4 : 8;

                for (int j = j_st; j < j_ed; j++) {
                    for (int t = 0;; t++) {
                        if (!s.setActionSet(i, x + t * x_step[j], y + t * y_step[j], 1))
                            break;
                        if (s.getBoard(x + t * x_step[j], y + t * y_step[j]) * p < 0)
                            break;
                    }
                }
            } break;
            case KNIGHT: {
                for (int j = 4; j < 8; j++) {
                    s.setActionSet(i, x + x_step[j] * 2, y + y_step[j] * 1, 1); // (2, 1)
                    s.setActionSet(i, x + x_step[j] * 1, y + y_step[j] * 2, 1); // (1, 2)
                }
            } break;
            case PAWN: {
                int dir = s.player;
                bool isPromotion = (x == (dir == WHITE ? 1 : BOARD_SIZE - 2));

                // basic action & Promotion
                if (s.getBoard(x + dir, y) == EMPTY)
                    s.setActionSet(i, x + dir, y, isPromotion ? -1 : 1);
                if (y - 1 >= 0 && s.getBoard(x + dir, y - 1) * p < 0)
                    s.setActionSet(i, x + dir, y - 1, isPromotion ? -1 : 1);
                if (y + 1 < BOARD_SIZE && s.getBoard(x + dir, y + 1) * p < 0)
                    s.setActionSet(i, x + dir, y + 1, isPromotion ? -1 : 1);

                // move two step
                if (x == (dir == WHITE ? BOARD_SIZE - 2 : 1) && s.getBoard(x + dir, y) == EMPTY && s.getBoard(x + 2 * dir, y) == EMPTY) {
                    s.setActionSet(i, x + 2 * dir, y, 1);
                }
                // En passant
                else if (x == (dir == WHITE ? 3 : 4) && abs(s.pawn_move_two - i) == 1) {
                    s.setActionSet(i, x + dir, s.pawn_move_two % BOARD_SIZE, -1);
                }
            } break;
            default: break;
            }
        }
    }

    // move chess
    inline bool moveChess(State& s) {
        if (s.action_set.find(s.action) == s.action_set.end())
            return false;

        int st = s.action / BOARD_PIECE_NUM,
            ed = s.action % BOARD_PIECE_NUM;

        // mark the flag of state
        s.pawn_move_two = -1;
        int p = abs(s.board[st]);

        if (p == KING) {
            s.king_move |= (s.player == BLACK) ? 0x01 : 0x10;
        }
        else if (p == ROOK || (p == KING && s.action_set[s.action] < 0)) {
            s.rook_move |= (s.player == BLACK) ? 0x01 : 0x10;
        }
        else if (p == PAWN && abs(st / BOARD_SIZE - ed / BOARD_SIZE) == 2) {
            s.pawn_move_two = ed;
        }

        if (s.action_set[s.action] > 0) {
            s.board[ed] = s.board[st];
            s.board[st] = EMPTY;
        }
        else {
            // Special Rules
            if (abs(s.board[st]) == KING) {
                // Castling  
                int x = ed / BOARD_SIZE,
                    y = ed % BOARD_SIZE;

                swap(s.board[st], s.board[ed]);

                if (y == 6)
                    swap(s.getBoard(x, 7), s.getBoard(x, 5));
                else if (y == 2)
                    swap(s.getBoard(x, 0), s.getBoard(x, 3));
            }
            if (abs(s.board[st]) == PAWN) {
                int x = ed / BOARD_SIZE,
                    y = ed % BOARD_SIZE;

                if (x != 0 && x != BOARD_SIZE - 1) {
                    // En passant  
                    swap(s.board[st], s.board[ed]);
                    s.setBoard(st / BOARD_SIZE, y, 0);
                }
                else {
                    // Promotion  
                    s.board[st] = 0;
                    s.board[ed] = s.player * QUEEN;
                }
            }
        }

        s.player = -s.player;
        createActionSet(s);

        return true;
    }
}
#endif