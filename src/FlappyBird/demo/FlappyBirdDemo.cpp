#include "FlappyBirdDemo.h"

FlappyBirdDemo::FlappyBirdDemo(QWidget* parent) : QMainWindow(parent) {
    setFixedSize(400, 400);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlappyBirdDemo::updateGame);
    timer->start(20);

    core = new FlappyBird(500, 500);
}

int main_() {
    FlappyBird game(500, 500);
    QLearning ai(game.windows_size.second * game.windows_size.first, 2);


    while (true) {
        int i = 0;
        game.init();
        while (true) {
            // play
            int dx = game.pillars->pillarHoles[0].first;
            int dy = game.bird->position.second - game.pillars->pillarHoles[0].second;
            int state = dy * game.windows_size.first + dx;
            int action = ai.chooseAction(state);
            int isSuccess = game.play(action);

            // feedback ai
            double R = 1;
            if (!isSuccess)
                R = -100;
            else if (game.pillars->pillarHoles[0].first <= -game.pillars->pillar_width)
                R = 15;
            ai.feedback(state, action, R);

            i++;
            if (!isSuccess)
                break;
        }printf("%d ", i++);
    }
}

void FlappyBirdDemo::paintEvent(QPaintEvent* event) override {
    Q_UNUSED(event);

    QPainter painter(this);

    // »æÖÆ±³¾°
    painter.fillRect(rect(), Qt::white);

    // »æÖÆÐ¡Äñ
    painter.setBrush(Qt::blue);
    painter.drawEllipse(core->bird->position.first, core->bird->position.second, birdSize, birdSize);
}

void FlappyBirdDemo::keyPressEvent(QKeyEvent* event) override {
    if (event->key() == Qt::Key_Space) {
        core->play(1);
    }
}

void FlappyBirdDemo::updateGame() {
    update();
}