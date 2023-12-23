#include "ChessClass.h"


ChessClass::ChessClass(QWidget* parent) : QWidget(parent)
{
    w = parent;

    resize(1000, 1000);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setFocusPolicy(Qt::StrongFocus);
    
    m_action_warn = new QLabel(this);
    m_win_lable = new QLabel(this);
    state = new Chess::State();
    //m_action_warn->setStyleSheet("QLabel{background:#FF0000;}");
    //m_action_warn->setGeometry(0, 0, 0, 0);

    {
        QFont font("Times New Roman", 40, 50);
        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            m_pieces[i] = new QLabel(this);
            m_pieces[i]->setAlignment(Qt::AlignCenter);
            m_pieces[i]->setFont(font);
        }
    }
    {
        QFont font("Times New Roman", 40, 50);
        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            m_chess_actions[i] = new QLabel(this);
            m_chess_actions[i]->setFont(font);
            m_chess_actions[i]->setStyleSheet("color:Yellow");
            m_chess_actions[i]->setAlignment(Qt::AlignCenter);
        }
    }
    
    Chess::createActionSet(*state);
    displayChess(state->board);
}

/*
 *  鼠标响应
 */
void ChessClass::mousePressEvent(QMouseEvent* e) {
    char x, y;
    static int st = -1;
    
    if (e->button() == Qt::LeftButton) {    //左键按下
        y = (e->x() - BoardClass::boardMargin) / BoardClass::gridSize;
        x = (e->y() - BoardClass::boardMargin) / BoardClass::gridSize;

        if (st != -1) {
            int ed = x * BOARD_SIZE + y;

            if (st != ed) {
                for (auto e = state->action_set.begin(); e != state->action_set.end(); e++) {
                    if (e->first== st * BOARD_PIECE_NUM + ed) {
                        state->action = e->first;
                        Chess::play(*state);
                        break;
                    }
                }
                displayChess(state->board); 
            }

            st = -1;
            displayActions(*state, x * BOARD_SIZE + y);
        }
        else if (state->getBoard(x, y) != Chess::EMPTY && displayActions(*state, x * BOARD_SIZE + y)) {
            st = x * BOARD_SIZE + y;
        }
    }
}

/*
 *  键盘相应
 */
void ChessClass::keyPressEvent(QKeyEvent* event) {
    switch (event->key())    {
    case Qt::Key_M: displayOpponentControlPoint(*state); break;
    }
}

/*
 *  显示棋子
 */
void ChessClass::displayChess(std::array<Chess::Piece, BOARD_PIECE_NUM>& board) {
    QPalette pe;

    for (int i = 0; i < BOARD_PIECE_NUM; i++) {
        if (board[i] != 0) {
            int x = i / BOARD_SIZE,
                y = i % BOARD_SIZE;

            x = BoardClass::boardMargin + (x + 0.05) * BoardClass::gridSize;
            y = BoardClass::boardMargin + (y + 0.05) * BoardClass::gridSize;

            m_pieces[i]->setGeometry(y, x, BoardClass::gridSize * 0.9, BoardClass::gridSize * 0.9);

            if (board[i] > 0) 
                pe.setColor(QPalette::WindowText, Qt::black);
            else
                pe.setColor(QPalette::WindowText, Qt::red);

            m_pieces[i]->setPalette(pe);

            switch (abs(board[i])) {
            case Chess::KING:   m_pieces[i]->setText(QString::fromStdString("♚")); break;
            case Chess::QUEEN:  m_pieces[i]->setText(QString::fromStdString("♛")); break;
            case Chess::BISHOP: m_pieces[i]->setText(QString::fromStdString("♝")); break;
            case Chess::ROOK:   m_pieces[i]->setText(QString::fromStdString("♜")); break;
            case Chess::KNIGHT: m_pieces[i]->setText(QString::fromStdString("♞")); break;
            case Chess::PAWN:   m_pieces[i]->setText(QString::fromStdString("♟")); break;
            }

            m_pieces[i]->show();
        }
        else
            m_pieces[i]->hide();
    }
}

/*
 *  显示可落子点
 */
bool ChessClass::displayActions(Chess::State& s, int st) {
    static int fg = 1;
    int num = 0;

    if (fg == 1) {
        for (auto e = state->action_set.begin(); e != state->action_set.end(); e++) {
            if (abs(e->first) / 64 == st) {
                int ed = abs(e->first) % 64,
                    x = ed / BOARD_SIZE,
                    y = ed % BOARD_SIZE;

                m_chess_actions[ed]->setText((QString)"〇");
                m_chess_actions[ed]->setGeometry(
                    BoardClass::boardMargin + BoardClass::gridSize * (y + 0.1),
                    BoardClass::boardMargin + BoardClass::gridSize * (x + 0.1), 50, 50);
                m_chess_actions[ed]->show();

                num++;
            }
        }
    }
    else {
        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            m_chess_actions[i]->hide();
        }
    }
    
    fg = -fg;

    if (num == 0) {
        fg = 1;
        return false;
    }
    return true;
}

/*
 *  显示对方控制点
 */

void opponentControlPoint(Chess::State& s, std::array<int, BOARD_PIECE_NUM>& mark, int player);

void ChessClass::displayOpponentControlPoint(Chess::State& s) {
    static int fg = 0;
    static QLabel ** labels = new QLabel * [BOARD_PIECE_NUM];

    if (fg == 0) {
        QFont font("Arial", 80, 50);
        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            labels[i] = new QLabel(this);
            labels[i]->setFont(font);
            labels[i]->setStyleSheet("color:Yellow");
            labels[i]->setAlignment(Qt::AlignCenter);
            labels[i]->hide();
        }
        fg = 1;
    }

    if (fg == 1) {
        std::array<int, BOARD_PIECE_NUM> mark;
        opponentControlPoint(*state, mark, -s.player);

        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            if (mark[i] > 0) {
                int x = i / BOARD_SIZE,
                    y = i % BOARD_SIZE;

                labels[i]->setText((QString)"×");
                labels[i]->setGeometry(
                    BoardClass::boardMargin + BoardClass::gridSize * (y + 0.1),
                    BoardClass::boardMargin + BoardClass::gridSize * (x + 0.1), 50, 50);
                labels[i]->show();
            }
        }
    }
    else {
        for (int i = 0; i < BOARD_PIECE_NUM; i++) {
            labels[i]->hide();
        }
    }
    fg = -fg;
}

void opponentControlPoint(Chess::State& s, std::array<int, BOARD_PIECE_NUM>& mark, int player) {
    mark.fill(0);

    for (int i = 0; i < BOARD_PIECE_NUM; i++) {
        if (s.board[i] * player > 0) {
            int x = i / BOARD_SIZE,
                y = i % BOARD_SIZE,
                p = s.board[i];

            switch (abs(p)) {
            case Chess::KING: {
                for (int j = 0; j < 8; j++) {
                    int xt = x + Chess::x_step[j],
                        yt = y + Chess::y_step[j];

                    if (xt < 0 || xt >= BOARD_SIZE ||
                        yt < 0 || yt >= BOARD_SIZE)
                        continue;

                    mark[xt * BOARD_SIZE + yt] += 1;
                }

            } break;
            case Chess::QUEEN: case Chess::BISHOP: case Chess::ROOK: {
                int j_st = abs(p) == Chess::BISHOP ? 4 : 0,
                    j_ed = abs(p) == Chess::ROOK ? 4 : 8;

                for (int j = j_st; j < j_ed; j++) {
                    int t = 0;

                    while (++t) {
                        int xt = x + t * Chess::x_step[j],
                            yt = y + t * Chess::y_step[j];

                        if (xt < 0 || xt >= BOARD_SIZE ||
                            yt < 0 || yt >= BOARD_SIZE)
                            break;

                        if (s.getBoard(xt, yt) != Chess::EMPTY) {
                            mark[xt * BOARD_SIZE + yt] += 1;
                            break;
                        }

                        mark[xt * BOARD_SIZE + yt] += 1;
                    }
                }
            } break;
            case Chess::KNIGHT: {
                for (int j = 4; j < 8; j++) {
                    // (2, 1)
                    int xt = x + Chess::x_step[j] * 2,
                        yt = y + Chess::y_step[j] * 1;

                    if (!(xt < 0 || xt >= BOARD_SIZE ||
                          yt < 0 || yt >= BOARD_SIZE))
                        mark[xt * BOARD_SIZE + yt] += 1;

                    // (1, 2)
                    xt = x + Chess::x_step[j] * 1,
                    yt = y + Chess::y_step[j] * 2;

                    if (!(xt < 0 || xt >= BOARD_SIZE ||
                        yt < 0 || yt >= BOARD_SIZE))
                        mark[xt * BOARD_SIZE + yt] += 1;
                }
            } break;
            case Chess::PAWN: {
                int x_ = x + (p > 0 ? -1 : +1);
                if(y - 1 >= 0)
                    mark[x_ * BOARD_SIZE + (y - 1)] += 1;
                if (y + 1 < BOARD_SIZE)
                    mark[x_ * BOARD_SIZE + (y + 1)] += 1;
            }  break;
            }
        }
    }
}