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
    is_ai_open = !is_ai_open;

    if (is_ai_open) {
        int max_reward = Gomoku_AI::run(s);
        aiEvaluate(s);

        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
            if (Gomoku_AI::evaluate_result[i] == max_reward && Gomoku_AI::evaluate_result[i] != -0x7FFFFFFF) {
                int x = i % Gomoku::BOARD_SIZE;
                int y = i / Gomoku::BOARD_SIZE;
                x = Board::boardMargin + x * Board::gridSize - (Board::gridSize * 0.8) / 2;
                y = Board::boardMargin + y * Board::gridSize - (Board::gridSize * 0.8) / 2;

                m_stones[i]->setGeometry(x, y, (Board::gridSize * 0.8), (Board::gridSize * 0.8));
                m_stones[i]->setStyleSheet("QLabel{background: transparent; border-radius: 16px; border: 1px solid #22B14C;}");
                m_stones[i]->show();
            }
            else {
                m_stones[i]->hide();
            }
        }
    }
    else {
        displayAnalysis();
        for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
            m_stones[i]->hide();
        }
    }

    return;
}

/*
 *  ÏÔÊ¾AIÆÀ¹À½á¹û
 */
void Analysis::aiEvaluate(Gomoku::State& s) {
    m_labels_string.fill("");

    for (int i = 0; i < Gomoku::BOARD_COLOR_NUM; i++) {
        if (s.getBoard(i) == EMPTY && Gomoku_AI::evaluate_result[i] != -0x7FFFFFFF) {
            m_labels_string[i] = to_string(Gomoku_AI::evaluate_result[i]);
        }
    }

    displayAnalysis();
}