#ifndef GO_DEMO_H
#define GO_DEMO_H

#include <QtWidgets/QMainWindow>  
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include "Board.h"
#include "Stone.h"

class GoDemo : public QMainWindow
{
public:
    short windowSize; 
    Board* board;
    Stone* stone;
    QWidget* m_boardWidget;
    QWidget* m_stoneWidget;

    GoDemo(QWidget* parent = 0) : QMainWindow(parent) {
        windowSize = Board::gridSize * (BOARD_SIZE + 0.5);
        setMaximumSize(windowSize, windowSize);
        setMinimumSize(windowSize, windowSize);
        setWindowTitle("Go");
        setWindowOpacity(0.8);

        // Board 
        m_boardWidget = new QWidget(this);
        initializeWidget(m_boardWidget, Qt::white);
        board = new Board(m_boardWidget, BOARD_SIZE);
        board->setGeometry(0, 0, windowSize, windowSize);

        // Stone 
        m_stoneWidget = new QWidget(this);
        initializeWidget(m_stoneWidget, Qt::transparent);
        stone = new Stone(m_stoneWidget);
        stone->setGeometry(0, 0, windowSize, windowSize);
    }
    ~GoDemo() { ; };

    void initializeWidget(QWidget* widget, const QColor& backgroundColor) {
        widget->setGeometry(0, 0, windowSize, windowSize);
        QPalette pal(widget->palette());
        pal.setColor(QPalette::Window, backgroundColor);
        widget->setAutoFillBackground(true);
        widget->setPalette(pal);
        widget->show();
    }
};

#endif