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

    QPainter painter(this);
    painter.drawPixmap(0, 0, this->width(), this->height(), QPixmap("../../../asset/background.png"));

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
    painter.setPen(QPen(QColor("#4D4E55"), 2));
    painter.setBrush(Qt::transparent);

    for (auto& e : core->pillars->pillarHoles) {
        // 上半部分
        QRectF upperRect(e.first, e.second + core->pillars->hole_size, core->pillars->pillar_width, windows_size_height - (e.second + core->pillars->hole_size) );
        QLinearGradient gradient(upperRect.topLeft(), upperRect.topRight());
        gradient.setColorAt(0, QColor("#7D9844"));
        gradient.setColorAt(0.2, QColor("#E2FB89"));
        gradient.setColorAt(0.35, QColor("#E2FB89"));
        gradient.setColorAt(0.65, QColor("#8DB04B"));
        gradient.setColorAt(1, QColor("#548021"));
        painter.fillRect(upperRect, gradient);
        painter.drawRect(upperRect);

        // 下半部分
        QRectF lowerRect(e.first, 0, core->pillars->pillar_width, e.second - core->pillars->hole_size);
        painter.fillRect(lowerRect, gradient);
        painter.drawRect(lowerRect);
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