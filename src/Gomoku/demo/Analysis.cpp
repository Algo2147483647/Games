#include "Analysis.h"

void Analysis::displayAnalysis() {
    static bool display = true;

    if (display) {
        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
            int x = i % Gomoku::BOARD_SIZE,
                y = i / Gomoku::BOARD_SIZE;

            m_labels[i]->setText(QString::fromStdString(m_labels_string[i]));
            m_labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            m_labels[i]->show();
        }
    } else {
        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++)
            m_labels[i]->hide();
    }
    display = !display;
}

void Analysis::displaySerialNumber(vector<Gomoku::State>& ss) {
    m_labels_string.fill("");
    /*
    int i = 0;
    for (auto& s : ss) {
        if (s.action != PASS && s.action != -2)
            m_labels_string[s.action] = to_string(i);
        i++;
    }*/
    displayAnalysis();
}

void Analysis::openAI(Gomoku::State& s) {
    //if (is_ai_open == false) {
    //    is_ai_open = true;
    //    myThread = std::thread(GoAI::MonteCarloTreeSearch, &s);
    //    myThread.detach();
    //}
    return;
}

/*
 *  ÏÔÊ¾AIÆÀ¹À½á¹û
 */
void Analysis::aiEvaluate(Gomoku::State& s) {
    //m_labels_string.fill("");

    //for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
    //    if (s.mark[i] == -1) {
    //        m_labels_string[i] = to_string(GoAI::evaluate_result[i] * 100);
    //    }
    //}

    displayAnalysis();
}