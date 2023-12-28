#pragma once

#include "ui_gameWindow.h"
#include "EndGamewindow.h"
#include "Client.h"

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QMap>
#include <QColor>
#include <QBuffer>


class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
    GameWindow(const std::string& username,QWidget* parent = nullptr);
    ~GameWindow();
    //std::vector<std::vector<int>> pixelMatrix; 

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;


private:
    inline static const uint16_t WIDTH{ 800 };
    inline static const uint16_t HEIGHT{ 600 };

private:
    void ResizeToScreenSize();
    QByteArray serializeDrawing();
    void setReceivedDrawing(const QPixmap& pixmap);
    QPixmap receivedDrawing;
    void addNewLine(const QVector<QPoint>& newLine);
    void ChangePenColor();
    void UpdateWordCensorship(char letter, int position);
    void CheckGameStatus();
    void ShowPointWindow();
    void ShowEndWindow();

private:
	void StartTurn();
    void ClearChat();
	std::string WordToCensor(std::string word);

private slots:
    void SendButton_Clicked();
    void InputField_ReturnPressed();
    void UpdateCharCount();
    void UpdatePenWidth();
    void ClearDrawingArea();

private:
    Ui::gameWindowClass ui;
    QVector<QVector<QPoint>> m_lines; 
    QVector<QPoint> m_currentLine; 
    int m_currentPenWidth;
    QMap<int, int> m_lineWidths; 
    QMap<int, QColor> m_lineColor;
    int m_lastUpdatedLineIndex = -1;
    QColor m_currentPenColor; 
   
private:

    bool m_isDrawing;
    bool m_gameEnded;
    bool m_turnEnded;
    Client m_client;
    std::string m_username;
    std::vector<std::string> m_players;
	std::string m_wordToCensor;
    uint8_t m_oldPosition=-1;
    uint8_t m_newPosition=-1;
};
