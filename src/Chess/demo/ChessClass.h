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

    QLabel* Chess[BOARD_PIECE_NUM];
    QLabel* ChessEd[BOARD_PIECE_NUM];
    QLabel* ChessWarn = new QLabel(this);
    QLabel* WinLable  = new QLabel(this);

    Chess::State* state = new Chess::State();

    void openAI();
    void aiEvaluate();
    void aiEvaluate_visit();

    void printChess(std::array<Chess::Piece, BOARD_PIECE_NUM>& Board);
    void printWin(int win);
    bool printEd(Chess::State& s, int st);
    void printOpponentControlPoint(Chess::State& s);
};
#endif