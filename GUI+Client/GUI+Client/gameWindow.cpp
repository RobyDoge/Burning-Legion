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
        sliderPos.setX(sliderPos.x() + 10 * value); 
        QToolTip::showText(sliderPos, QString::number(value));
        });

    connect(ui.penWidthSlider, &QSlider::valueChanged, this, &GameWindow::updatePenWidth);
    connect(ui.colorPickerButton, &QPushButton::clicked, this, &GameWindow::changePenColor);
    connect(ui.clearButton, &QPushButton::clicked, this, &GameWindow::clearDrawingArea);
   
   
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
                lineWidths[lines.size()] = currentPenWidth; 
                lineColor[lines.size()] = currentPenColor;
                update();
            }
        }
    }
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && isDrawing)
    {
        isDrawing = false;

        lines.append(currentLine); 
        lineWidths[lines.size() - 1] = currentPenWidth;
        lineColor[lines.size() - 1] = currentPenColor;
        currentLine.clear(); 

        update(); 
    }
}

void GameWindow::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int xPos = (width() - WIDTH) / 2;
    int yPos = (height() - HEIGHT) / 2;

    QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
    painter.drawRect(drawingArea);

   if(!lines.empty())
    for (int i = 0; i < lines.size(); ++i) {
        const QVector<QPoint>& line = lines[i];

        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(lineWidths.value(i, 1));
        pen.setColor(lineColor.value(i,1));
        painter.setPen(pen);
        for (int j = 1; j < line.size(); ++j) {
            painter.drawLine(line[j - 1], line[j]);
        }
    }

    if (isDrawing && !currentLine.isEmpty()) {

        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(currentPenWidth); 
        pen.setColor(currentPenColor);
        painter.setPen(pen);
        if(currentLine.size()>1)
            for (int i = 1; i < currentLine.size(); ++i) 
                painter.drawLine(currentLine[i - 1], currentLine[i]);
        
    }

    QWidget::paintEvent(event);
}

void GameWindow::updatePenWidth() {

    currentPenWidth = ui.penWidthSlider->value();
    ui.messageArea->append(QString::number(ui.penWidthSlider->value()));
    update(); 
}

void GameWindow::changePenColor() {
    QColorDialog colorDialog(this);
    QColor chosenColor = colorDialog.getColor(currentPenColor, this, "Choose Pen Color");

    if (chosenColor.isValid()) {
        currentPenColor = chosenColor;
        // Optionally, update UI or perform any actions with the new color
        update(); // Trigger a repaint to apply the new color to subsequent drawings
    }
}
void GameWindow::clearDrawingArea() {
    //lines.clear(); // Clear the stored lines
    lineWidths.clear(); // Clear the stored line widths
    lineColor.clear();
    lines.clear();
    
    update(); // Trigger a repaint to clear the drawing area
}