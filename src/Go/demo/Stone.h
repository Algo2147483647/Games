#ifndef GO_DEMO_STONE_H
#define GO_DEMO_STONE_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread> 
#include <QMessageBox>
#include "Board.h"

class Stone : public QWidget
{
    Q_OBJECT
public:
    Stone(QWidget* parent);

protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* e);

private:
    const int stoneSize = Board::gridSize * 0.8;

    QLabel* m_stones[BOARD_COLOR_NUM + 5];
    QLabel* m_stoneWarn = new QLabel(this);
    QLabel* m_winLable  = new QLabel(this);

    Go::State* state;

    void displayWin();
    void displayStone(array<Go::Color, BOARD_COLOR_NUM>& board);
};
#endif