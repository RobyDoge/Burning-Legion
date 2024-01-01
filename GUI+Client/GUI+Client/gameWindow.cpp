#include "GameWindow.h"
#include <chrono>
#include<QToolTip>
#include<QColorDialog>
#include<qtimer.h>


GameWindow::GameWindow(const std::string& username, QWidget* parent) :
	QMainWindow(parent),
	m_username(username)
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAttribute(Qt::WA_StaticContents);
	ResizeToScreenSize();

	connect(ui.sendButton, &QPushButton::clicked, this, &GameWindow::SendButton_Clicked);
	connect(ui.inputField, &QLineEdit::returnPressed, this, &GameWindow::InputField_ReturnPressed);
	connect(ui.inputField, &QLineEdit::textChanged, this, &GameWindow::UpdateCharCount);
	connect(ui.penWidthSlider, &QSlider::sliderMoved, this, [this](const int value)
	{
		QPoint sliderPos = ui.penWidthSlider->mapToGlobal(QPoint(0, -30));
		sliderPos.setX(sliderPos.x() + 10 * value);
		QToolTip::showText(sliderPos, QString::number(value));
	});
	connect(ui.penWidthSlider, &QSlider::valueChanged, this, &GameWindow::UpdatePenWidth);
	connect(ui.colorPickerButton, &QPushButton::clicked, this, &GameWindow::ChangePenColor);
	connect(ui.clearButton, &QPushButton::clicked, this, &GameWindow::ClearDrawingArea);


	//QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
	ui.drawingArea->setGeometry(m_xPos, m_yPos, WIDTH, HEIGHT);

	//Return_TurnStatus();
	//Return_GameStatus();

	// În constructorul GameWindow
	QTimer* gameStatusTimer = new QTimer(this);
	connect(gameStatusTimer, &QTimer::timeout, this, &GameWindow::CheckGameStatus);
	gameStatusTimer->start(1000);

	// Intervalul în milisecunde

}

GameWindow::~GameWindow() = default;


void GameWindow::CheckGameStatus()
{
	currentTime--;
	ui.timerLabel->setText(QString::number(currentTime));
	m_gameEnded = m_client.Return_GameStatus();
	m_currentDrawerPosition = m_client.Return_DrawerPosition();
	if (m_gameEnded)
	{
		ShowEndWindow();
		this->destroy();
	}
	else if (m_previousDrawerPosition!=m_currentDrawerPosition)
		{
			m_previousDrawerPosition = m_currentDrawerPosition;
			emit StartTurn();
		}
}

//need to add function to display a message with the player that is drawing
//function to display a message that the player is close or that he has guessed the word

void GameWindow::SendButton_Clicked()
{
	if (!m_isDrawer)
	{
		const QString playerMessage = ui.inputField->text();

		if (!playerMessage.isEmpty())
		{
			ui.messageArea->append("Player: " + playerMessage);
		}
		ui.inputField->clear();

		if (const auto serverMessage = QString(m_client.Return_PlayerGuessResponse(playerMessage.toUtf8().constData()).c_str()); 
			serverMessage != playerMessage)
		{
			ui.messageArea->append("Player: " + playerMessage);
		}
	}
}

void GameWindow::InputField_ReturnPressed()
{
	SendButton_Clicked();
}

void GameWindow::UpdateCharCount() const
{
	const int charCount = ui.inputField->text().length();
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
			const QPoint currentPos = event->pos();
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
	if (!m_receivedDrawing.isNull())
	{
		painter.drawPixmap(m_xPos, m_yPos, m_receivedDrawing);
		QWidget::paintEvent(event);
		return;
	}

	const QRect border(m_xPos, m_yPos, WIDTH, HEIGHT);
	painter.setBrush(Qt::white);
	painter.drawRect(border);

	if (!m_lines.empty())
		for (int lineIndex = 0; lineIndex < m_lines.size(); ++lineIndex)
		{
			const QVector<QPoint>& line = m_lines[lineIndex];
			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(m_lineWidths.value(lineIndex, 1));
			pen.setColor(m_lineColor.value(lineIndex, 1));
			painter.setPen(pen);
			for (int linePixelIndex = 1; linePixelIndex < line.size(); ++linePixelIndex)
			{
				painter.drawLine(line[linePixelIndex - 1], line[linePixelIndex]);
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
			for (int linePixelIndex = 1; linePixelIndex < m_currentLine.size(); ++linePixelIndex)
				painter.drawLine(m_currentLine[linePixelIndex - 1], m_currentLine[linePixelIndex]);
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
	if (const QColor chosenColor = QColorDialog::getColor(m_currentPenColor, this, "Choose Pen Color"); 
		chosenColor.isValid())
	{
		m_currentPenColor = chosenColor;
		update();
	}
}

void GameWindow::ClearDrawingArea()
{
	m_lineWidths.clear(); 
	m_lineColor.clear();
	std::ranges::for_each(m_lines, [](QVector<QPoint>& line) { line.clear(); });
	update();
}

void GameWindow::ClearChat() const
{
	ui.messageArea->clear();
}

std::string GameWindow::WordToCensor(std::string word)
{
	std::ranges::for_each(word, [](char& letter) { letter = '*'; });
	m_wordToCensor = word;
	return word;
}

void GameWindow::UpdateWordCensorship(const char letter, const int position)
{
	m_wordToCensor[position] = letter;
	ui.wordtoGuess->setText(QString(m_wordToCensor.c_str()));
}

void GameWindow::StartTurn()
{
	ClearDrawingArea();
	ClearChat();
	currentTime = 60;
	ui.timerLabel->setText("60");
	if (m_username == m_client.Return_DrawerName())
	{
		m_isDrawer = true;
		ui.wordtoGuess->setText(QString(m_client.Return_WordToBeGuessed().c_str()));
	}
	else
	{
		m_isDrawer = false;
		ui.wordtoGuess->setText(QString(WordToCensor(m_client.Return_WordToBeGuessed()).c_str()));
	}
	//while (true)
	//{
	//	if (m_gameStatus)
	//		ShowEndWindow();
	//	if (m_turnEnded)
	//		ShowPointWindow();
	//}
}

//TODO: implement this function
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

QByteArray GameWindow::SerializeDrawing()
{
	const QPixmap pixelMap = ui.drawingArea->grab();
	const QImage image = pixelMap.toImage();

	QByteArray byteArray;
	QBuffer buffer(&byteArray);
	buffer.open(QIODevice::WriteOnly);
	image.save(&buffer, "PNG");

	return byteArray;
}

void GameWindow::SetReceivedDrawing(const QPixmap& pixelMap)
{
	m_receivedDrawing = pixelMap;
	ui.drawingArea->update();
}