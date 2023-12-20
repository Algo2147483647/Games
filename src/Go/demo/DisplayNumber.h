
void openAI();
void aiEvaluate();
void aiEvaluate_visit();
void displayQi(Go::State& s);
void displayMark(Go::State& s);
void displayNumber(Go::State& s);

//GoAI::evaluate_result.resize(BOARD_COLOR_NUM, 0);
//GoAI::evaluate_visit. resize(BOARD_COLOR_NUM, 0);

void Stone::openAI() {
    //static ThreadClass ai;
    static QThread thread;

    if (ai_is_open == 0) {
        ai_is_open = 1;
        //ai.s = state;

       // QObject::connect(&thread, &QThread::started, &ai, &ThreadClass::openAI);
        //ai.moveToThread(&thread);
        //thread.start();
    }
    return;
}

/*
 *  显示AI评估结果
 */
void Stone::aiEvaluate() {
    static int fg = 0;
    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
    static QFont font("Times New Roman", 12, 50);

    if (fg == 0) {
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            labels[i] = new QLabel(w);
            labels[i]->setFont(font);
            labels[i]->setAlignment(Qt::AlignCenter);
        }
        fg = 1;
    }

    float maxn = -0x7FFFFFFF;
    int maxi = 0;

    if (fg == 1) {
        //GoAI::evaluate_fg = 1;
        QThread::msleep(50);

        //for (int i = 0; i < BOARD_COLOR_NUM; i++)
            //if (state->mark[i] == -1 && maxn < GoAI::evaluate_result[i]) {
                //maxn = GoAI::evaluate_result[i];
                //maxi = i;
            //} 
    }

    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if ((state->mark[i] == -1) && fg == 1) {
            int x = i % BOARD_SIZE,
                y = i / BOARD_SIZE;
            //v = GoAI::evaluate_result[i] * 100

            if (i == maxi)
                labels[i]->setStyleSheet("color:Red");
            else
                labels[i]->setStyleSheet("color:Blue");

            //labels[i]->setText(QString::fromStdString(to_string(v)));
            labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            labels[i]->show();
        }
        else
            labels[i]->hide();
    }
    fg = -fg;
}

/*
 *  显示AI评估结果
 */
void Stone::aiEvaluate_visit() {
    static int fg = 0;
    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
    static QFont font("Times New Roman", 8, 50);

    if (fg == 0) {
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            labels[i] = new QLabel(w);
            labels[i]->setFont(font);
            labels[i]->setAlignment(Qt::AlignCenter);
            labels[i]->setStyleSheet("color:Blue");
        }
        fg = 1;
    }

    if (fg == 1) {
        //GoAI::evaluate_fg = 1;
        QThread::msleep(50);
    }

    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if ((state->mark[i] == -1) && fg == 1) {
            int x = i % BOARD_SIZE,
                y = i / BOARD_SIZE;
            //v = GoAI::evaluate_visit[i]

        //labels[i]->setText(QString::fromStdString(to_string(v)));
            labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            labels[i]->show();
        }
        else
            labels[i]->hide();
    }
    fg = -fg;
}


/*
 *  显示气数
 */
void Stone::displayQi(Go::State& s) {
    static int fg = 0;
    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
    static QFont font("Times New Roman", 15, 50);

    if (fg == 0) {
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            labels[i] = new QLabel(w);
            labels[i]->setFont(font);
            labels[i]->setStyleSheet("color:White");
            labels[i]->setAlignment(Qt::AlignCenter);
        }
        fg = 1;
    }

    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if (s.board[i] != 0 && fg == 1) {
            int x = i % BOARD_SIZE,
                y = i / BOARD_SIZE;

            labels[i]->setText(QString::fromStdString(to_string(s.qi[s.mark[i]])));
            labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            labels[i]->show();
        }
        else {
            labels[i]->hide();
        }
    }
    fg = -fg;
}

/*
 *  显示棋块标记
 */
void Stone::displayMark(Go::State& s) {
    static int fg = 0;
    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
    static QFont font("Times New Roman", 15, 50);

    if (fg == 0) {
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            labels[i] = new QLabel(w);
            labels[i]->setFont(font);
            labels[i]->setAlignment(Qt::AlignCenter);
        }
        fg = 1;
    }

    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if (s.mark[i] >= 0 && fg == 1) {
            int x = i % BOARD_SIZE,
                y = i / BOARD_SIZE;

            labels[i]->setText(QString::fromStdString(to_string(s.mark[i])));
            labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            labels[i]->setStyleSheet("color:White");
            labels[i]->show();
        }
        else {
            labels[i]->hide();
        }
    }
    fg = -fg;
}
/*
 *  显示手数
 */
void Stone::displayNumber(Go::State& s) {
    static int fg = 0, number[BOARD_COLOR_NUM];
    static QLabel** labels = new QLabel * [BOARD_COLOR_NUM];
    static QFont font("Times New Roman", 15, 50);

    if (fg == 0) {
        for (int i = 0; i < BOARD_COLOR_NUM; i++) {
            labels[i] = new QLabel(w);
            labels[i]->setFont(font);
            labels[i]->setStyleSheet("color:White");
            labels[i]->setAlignment(Qt::AlignCenter);
        }
        fg = 1;
    }

    memset(number, 0, sizeof(int) * BOARD_COLOR_NUM);
    Go::State* s_ = &s;
    int num = 0, sum = 0;

    /*
    while (s_ != NULL) {
        num--;
        sum++;

        if(s.board[s_->action] != 0 && number[s_->action] == 0)
            number[s_->action] = num;

        s_ = s_->parent;
    }*/

    for (int i = 0; i < BOARD_COLOR_NUM; i++) {
        if (number[i] != 0)
            number[i] += sum;

        if (s.board[i] != 0 && fg == 1) {
            int x = i % BOARD_SIZE,
                y = i / BOARD_SIZE;

            labels[i]->setText(QString::fromStdString(to_string(number[i])));
            labels[i]->setGeometry(
                Board::boardMargin + Board::gridSize * (x - 0.36),
                Board::boardMargin + Board::gridSize * (y - 0.35), 30, 30);
            labels[i]->show();
        }
        else {
            labels[i]->hide();
        }
    }
    fg = -fg;
}

void Stone::mousePressEvent(QMouseEvent* e) {
    signed char x, y;

    if (e->button() == Qt::LeftButton) {    //左键按下
        x = (e->x() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;
        y = (e->y() - Board::boardMargin + Board::gridSize / 2) / Board::gridSize;

        Go::play(*state, y * BOARD_SIZE + x);

        displayStone(state->board);
        displayWin();

        //if (ai_is_open)
            //GoAI::move_pos = y * BOARD_SIZE + x;

        StoneWarn->setGeometry(
            Board::boardMargin + x * Board::gridSize - stoneSize / 2,
            Board::boardMargin + y * Board::gridSize - stoneSize / 2,
            4, 4
        );
    }
    else if (e->button() == Qt::RightButton) {

    }
    else if (e->button() == Qt::MiddleButton) {

        displayStone(state->board);
    }
}

/*
 *  键盘相应
 */
void Stone::keyPressEvent(QKeyEvent* event) {

    switch (event->key()) {
    case Qt::Key_A: openAI(); break;
    case Qt::Key_S: aiEvaluate(); break;
    case Qt::Key_D: aiEvaluate_visit(); break;
    case Qt::Key_Q: displayQi(*state); break;
    case Qt::Key_M: displayMark(*state); break;
    case Qt::Key_N: displayNumber(*state); break;
    case Qt::Key_P: {
        QMessageBox pass(QMessageBox::NoIcon, "Confirm Pass?", "Do you want to Pass?",
            QMessageBox::Ok | QMessageBox::Cancel);

        if (pass.exec() == QMessageBox::Ok) {
            Go::play(*state, PASS);
            displayWin();

            if (ai_is_open) {
                //GoAI::move_pos = -1;
            }
        }
    } break;
    }
}
