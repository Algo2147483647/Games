#ifndef GO_DEMO_CONTROLLER_H
#define GO_DEMO_CONTROLLER_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread> 
#include <QMessageBox>
#include "Stone.h"
#include "Analysis.h"
#include "./core/Go.h"

class Controller : public QWidget
{
    Q_OBJECT
public:
    Stone* stone;
    Analysis* analysis;
    Go::State* state;
    vector<Go::State> m_state_history;
    
    Controller(QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);
};
#endif
/*QLabel* m_winLable = new QLabel(this);*/
/*void displayWin() {
    if (Go::isTermination(*state)) {
        Go::Color win = Go::computeReward(*state);

        QFont font("Times New Roman", 50, 50, false);
        m_winLable->setGeometry(0, 0, 0, 0);
        m_winLable->setFont(font);
        m_winLable->setGeometry(20, 20, 1000, 100);

        if (win == Go::BLACK)
            m_winLable->setText("BLACK Win");
        else if (win == Go::WHITE)
            m_winLable->setText("WHITE Win");
    }
}*/