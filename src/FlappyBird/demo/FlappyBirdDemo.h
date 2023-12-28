#ifndef FLAPPYBIRD_DEMO_H
#define FLAPPYBIRD_DEMO_H

#include <QtWidgets/QMainWindow>  
#include <QPainter>
#include <QWidget>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include "./core/FlappyBird.h"
#include "./ai/ai.h"

class FlappyBirdDemo : public QMainWindow {
    Q_OBJECT
public:
    int windows_size_width  = 500;
    int windows_size_height = 500;

    QTimer* timer;
    FlappyBird* core;

    FlappyBirdDemo(QWidget* parent = nullptr);
    void drawBird();
    void drawPillars();

protected:
    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void updateGame();
};
#endif // !FLAPPYBIRD_DEMO_H