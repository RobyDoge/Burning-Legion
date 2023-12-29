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
    inline static constexpr uint16_t WIDTH{ 800 };
    inline static constexpr uint16_t HEIGHT{ 600 };
    constexpr int m_xPos { (width() - WIDTH) / 2 };
    constexpr int m_yPos { (height() - HEIGHT) / 2 };

private:
    void ResizeToScreenSize();
    QByteArray SerializeDrawing();
    void SetReceivedDrawing(const QPixmap& pixelMap);
    void AddNewLine(const QVector<QPoint>& newLine);
    void ChangePenColor();
    void UpdateWordCensorship(char letter, int position);
    void CheckGameStatus();
    void ShowPointWindow();
    void ShowEndWindow();

private:
	void StartTurn();
    void ClearChat() const;
	std::string WordToCensor(std::string word);

private slots:
    void SendButton_Clicked();
    void InputField_ReturnPressed();
    void UpdateCharCount() const;
    void UpdatePenWidth();
    void ClearDrawingArea();

private:
    /*those are unused for now
    *
    *int m_lastUpdatedLineIndex = -1;
	*bool m_gameStatus;
	*bool m_turnEnded;
    *std::vector<std::string> m_players;
    */

private:
    Client m_client;
    Ui::gameWindowClass ui;
    std::string m_username;
    std::string m_wordToCensor;

    bool m_isDrawing{ false };
    bool m_isDrawer{ false };
    uint8_t m_previousDrawerPosition{ 255 };
    uint8_t m_currentDrawerPosition{ 255 };
    QPixmap m_receivedDrawing{};

    QVector<QVector<QPoint>> m_lines;
    QVector<QPoint> m_currentLine;
    QColor m_currentPenColor;
    int m_currentPenWidth;
    QMap<int, int> m_lineWidths;
    QMap<int, QColor> m_lineColor;

};
