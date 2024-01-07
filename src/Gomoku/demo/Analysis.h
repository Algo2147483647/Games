#ifndef GOMOKU_DEMO_ANALYSIS_H
#define GOMOKU_DEMO_ANALYSIS_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <thread> 
#include <QMessageBox>
#include "Board.h"
#include "./core/Gomoku.h"
#include "./ai/ai.h"

class Analysis : public QWidget
{
public:
    QWidget* w;
    array<QLabel*, Gomoku::BOARD_COLOR_NUM> m_labels;
    array<string, Gomoku::BOARD_COLOR_NUM> m_labels_string;
    std::vector<QLabel*> m_stones;

    bool is_ai_open = false;
    std::thread myThread;

    Analysis(QWidget* parent) : QWidget(parent) {
        w = parent;

        QFont font("Times New Roman", 8, 50);
        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
            m_labels[i] = new QLabel(w);
            m_labels[i]->setFont(font);
            m_labels[i]->setStyleSheet("color:Green");
            m_labels[i]->setAlignment(Qt::AlignCenter);
        }

        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++)
            m_stones.push_back(new QLabel(this));
    }

    void displayAnalysis();
    void displaySerialNumber(vector<Gomoku::State>& ss);

    void openAI(Gomoku::State& s);
    void aiEvaluate(Gomoku::State& s);
};

#endif
