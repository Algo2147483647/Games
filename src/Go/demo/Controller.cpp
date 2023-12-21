#include "Controller.h"

Controller::Controller(QWidget* parent) : QWidget(parent) {
    resize(1000, 1000);
    setAttribute(Qt::WA_TranslucentBackground, true);

    setFocusPolicy(Qt::StrongFocus);

    Go::go_init();
    state = new Go::State();
    m_state_history.push_back(*state);
}

void Controller::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        signed char x = (event->x() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
        signed char y = (event->y() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;

        Go::play(*state, y * BOARD_SIZE + x);
        m_state_history.push_back(*state);
        stone->displayStone(state->board);
    }
    else if (event->button() == Qt::MiddleButton) {
        stone->displayStone(state->board);
    }
}

void Controller::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
        //case Qt::Key_A: analysis.openAI(); break;
        //case Qt::Key_S: analysis.aiEvaluate(); break;
        //case Qt::Key_D: analysis.aiEvaluate_visit(); break;
    case Qt::Key_Q: analysis->displayQi(*state); break;
    case Qt::Key_M: analysis->displayMark(*state); break;
    case Qt::Key_N: analysis->displaySerialNumber(m_state_history); break;
    case Qt::Key_P: {
        QMessageBox pass(QMessageBox::NoIcon, "Confirm Pass?", "Do you want to Pass?",
            QMessageBox::Ok | QMessageBox::Cancel);

        if (pass.exec() == QMessageBox::Ok) {
            Go::play(*state, PASS);
            m_state_history.push_back(*state);
            //displayWin();

            if (analysis->is_ai_open) {
                //GoAI::move_pos = -1;
            }
        }
    } break;
    }
}