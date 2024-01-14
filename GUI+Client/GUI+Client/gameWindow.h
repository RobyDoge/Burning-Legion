#pragma once

#include "ui_gameWindow.h"
#include "EndGamewindow.h"
#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QMap>
#include <QColor>
#include <QBuffer>
#include<algorithm>

class GameWindow : public QMainWindow
{
	Q_OBJECT

public:
    GameWindow(const std::string& username,QWidget* parent = nullptr);
    ~GameWindow() = default;
    void SetReceivedDrawing(const QPixmap& pixelMap);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    inline static constexpr uint16_t WIDTH{ 800 };
    inline static constexpr uint16_t HEIGHT{ 600 };

private:
    void ResizeToScreenSize();
    void ChangePenColor();
    void UpdateWordCensorship(char letter, int position);
    void CheckGameStatus();
    void ShowPointWindow();
    void ShowEndWindow();
    void UpdatePlayerMessages();
    void RevealRandomLetters();
    void DisplayPlayers() const;
    void StartDrawingThread();
	void StartTurn();
    void ClearChat() const;
	void CensoredWord();

private slots:
    void SendButton_Clicked();
    void InputField_ReturnPressed();
    void UpdateCharCount() const;
    void UpdatePenWidth();
    void ClearDrawingArea();

private:
    Ui::gameWindowClass ui;
    std::string m_username;
    std::string m_censoredWord;
    std::string m_guessWord;

    bool m_isDrawing{ false };
    bool m_isDrawer{ false };
    uint8_t m_previousDrawerPosition{ 255 };
    uint8_t m_currentDrawerPosition{ 255 };
    QPixmap m_receivedDrawing{};
    std::atomic<bool> m_stopThread{};

    QVector<QVector<QPoint>> m_lines{};
    QVector<QPoint> m_currentLine{};
    QColor m_currentPenColor{};
    int m_currentPenWidth{};
    QMap<int, int> m_lineWidths{};
    QMap<int, QColor> m_lineColor{};
    
	bool m_gameEnded{ false };
    uint8_t m_currentTime{};

    QString m_currentPlayerGuess{};
    QString m_lastPlayerGuess{};
    QString m_playerMessage{};
    QImage m_receivedImage{};
    QImage m_capturedImage{};
    std::string m_imgString{};

    int m_xPos;
    int m_yPos;
};
