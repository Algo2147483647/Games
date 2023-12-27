#ifndef FLAPPYBIRD_DEMO_H
#define FLAPPYBIRD_DEMO_H

#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QPainter>
#include "./core/FlappyBird.h"
#include "./ai/ai.h"

class FlappyBirdDemo : public QMainWindow {
    Q_OBJECT
public:
    QTimer* timer;
    FlappyBird* core;

    int birdSize = 10;

    FlappyBirdDemo(QWidget* parent = nullptr);
protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateGame();
};
#endif // !FLAPPYBIRD_DEMO_H