#include "Stone.h"

Stone::Stone(QWidget* parent) : QWidget(parent) {
    resize(1000, 1000);
    setAttribute(Qt::WA_TranslucentBackground, true);

    m_stoneWarn->setStyleSheet("QLabel{background:#FF0000;}");
    m_stoneWarn->setGeometry(0, 0, 0, 0);

    for (int i = 0; i < BOARD_COLOR_NUM; i++)
        m_stones[i] = new QLabel(this);

    setFocusPolicy(Qt::StrongFocus); 

    Go::go_init();
    state = new Go::State();
}

void Stone::mousePressEvent(QMouseEvent* e) {
    if (e->button() == Qt::LeftButton) {
        signed char x = (e->x() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
        signed char y = (e->y() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;

        Go::play(*state, y * BOARD_SIZE + x);
        displayStone(state->board);
        m_stoneWarn->setGeometry(
            Board::boardMargin + x * Board::gridSize - stoneSize / 2,
            Board::boardMargin + y * Board::gridSize - stoneSize / 2,
            4, 4
        );
    }
    else if (e->button() == Qt::MiddleButton) {
        displayStone(state->board);
    }
}

void Stone::keyPressEvent(QKeyEvent* event) {
    switch (event->key())    {
    case Qt::Key_P: {
        QMessageBox pass(QMessageBox::NoIcon, "Confirm Pass?", "Do you want to Pass?",
            QMessageBox::Ok | QMessageBox::Cancel);

        if (pass.exec() == QMessageBox::Ok) {
            Go::play(*state, PASS);
            displayStone(state->board);
        }
    } break;
    }
}

void Stone::displayWin() {
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
}

void Stone::displayStone(array<Go::Color, BOARD_COLOR_NUM>& board) {
    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if (board[i] != 0) {
            int x = i % BOARD_SIZE;
            int y = i / BOARD_SIZE;
            x = Board::boardMargin + x * Board::gridSize - stoneSize / 2;
            y = Board::boardMargin + y * Board::gridSize - stoneSize / 2;

            m_stones[i]->setGeometry(x, y, stoneSize, stoneSize);
            
            if (board[i] == Go::BLACK)
                m_stones[i]->setStyleSheet("QLabel{background:#000000; border-radius: 16px; border:0px solid black;}");
            else
                m_stones[i]->setStyleSheet("QLabel{background:#FF0000; border-radius: 16px; border:0px solid #FF0000;}");

            m_stones[i]->show();
        }
        else {
            m_stones[i]->hide();
        }
    }
    displayWin();
}
