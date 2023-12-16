#include "gameWindow.h"
#include<QToolTip>
#include<QColorDialog>
GameWindow::GameWindow(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setMouseTracking(true);
    setAttribute(Qt::WA_StaticContents);
    isDrawing = false;
    resizeToScreenSize();


    connect(ui.sendButton, &QPushButton::clicked, this, &GameWindow::sendButton_clicked);
    connect(ui.inputField, &QLineEdit::returnPressed, this, &GameWindow::inputField_returnPressed);
    connect(ui.inputField, &QLineEdit::textChanged, this, &GameWindow::updateCharCount);

    connect(ui.penWidthSlider, &QSlider::sliderMoved, this, [this](int value) {
        QPoint sliderPos = ui.penWidthSlider->mapToGlobal(QPoint(0, -30));
        sliderPos.setX(sliderPos.x() + 10 * value); // Adjust X position based on slider value, multiplied by 2 for faster movement
        QToolTip::showText(sliderPos, QString::number(value));
        });

    connect(ui.penWidthSlider, &QSlider::valueChanged, this, &GameWindow::updatePenWidth);
   
   
}

GameWindow::~GameWindow()
{}

//need to add function to display a message with the player that is drawing
//function to display a message that the player is close or that he has guessed the word

void GameWindow::sendButton_clicked() {

    QString playerMessage = ui.inputField->text();
    QString message = "Player: " + playerMessage;
    if (!playerMessage.isEmpty())
        ui.messageArea->append(message);
    ui.inputField->clear();
}

void GameWindow::inputField_returnPressed() {
    sendButton_clicked();
}

void GameWindow::updateCharCount() {
    int charCount = ui.inputField->text().length();
    ui.charCountLabel->setText(QString::number(charCount));
}
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

            if (!currentLine.empty()) {
                QPoint lastPoint = currentLine.back();
                currentLine.append(currentPos);
                lineWidths[lines.size()] = currentPenWidth; // Store the width for the current line using the line index
                update();
            }
        }
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDrawing) {
        isDrawing = false;

        lines.append(currentLine); // Save the current line to the list of lines
        lineWidths[lines.size() - 1] = currentPenWidth; // Set the width for the current line using its index

        currentLine.clear(); // Clear the current line's points after finishing

        update(); // Trigger repaint to include the updated line in the drawing
    }
}

void GameWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int xPos = (width() - WIDTH) / 2;
    int yPos = (height() - HEIGHT) / 2;

    QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
    painter.drawRect(drawingArea);

    // Draw existing lines with their respective widths
    for (int i = 0; i < lines.size(); ++i) {
        const QVector<QPoint>& line = lines[i];

        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(lineWidths.value(i, 1)); // Use the stored width for this line index, default to 1 if not found
        painter.setPen(pen);

        for (int j = 1; j < line.size(); ++j) {
            painter.drawLine(line[j - 1], line[j]);
        }
    }

    // Draw the current line being drawn with the updated width
    if (isDrawing && !currentLine.isEmpty()) {
        // Draw the current line with the updated pen width
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(currentPenWidth); // Use the current pen width for the current line
        painter.setPen(pen);

        for (int i = 1; i < currentLine.size(); ++i) {
            painter.drawLine(currentLine[i - 1], currentLine[i]);
        }
    }

    QWidget::paintEvent(event);
}

void GameWindow::updatePenWidth() {
    // Update the pen width when the slider value changes
    currentPenWidth = ui.penWidthSlider->value();
    ui.messageArea->append(QString::number(ui.penWidthSlider->value()));
    update(); // Trigger a repaint to apply the new pen width to subsequent drawings
}
