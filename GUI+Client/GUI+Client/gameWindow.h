#pragma once

#include <QMainWindow>
#include "ui_gameWindow.h"
#include <QPainter>
#include <QMouseEvent>
const int MATRIX_WIDTH = 640; 
const int MATRIX_HEIGHT = 480;

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
    GameWindow(QWidget* parent = nullptr);
    ~GameWindow();
    //std::vector<std::vector<int>> pixelMatrix; 

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    Ui::gameWindowClass ui;
    QVector<QVector<QPoint>> lines; 
    QVector<QPoint> currentLine; 
    bool isDrawing; 
};
