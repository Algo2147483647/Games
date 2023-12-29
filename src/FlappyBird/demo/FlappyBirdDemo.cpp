#include "FlappyBirdDemo.h"

FlappyBirdDemo::FlappyBirdDemo(QWidget* parent) : QMainWindow(parent) {
    setFixedSize(windows_size_width, windows_size_height);
    setWindowTitle("Flappy Bird");
    setWindowOpacity(0.8);
    setFocusPolicy(Qt::StrongFocus);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FlappyBirdDemo::updateGame);
    timer->start(20);
    core = new FlappyBird(windows_size_width, windows_size_height);

    m_terminationLabel = new QLabel(this);
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
    font.setBold(true);
    painter.setFont(font);
    QTransform transform;
    transform.scale(-1, 1);
    painter.setTransform(transform);

    QFontMetrics fontMetrics(painter.font());
    QString text = "🕊️";
    int textWidth = fontMetrics.horizontalAdvance(text);
    int textHeight = fontMetrics.height();
    int centerX = -core->bird->position.first - textWidth / 2;
    int centerY = windows_size_height - core->bird->position.second + textHeight / 3;
    painter.drawText(centerX, centerY, text);

    painter.setBrush(Qt::red);
    painter.setPen(Qt::red);
    painter.drawEllipse(-core->bird->position.first, windows_size_height - core->bird->position.second, 1, 1);
}

void FlappyBirdDemo::drawPillars() {
    QPainter painter(this);
    painter.setPen(QPen(QColor("#4D4E55"), 2));
    painter.setBrush(Qt::transparent);

    for (auto& e : core->pillars->pillarHoles) {
        float y = windows_size_height - e.second;
        {
            // 上半部分
            QRectF upperRect(e.first, y + core->pillars->hole_size_half, core->pillars->pillar_width, windows_size_height - (y + core->pillars->hole_size_half));
            QLinearGradient gradient(upperRect.topLeft(), upperRect.topRight());
            gradient.setColorAt(0, QColor("#7D9844"));
            gradient.setColorAt(0.2, QColor("#E2FB89"));
            gradient.setColorAt(0.35, QColor("#E2FB89"));
            gradient.setColorAt(0.65, QColor("#8DB04B"));
            gradient.setColorAt(1, QColor("#548021"));
            painter.fillRect(upperRect, gradient);
            painter.drawRect(upperRect);

            // 下半部分
            QRectF lowerRect(e.first, 0, core->pillars->pillar_width, y - core->pillars->hole_size_half);
            painter.fillRect(lowerRect, gradient);
            painter.drawRect(lowerRect);
        }
        {
            // 上半部分
            QRectF upperRect(e.first - 5, y + core->pillars->hole_size_half - 10, core->pillars->pillar_width + 10, 10);
            QLinearGradient gradient(upperRect.topLeft(), upperRect.topRight());
            gradient.setColorAt(0, QColor("#7D9800"));
            gradient.setColorAt(0.2, QColor("#E2FB00"));
            gradient.setColorAt(0.35, QColor("#E2FB00"));
            gradient.setColorAt(0.65, QColor("#8DB000"));
            gradient.setColorAt(1, QColor("#548000"));
            painter.fillRect(upperRect, gradient);
            painter.drawRect(upperRect);

            // 下半部分
            QRectF lowerRect(e.first - 5, y - core->pillars->hole_size_half - 10, core->pillars->pillar_width + 10, 10);
            painter.fillRect(lowerRect, gradient);
            painter.drawRect(lowerRect);
        }
    }
}

void FlappyBirdDemo::displayTermination() {
    // Use a more modern and appealing font, adjust size and boldness as needed
    QFont font("Arial", 50, QFont::Bold);
    m_terminationLabel->setFont(font);

    // Set the geometry to center the label in the window
    int labelWidth = 1000;
    int labelHeight = 100;
    int windowCenterX = this->width() / 2;
    int windowCenterY = this->height() / 2;
    m_terminationLabel->setGeometry(windowCenterX - labelWidth / 2, windowCenterY - labelHeight / 2, labelWidth, labelHeight);
    m_terminationLabel->setAlignment(Qt::AlignCenter);

    // Set the background color to red and 50% opacity
    m_terminationLabel->setStyleSheet("QLabel { background-color: rgba(255, 0, 0, 0.5); color: white; }");
    m_terminationLabel->setText("Termination!");
}

void FlappyBirdDemo::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Space) {
        action = 1;
    }
}

void FlappyBirdDemo::updateGame() {
    termination = !core->play(action);
    action = 0;
    update();

    if (termination) {
        timer->stop();
        displayTermination();
    }
}