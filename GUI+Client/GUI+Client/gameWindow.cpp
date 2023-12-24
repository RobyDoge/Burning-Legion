#include "GameWindow.h"
#include <chrono>
#include<QToolTip>
#include<QColorDialog>
#include<qtimer.h>

void GameWindow::checkGameStatus()
{
	m_gameEnded = m_client.GetGameStatus();
	newpos = m_client.GetDrawerPosition();
	if (oldpos!=newpos)
	{
		oldpos = newpos;
		emit StartTurn();
	}
}

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

	connect(ui.penWidthSlider, &QSlider::sliderMoved, this, [this](int value)
	{
		QPoint sliderPos = ui.penWidthSlider->mapToGlobal(QPoint(0, -30));
		sliderPos.setX(sliderPos.x() + 10 * value);
		QToolTip::showText(sliderPos, QString::number(value));
	});

	connect(ui.penWidthSlider, &QSlider::valueChanged, this, &GameWindow::updatePenWidth);
	connect(ui.colorPickerButton, &QPushButton::clicked, this, &GameWindow::changePenColor);
	connect(ui.clearButton, &QPushButton::clicked, this, &GameWindow::clearDrawingArea);
	int xPos = (width() - WIDTH) / 2;
	int yPos = (height() - HEIGHT) / 2;

	QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);

	//GetTurnStatus();
	//GetGameStatus();



	// În constructorul GameWindow
	QTimer* gameStatusTimer = new QTimer(this);
	connect(gameStatusTimer, &QTimer::timeout, this, &GameWindow::checkGameStatus);
	gameStatusTimer->start(1000);

	  // Intervalul în milisecunde

}

GameWindow::~GameWindow()
{
}

//need to add function to display a message with the player that is drawing
//function to display a message that the player is close or that he has guessed the word

void GameWindow::sendButton_clicked()
{
	if (!isDrawing)
	{
		QString playerMessage = ui.inputField->text();
		QString message = "Player: " + playerMessage;
		if (!playerMessage.isEmpty())
			ui.messageArea->append(message);
		ui.inputField->clear();
		QString serverMessage = QString(m_client.SendPlayerMessage(playerMessage.toUtf8().constData()).c_str());
		if (serverMessage!=playerMessage)
		ui.messageArea->append("Player: " + playerMessage);
	}
}

void GameWindow::inputField_returnPressed()
{
	sendButton_clicked();
}

void GameWindow::updateCharCount()
{
	int charCount = ui.inputField->text().length();
	ui.charCountLabel->setText(QString::number(charCount));
}

void GameWindow::resizeToScreenSize()
{
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
	if (event->buttons() & Qt::LeftButton && isDrawing)
	{
		int xPos = (width() - WIDTH) / 2;
		int yPos = (height() - HEIGHT) / 2;

		QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
		if (drawingArea.contains(event->pos()))
		{
			QPoint currentPos = event->pos();

			if (!currentLine.empty())
			{
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

void GameWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int xPos = (width() - WIDTH) / 2;
	int yPos = (height() - HEIGHT) / 2;

	QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
	painter.setBrush(Qt::white);
	painter.drawRect(drawingArea);

	if (!lines.empty())
		for (int i = 0; i < lines.size(); ++i)
		{
			const QVector<QPoint>& line = lines[i];

			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(lineWidths.value(i, 1));
			pen.setColor(lineColor.value(i, 1));
			painter.setPen(pen);
			for (int j = 1; j < line.size(); ++j)
			{
				painter.drawLine(line[j - 1], line[j]);
			}
		}

	if (isDrawing && !currentLine.isEmpty())
	{
		QPen pen;
		pen.setColor(Qt::black);
		pen.setWidth(currentPenWidth);
		pen.setColor(currentPenColor);
		painter.setPen(pen);
		if (currentLine.size() > 1)
			for (int i = 1; i < currentLine.size(); ++i)
				painter.drawLine(currentLine[i - 1], currentLine[i]);
	}

	QWidget::paintEvent(event);
}

void GameWindow::updatePenWidth()
{
	currentPenWidth = ui.penWidthSlider->value();
	update();
}

void GameWindow::changePenColor()
{
	QColorDialog colorDialog(this);
	QColor chosenColor = colorDialog.getColor(currentPenColor, this, "Choose Pen Color");

	if (chosenColor.isValid())
	{
		currentPenColor = chosenColor;
		update();
	}
}

void GameWindow::clearDrawingArea()
{
	//lines.clear(); // Clear the stored lines
	lineWidths.clear(); // Clear the stored line widths
	lineColor.clear();
	for (auto& line : lines) line.clear();

	update(); // Trigger a repaint to clear the drawing area
}

void GameWindow::ClearChat()
{
	ui.messageArea->clear();
}

std::string GameWindow::WordToCensor(std::string word)
{
	for (auto letter : word)
		word.replace(word.find(letter), 1, "*");
	m_wordToCensor = word;
	return word;
}

void GameWindow::UpdateWordCensorship(char letter, int position)
{
	m_wordToCensor[position] = letter;
	ui.wordtoGuess->setText(QString(m_wordToCensor.c_str()));
}

void GameWindow::StartTurn()
{
	clearDrawingArea();
	ClearChat();
	ui.timerLabel->setText("60");
	if (m_username == m_client.GetDrawer())
		isDrawing = true;
	else
		isDrawing = false;

	if (isDrawing)
		ui.wordtoGuess->setText(QString(m_client.GetWordToBeGuessed().c_str()));
	else
		ui.wordtoGuess->setText(QString(WordToCensor(m_client.GetWordToBeGuessed()).c_str()));
	//while (true)
	//{
	//	if (m_gameEnded)
	//		ShowEndWindow();
	//	if (m_turnEnded)
	//		ShowPointWindow();
	//}
}

void GameWindow::ShowPointWindow()
{
	return;
}

void GameWindow::ShowEndWindow()
{
	auto* endWindow = new EndGameWindow();
	endWindow->show();
	this->destroy();
}
