#include "Controller.h"

Controller::Controller(QWidget* parent) : QWidget(parent) {
    resize(Board::gridSize * (Gomoku::BOARD_SIZE + 0.5), Board::gridSize * (Gomoku::BOARD_SIZE + 0.5));
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::StrongFocus);

    m_winLabel = new QLabel(this);

    state = new Gomoku::State();
    m_state_history.push_back(*state);
}

void Controller::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        signed char x = (event->x() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
        signed char y = (event->y() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;

        Gomoku::play(*state, x, y);
        m_state_history.push_back(*state);
        stone->displayStone(state->board);
        displayWin();
    }
    else if (event->button() == Qt::MiddleButton) {
        if (m_state_history.size() >= 2) {
            *state = m_state_history[m_state_history.size() - 2];
            m_state_history.pop_back();
        }
        stone->displayStone(state->board);
    }
}

void Controller::keyPressEvent(QKeyEvent* event) {
    switch (event->key()) {
    case Qt::Key_A: {
        QMessageBox pass(QMessageBox::NoIcon, "Confirm AI?", "Open AI?", QMessageBox::Ok | QMessageBox::Cancel);

        if (pass.exec() == QMessageBox::Ok) {
            analysis->openAI(*state);
        }
    } break;
    case Qt::Key_S: analysis->aiEvaluate(*state); break;
    case Qt::Key_N: analysis->displaySerialNumber(m_state_history); break;
    }
}

void Controller::displayWin() {
    Color res = state->isTermination();

    if (res != EMPTY) {
        // Use a more modern and appealing font, adjust size and boldness as needed
        QFont font("Arial", 60, QFont::Bold);
        m_winLabel->setFont(font);

        // Set the geometry to center the label in the window
        int labelWidth = 1000;
        int labelHeight = 100;
        int windowCenterX = this->width() / 2;
        int windowCenterY = this->height() / 2;
        m_winLabel->setGeometry(windowCenterX - labelWidth / 2, windowCenterY - labelHeight / 2, labelWidth, labelHeight);

        // Align text to the center
        m_winLabel->setAlignment(Qt::AlignCenter);

        // Set a background color and text color for better visibility
        m_winLabel->setStyleSheet("QLabel { background-color : black; color : white; }");

        if (res == Gomoku::BLACK)
            m_winLabel->setText("BLACK  Wins!");
        else if (res == Gomoku::WHITE)
            m_winLabel->setText("WHITE  Wins!");
    }
}
