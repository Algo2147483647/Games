#ifndef GO_DEMO_ANALYSIS_H
#define GO_DEMO_ANALYSIS_H

#include <QMainWindow>
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QThread> 
#include <QMessageBox>
#include "Board.h"
#include "./core/Go.h"

class Analysis : public QWidget
{
public:
    QWidget* w;
    array<QLabel*, BOARD_COLOR_NUM> m_labels;
    array<string, BOARD_COLOR_NUM> m_labels_string;

    bool is_ai_open = false;

    Analysis(QWidget* parent) : QWidget(parent) {
        w = parent;

        QFont font("Times New Roman", 15, 50);
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            m_labels[i] = new QLabel(w);
            m_labels[i]->setFont(font);
            m_labels[i]->setStyleSheet("color:White");
            m_labels[i]->setAlignment(Qt::AlignCenter);
        }
    }

    void displayAnalysis();
    void displaySerialNumber(vector<Go::State>& ss);
    void displayQi(Go::State& s);
    void displayMark(Go::State& s);
};

#endif
//
//void openAI();
//void aiEvaluate();
//void aiEvaluate_visit();
//void displayQi(Go::State& s);
//void displayMark(Go::State& s);
//
//
////GoAI::evaluate_result.resize(BOARD_COLOR_NUM, 0);
////GoAI::evaluate_visit. resize(BOARD_COLOR_NUM, 0);
//
//void Stone::openAI() {
//    //static ThreadClass ai;
//    static QThread thread;
//
//    if (ai_is_open == 0) {
//        ai_is_open = 1;
//        //ai.s = state;
//
//       // QObject::connect(&thread, &QThread::started, &ai, &ThreadClass::openAI);
//        //ai.moveToThread(&thread);
//        //thread.start();
//    }
//    return;
//}
//
///*
// *  显示AI评估结果
// */
//void Stone::aiEvaluate() {
//    static int fg = 0;
//    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
//    static QFont font("Times New Roman", 12, 50);
//
//    if (fg == 0) {
//        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
//            labels[i] = new QLabel(w);
//            labels[i]->setFont(font);
//            labels[i]->setAlignment(Qt::AlignCenter);
//        }
//        fg = 1;
//    }
//
//    float maxn = -0x7FFFFFFF;
//    int maxi = 0;
//
//    if (fg == 1) {
//        //GoAI::evaluate_fg = 1;
//        QThread::msleep(50);
//
//        //for (int i = 0; i < BOARD_COLOR_NUM; i++)
//            //if (state->mark[i] == -1 && maxn < GoAI::evaluate_result[i]) {
//                //maxn = GoAI::evaluate_result[i];
//                //maxi = i;
//            //} 
//    }
//
//    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
//        if ((state->mark[i] == -1) && fg == 1) {
//            int x = i % BOARD_SIZE,
//                y = i / BOARD_SIZE;
//            //v = GoAI::evaluate_result[i] * 100
//
//            if (i == maxi)
//                labels[i]->setStyleSheet("color:Red");
//            else
//                labels[i]->setStyleSheet("color:Blue");
//
//            //labels[i]->setText(QString::fromStdString(to_string(v)));
//            labels[i]->setGeometry(
//                Board::boardMargin + Board::gridSize * (x - 0.36),
//                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
//            labels[i]->show();
//        }
//        else
//            labels[i]->hide();
//    }
//    fg = -fg;
//}
//
///*
// *  显示AI评估结果
// */
//void Stone::aiEvaluate_visit() {
//    static int fg = 0;
//    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
//    static QFont font("Times New Roman", 8, 50);
//
//    if (fg == 0) {
//        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
//            labels[i] = new QLabel(w);
//            labels[i]->setFont(font);
//            labels[i]->setAlignment(Qt::AlignCenter);
//            labels[i]->setStyleSheet("color:Blue");
//        }
//        fg = 1;
//    }
//
//    if (fg == 1) {
//        //GoAI::evaluate_fg = 1;
//        QThread::msleep(50);
//    }
//
//    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
//        if ((state->mark[i] == -1) && fg == 1) {
//            int x = i % BOARD_SIZE,
//                y = i / BOARD_SIZE;
//            //v = GoAI::evaluate_visit[i]
//
//        //labels[i]->setText(QString::fromStdString(to_string(v)));
//            labels[i]->setGeometry(
//                Board::boardMargin + Board::gridSize * (x - 0.36),
//                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
//            labels[i]->show();
//        }
//        else
//            labels[i]->hide();
//    }
//    fg = -fg;
//}
//
//

//
//void Stone::mousePressEvent(QMouseEvent* e) {
//    signed char x, y;
//
//    if (e->button() == Qt::LeftButton) {    //左键按下
//        x = (e->x() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
//        y = (e->y() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
//
//        Go::play(*state, y * BOARD_SIZE + x);
//
//        displayStone(state->board);
//        displayWin();
//
//        //if (ai_is_open)
//            //GoAI::move_pos = y * BOARD_SIZE + x;
//
//        StoneWarn->setGeometry(
//            Board::boardMargin + x * Board::gridSize - stoneSize / 2,
//            Board::boardMargin + y * Board::gridSize - stoneSize / 2,
//            4, 4
//        );
//    }
//    else if (e->button() == Qt::RightButton) {
//
//    }
//    else if (e->button() == Qt::MiddleButton) {
//
//        displayStone(state->board);
//    }
//}
//

