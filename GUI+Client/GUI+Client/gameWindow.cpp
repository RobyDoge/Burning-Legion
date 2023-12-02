#include "gameWindow.h"

GameWindow::GameWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAttribute(Qt::WA_StaticContents); 
	
}

GameWindow::~GameWindow()
{}
void GameWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) 
    {
        QRect drawingArea(0, 0, 640, 480);
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
        QRect drawingArea(0, 0, 640, 480);
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
    painter.setRenderHint(QPainter::Antialiasing); // Smoother drawing

    // Set the pen properties for drawing
    QPen pen;
    pen.setColor(Qt::black); // Set the drawing color
    pen.setWidth(2); // Set the drawing line width
    painter.setPen(pen);

    // Draw all saved lines
    for (const QVector<QPoint>& line : lines) {
        for (int i = 1; i < line.size(); ++i) {
            painter.drawLine(line[i - 1], line[i]);
        }
    }

    // Draw the current line being drawn (if any)
    for (int i = 1; i < currentLine.size(); ++i) {
        painter.drawLine(currentLine[i - 1], currentLine[i]);
    }

    QWidget::paintEvent(event);
}
