#ifndef GOMOKU_DEMO_CONTROLLER_H
#define GOMOKU_DEMO_CONTROLLER_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread> 
#include <QMessageBox>
#include <QVBoxLayout>
#include "Board.h"
#include "Stone.h"
#include "Analysis.h"
#include "./core/Gomoku.h"

class Controller : public QWidget
{
    Q_OBJECT
public:
    QLabel* m_winLabel;

    Stone* stone;
    Analysis* analysis;

    Gomoku::State* state;
    vector<Gomoku::State> m_state_history;
    
    Controller(QWidget* parent);

    void displayWin();

protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
};
#endif
