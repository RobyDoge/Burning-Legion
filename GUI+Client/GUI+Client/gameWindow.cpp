#include "gameWindow.h"

GameWindow::GameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAttribute(Qt::WA_StaticContents); 
    isDrawing = false;
    resizeToScreenSize();
}

GameWindow::~GameWindow()
{}
void GameWindow::resizeToScreenSize() {
    QScreen* primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    resize(screenGeometry.width(), screenGeometry.height());
    setFixedSize(screenGeometry.width(), screenGeometry.height());
}
void GameWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        int xPos = (width() - WIDTH) / 2; 
        int yPos = (height() - HEIGHT) / 2; 

        QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
        if (drawingArea.contains(event->pos()))
        {
            currentLine.clear();
            currentLine.append(event->pos());
            isDrawing = true;
        }
    }
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton && isDrawing) {

        int xPos = (width() - WIDTH) / 2; 
        int yPos = (height() - HEIGHT) / 2; 

        QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
        if (drawingArea.contains(event->pos())) {
            QPoint currentPos = event->pos();

            if (!currentLine.empty()) 
                QPoint lastPoint = currentLine.back();
                
            

            currentLine.append(currentPos);
            update();
        }
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDrawing) {
        isDrawing = false; 
        lines.append(currentLine); // Save the current line to the list of lines
        currentLine.clear(); // Clear the current line's points after finishing
    }
}

void GameWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 

    int xPos = (width() - WIDTH) / 2; 
    int yPos = (height() - HEIGHT) / 2; 
    QPen pen;
    pen.setColor(Qt::black); 
    pen.setWidth(2); 
    painter.setPen(pen);
    QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
    painter.drawRect(drawingArea);
    for (const QVector<QPoint>& line : lines) {
        for (int i = 1; i < line.size(); ++i) {
            painter.drawLine(line[i - 1], line[i]);
        }
    }
    for (int i = 1; i < currentLine.size(); ++i) {
        painter.drawLine(currentLine[i - 1], currentLine[i]);
    }

    QWidget::paintEvent(event);
}
