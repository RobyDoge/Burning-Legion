#include "GameWindow.h"
#include <chrono>
#include<QToolTip>
#include<QColorDialog>
#include<qtimer.h>

void GameWindow::CheckGameStatus()
{
	m_gameEnded = m_client.GetGameStatus();
	m_newPosition = m_client.GetDrawerPosition();
	if (m_oldPosition!=m_newPosition)
	{
		m_oldPosition = m_newPosition;
		emit StartTurn();
	}
}

GameWindow::GameWindow(const std::string& username,QWidget* parent):
	QMainWindow(parent),
	m_username(username)
{

	ui.setupUi(this);
	setMouseTracking(true);
	setAttribute(Qt::WA_StaticContents);
	m_isDrawing = false;
	ResizeToScreenSize();
	connect(ui.sendButton, &QPushButton::clicked, this, &GameWindow::SendButton_Clicked);
	connect(ui.inputField, &QLineEdit::returnPressed, this, &GameWindow::InputField_ReturnPressed);
	connect(ui.inputField, &QLineEdit::textChanged, this, &GameWindow::UpdateCharCount);

	connect(ui.penWidthSlider, &QSlider::sliderMoved, this, [this](int value)
	{
		QPoint sliderPos = ui.penWidthSlider->mapToGlobal(QPoint(0, -30));
		sliderPos.setX(sliderPos.x() + 10 * value);
		QToolTip::showText(sliderPos, QString::number(value));
	});

	connect(ui.penWidthSlider, &QSlider::valueChanged, this, &GameWindow::UpdatePenWidth);
	connect(ui.colorPickerButton, &QPushButton::clicked, this, &GameWindow::ChangePenColor);
	connect(ui.clearButton, &QPushButton::clicked, this, &GameWindow::ClearDrawingArea);
	int xPos = (width() - WIDTH) / 2;
	int yPos = (height() - HEIGHT) / 2;

	//QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
	ui.drawingArea->setGeometry(xPos, yPos, WIDTH, HEIGHT);

	//GetTurnStatus();
	//GetGameStatus();



	// În constructorul GameWindow
	QTimer* gameStatusTimer = new QTimer(this);
	connect(gameStatusTimer, &QTimer::timeout, this, &GameWindow::CheckGameStatus);
	gameStatusTimer->start(1000);

	  // Intervalul în milisecunde

}

GameWindow::~GameWindow()
{
}

//need to add function to display a message with the player that is drawing
//function to display a message that the player is close or that he has guessed the word

void GameWindow::SendButton_Clicked()
{
	if (!m_isDrawing)
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

void GameWindow::InputField_ReturnPressed()
{
	SendButton_Clicked();
}

void GameWindow::UpdateCharCount()
{
	int charCount = ui.inputField->text().length();
	ui.charCountLabel->setText(QString::number(charCount));
}

void GameWindow::ResizeToScreenSize()
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

		if(ui.drawingArea->geometry().contains(event->pos()))
		{
			m_currentLine.clear();
			m_currentLine.append(event->pos());
			m_isDrawing = true;
		}
	}
}

void GameWindow::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton && m_isDrawing)
	{
		
		if(ui.drawingArea->geometry().contains(event->pos()))
		{
			QPoint currentPos = event->pos();

			if (!m_currentLine.empty())
			{
				QPoint lastPoint = m_currentLine.back();
				m_currentLine.append(currentPos);
				m_lineWidths[m_lines.size()] = m_currentPenWidth;
				m_lineColor[m_lines.size()] = m_currentPenColor;
				update();
			}
		}
	}
}

void GameWindow::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton && m_isDrawing)
	{
		m_isDrawing = false;

		m_lines.append(m_currentLine);
		m_lineWidths[m_lines.size() - 1] = m_currentPenWidth;
		m_lineColor[m_lines.size() - 1] = m_currentPenColor;
		m_currentLine.clear();

		update();
	}
}

void GameWindow::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);

	int xPos = (width() - WIDTH) / 2;
	int yPos = (height() - HEIGHT) / 2;

	QRect border(xPos, yPos, WIDTH, HEIGHT);
	painter.setBrush(Qt::white);
	painter.drawRect(border);

	if (!m_lines.empty())
		for (int i = 0; i < m_lines.size(); ++i)
		{
			const QVector<QPoint>& line = m_lines[i];

			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(m_lineWidths.value(i, 1));
			pen.setColor(m_lineColor.value(i, 1));
			painter.setPen(pen);
			for (int j = 1; j < line.size(); ++j)
			{
				painter.drawLine(line[j - 1], line[j]);
			}
		}

	if (m_isDrawing && !m_currentLine.isEmpty())
	{
		QPen pen;
		pen.setColor(Qt::black);
		pen.setWidth(m_currentPenWidth);
		pen.setColor(m_currentPenColor);
		painter.setPen(pen);
		if (m_currentLine.size() > 1)
			for (int i = 1; i < m_currentLine.size(); ++i)
				painter.drawLine(m_currentLine[i - 1], m_currentLine[i]);
	}

	QWidget::paintEvent(event);
}

void GameWindow::UpdatePenWidth()
{
	m_currentPenWidth = ui.penWidthSlider->value();
	update();
}

void GameWindow::ChangePenColor()
{
	QColor chosenColor = QColorDialog::getColor(m_currentPenColor, this, "Choose Pen Color");

	if (chosenColor.isValid())
	{
		m_currentPenColor = chosenColor;
		update();
	}
}

void GameWindow::ClearDrawingArea()
{
	//lines.clear(); // Clear the stored lines
	m_lineWidths.clear(); // Clear the stored line widths
	m_lineColor.clear();
	for (auto& line : m_lines) line.clear();

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
	ClearDrawingArea();
	ClearChat();
	ui.timerLabel->setText("60");
	if (m_username == m_client.GetDrawer())
		m_isDrawing = true;
	else
		m_isDrawing = false;

	if (m_isDrawing)
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
