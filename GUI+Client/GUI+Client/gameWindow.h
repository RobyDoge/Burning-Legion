#pragma once

#include <QMainWindow>
#include "ui_gameWindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
const int WIDTH = 800; 
const int HEIGHT = 600;

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

private slots:
    void on_sendButton_clicked();
    void on_inputField_returnPressed();
    void updateCharCount();

private:
    Ui::gameWindowClass ui;
    QVector<QVector<QPoint>> lines; 
    QVector<QPoint> currentLine; 
    void resizeToScreenSize();
    bool isDrawing; 
};
