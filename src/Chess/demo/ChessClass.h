#ifndef CHESS_DEMO_Chess_H
#define CHESS_DEMO_Chess_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread> 
#include <stdio.h>
#include "./core/Chess.h"
#include "BoardClass.h"
#include "ThreadClass.h"

class ChessClass : public QWidget
{
public:
    ChessClass(QWidget* parent);

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* e);//鼠标点击事件

private:
    QWidget* w;
    int ai_is_open = 0;

    array<QLabel*, BOARD_PIECE_NUM> m_pieces;
    array<QLabel*, BOARD_PIECE_NUM> m_chess_actions;
    QLabel* m_action_warn;
    QLabel* m_win_lable;

    Chess::State* state;

    void displayChess(std::array<Chess::Piece, BOARD_PIECE_NUM>& board);
    void displayWin(int win);
    bool displayActions(Chess::State& s, int st);
    void displayOpponentControlPoint(Chess::State& s);
};
#endif