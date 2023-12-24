#pragma once

#include "ui_gameWindow.h"
#include "EndGamewindow.h"
#include "Client.h"

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include<QMap>
#include <QColor>
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

private:

    void resizeToScreenSize();
    void addNewLine(const QVector<QPoint>& newLine);
    void changePenColor();
    void UpdateWordCensorship(char letter, int position);
    void checkGameStatus();
    void ShowPointWindow();
    void ShowEndWindow();

private:

	void StartTurn();
    void ClearChat();
	std::string WordToCensor(std::string word);

private slots:
    void sendButton_clicked();
    void inputField_returnPressed();
    void updateCharCount();
    void updatePenWidth();
    void clearDrawingArea();

private:
    Ui::gameWindowClass ui;
    QVector<QVector<QPoint>> lines; 
    QVector<QPoint> currentLine; 
    int currentPenWidth;
    QMap<int, int> lineWidths; 
    QMap<int, QColor> lineColor;
    int lastUpdatedLineIndex = -1;
    QColor currentPenColor; 
   
private:
    bool isDrawing;
    bool m_gameEnded;
    bool m_turnEnded;
    Client m_client;
    std::string m_username;
    std::vector<std::string> m_players;
	std::string m_wordToCensor;
};
