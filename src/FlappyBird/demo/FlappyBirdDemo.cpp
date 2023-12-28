#include "FlappyBirdDemo.h"

FlappyBirdDemo::FlappyBirdDemo(QWidget* parent) : QMainWindow(parent) {
    setFixedSize(windows_size_width, windows_size_height);
    setWindowTitle("Flappy Bird");
    setWindowOpacity(0.8);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlappyBirdDemo::updateGame);
    timer->start(100);

    core = new FlappyBird(windows_size_width, windows_size_height);
}

void FlappyBirdDemo::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);

    drawBird();
    drawPillars();
}

void FlappyBirdDemo::drawBird() {
    QPainter painter(this);
    QFont font;
    font.setPointSize(36);
    painter.setFont(font);
    QTransform transform;
    transform.scale(-1, 1);
    painter.setTransform(transform);
    painter.drawText(-core->bird->position.first, 500 - core->bird->position.second, "🕊️");
}

void FlappyBirdDemo::drawPillars() {
    QPainter painter(this);
    painter.setPen(Qt::NoPen);  // 设置画笔为透明，不绘制边框
    painter.setBrush(Qt::green);

    for (auto& e : core->pillars->pillarHoles) {
        // 上半部分
        QRectF upperRect(e.first, e.second + core->pillars->hole_size, core->pillars->pillar_width, windows_size_height);
        QLinearGradient upperGradient(upperRect.topLeft(), upperRect.bottomLeft());
        upperGradient.setColorAt(0, Qt::darkGreen);
        upperGradient.setColorAt(0.5, Qt::green);
        upperGradient.setColorAt(1, Qt::darkGreen);
        painter.fillRect(upperRect, upperGradient);

        // 下半部分
        QRectF lowerRect(e.first, 0, core->pillars->pillar_width, e.second - core->pillars->hole_size);
        QLinearGradient lowerGradient(lowerRect.topLeft(), lowerRect.bottomLeft());
        lowerGradient.setColorAt(0, Qt::darkGreen);
        lowerGradient.setColorAt(0.5, Qt::green);
        lowerGradient.setColorAt(1, Qt::darkGreen);
        painter.fillRect(lowerRect, lowerGradient);
    }
}

void FlappyBirdDemo::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        core->play(1);
    }
}

void FlappyBirdDemo::updateGame() {
    core->play(0);
    update();
}