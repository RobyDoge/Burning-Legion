#include "GameWindow.h"
#include "ShowPointsWindow.h"
#include "Client.h"
#include <chrono>
#include <QToolTip>
#include <QColorDialog>
#include <qtimer.h>
#include <QThread>
#include <algorithm>
#include <random>

GameWindow::GameWindow(const std::string& username, QWidget* parent) :
	QMainWindow(parent),
	m_username(username), m_receivedImage(400, 400, QImage::Format_RGB32),m_capturedImage(400, 400, QImage::Format_RGB32)
{
	ui.setupUi(this);
	setMouseTracking(true);
	setAttribute(Qt::WA_StaticContents);
	ResizeToScreenSize();
	DisplayPlayers();
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
	connect(ui.saveDrawing, &QPushButton::clicked, this, &GameWindow::SaveDrawing);
	m_xPos = (width() - WIDTH) / 2;
	m_yPos = (height() - HEIGHT) / 2;
	//QRect drawingArea(xPos, yPos, WIDTH, HEIGHT);
	ui.drawingArea->setGeometry(m_xPos, m_yPos, WIDTH, HEIGHT);


	m_stopThread.store(true);

	
	CheckGameStatus();
	UpdatePlayerMessages();
	StartDrawingThread();
}

void GameWindow::DisplayPlayers() const
{
	ui.gamePlayersList->clear();
	for (const auto& player : Client::Return_PlayersNames())
	{
		ui.gamePlayersList->addItem(QString(player.c_str()));
	}
}


void GameWindow::StartDrawingThread()
{
	std::thread drawThread([this]()
		{
			while (m_stopThread)
			{
					if (m_isDrawer)
					{

						QImage image = m_capturedImage;
						QByteArray byteArray;
						QBuffer buffer(&byteArray);
						buffer.open(QIODevice::WriteOnly);
						image.save(&buffer, "PNG");
						QString imageString = byteArray.toBase64();
						m_imgString = imageString.toUtf8().constData();
						Client::Send_Drawing(m_imgString);

					}
					else {

						std::string imageString = Client::Return_Drawing();
						QByteArray byteArray = QByteArray::fromBase64(imageString.c_str());
				
						m_receivedImage.loadFromData(byteArray, "PNG");
						
						update();
					}
					std::this_thread::sleep_for(std::chrono::milliseconds(100));
				
			}
		});
	drawThread.detach();
}

void GameWindow::CheckGameStatus()
{
	std::thread updateThread([this]()
		{
			while (m_stopThread)
			{
				m_currentTime = Client::Return_CurrentTime();
				ui.timerLabel->setText(QString::number(60-m_currentTime));
				m_gameEnded = Client::Return_GameStatus();
				m_currentDrawerPosition = Client::Return_DrawerPosition();

				if(!m_isDrawer)
				if ((m_currentTime == 30 || m_currentTime == 45))
					RevealRandomLetters();

					if (m_gameEnded)
					{
						m_stopThread.store(false);
						ShowEndWindow();
					}

				 if (m_previousDrawerPosition != m_currentDrawerPosition)
				{
					if (m_previousDrawerPosition != 255)
					{
						m_previousDrawerPosition = m_currentDrawerPosition;
						emit ShowPointWindow();
						QTimer::singleShot(5000, this, &GameWindow::StartTurn);
					}
					else
					{
						m_previousDrawerPosition = m_currentDrawerPosition;
						emit StartTurn();
					}
				}
			}
			});

	updateThread.detach();

}

//need to add function to display a message with the player that is drawing

void GameWindow::UpdatePlayerMessages()
{
	std::thread messageThread([this]()
		{
			while (m_stopThread)
			{
				m_currentPlayerGuess = QString(Client::Return_OtherPlayerGuess().c_str());
				if (m_currentPlayerGuess != m_lastPlayerGuess)
				{
					m_lastPlayerGuess = m_currentPlayerGuess;
					QMetaObject::invokeMethod(this, [this]() 
					{
					
						if (!m_currentPlayerGuess.isEmpty() && m_currentPlayerGuess != QString(Client::Return_WordToBeGuessed().c_str()))
						{
							ui.messageArea->append("Player: " + m_currentPlayerGuess);
						}
						ui.inputField->clear();

						if (const auto serverMessage = QString(Client::Return_PlayerGuessResponse(m_currentPlayerGuess.toUtf8().constData(),m_username).c_str());
							serverMessage != m_currentPlayerGuess)
						{
							ui.messageArea->append("Player: " + serverMessage);
						}

					}, Qt::QueuedConnection);

				}
			}
		});
	messageThread.detach();
}
void GameWindow::SendButton_Clicked()
{
	if (!m_isDrawer)
	{
	    m_playerMessage = ui.inputField->text();
		Client::Send_PlayerGuess(m_playerMessage.toUtf8().constData());
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
	 resize(1536, 864);
	setFixedSize(1536,864); 
}

void GameWindow::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		if(ui.drawingArea->geometry().contains(event->pos()) && m_isDrawer)
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

	int captureOffsetX = m_xPos;
	int captureOffsetY = m_yPos;

	m_capturedImage = QImage(WIDTH, HEIGHT, QImage::Format_RGB32);
	QPainter capturePainter(&m_capturedImage);
	capturePainter.translate(-m_xPos, -m_yPos);
	capturePainter.setRenderHint(QPainter::Antialiasing);

	const QRect border(0, 0, WIDTH, HEIGHT);
	painter.setBrush(Qt::white);
	capturePainter.setBrush(Qt::white);
	painter.drawRect(border.translated(captureOffsetX, captureOffsetY));
	capturePainter.drawRect(border.translated(captureOffsetX, captureOffsetY));

	if (!m_receivedImage.isNull())
	{


		painter.drawImage(m_xPos, m_yPos, m_receivedImage);
		capturePainter.drawImage(m_xPos, m_yPos, m_receivedImage);
	}

	if (!m_lines.empty())
		for (int lineIndex = 0; lineIndex < m_lines.size(); ++lineIndex)
		{
			const QVector<QPoint>& line = m_lines[lineIndex];
			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(m_lineWidths.value(lineIndex, 1));
			pen.setColor(m_lineColor.value(lineIndex, 1));
			painter.setPen(pen);
			capturePainter.setPen(pen);
			for (int linePixelIndex = 1; linePixelIndex < line.size(); ++linePixelIndex)
			{
				painter.drawLine(line[linePixelIndex - 1], line[linePixelIndex]);
				capturePainter.drawLine(line[linePixelIndex - 1], line[linePixelIndex]);
			}
		}

	if (m_isDrawing && !m_currentLine.isEmpty())
	{
		QPen pen;
		pen.setColor(Qt::black);
		pen.setWidth(m_currentPenWidth);
		pen.setColor(m_currentPenColor);
		painter.setPen(pen);
		capturePainter.setPen(pen);
		if (m_currentLine.size() > 1)
			for (int linePixelIndex = 1; linePixelIndex < m_currentLine.size(); ++linePixelIndex)
			{
				painter.drawLine(m_currentLine[linePixelIndex - 1], m_currentLine[linePixelIndex]);
				capturePainter.drawLine(m_currentLine[linePixelIndex - 1], m_currentLine[linePixelIndex]);
			}
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

void GameWindow::CensoredWord()
{
	m_censoredWord.clear();
	for (int i = 0; i < m_guessWord.length(); i++)
	{
		m_censoredWord += "*";
	}
	
}

void GameWindow::UpdateWordCensorship(const char letter, const int position)
{
	m_censoredWord[position] = letter;
	ui.wordtoGuess->setText(QString(m_censoredWord.c_str()));
}
void GameWindow::RevealRandomLetters()
{
	const int lettersToReveal = m_censoredWord.length() / 4;

	std::vector<int> indices;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(0, m_censoredWord.length() - 1);

	while (indices.size() < lettersToReveal) 
	{
		if (int randIndex = distribution(gen); 
			std::ranges::find(indices, randIndex) == indices.end()) 
		{
			indices.push_back(randIndex);
		}
	}

	for (const int index : indices)
	{
		UpdateWordCensorship(m_guessWord[index], index);
		ui.wordtoGuess->setText(QString(m_censoredWord.c_str()));
	}

}
void GameWindow::StartTurn()
{
	QMetaObject::invokeMethod(this, [this]()
	{
		ClearDrawingArea();
		ClearChat();
		m_capturedImage.fill(Qt::white);
		update();
		m_currentTime = 60;
		ui.timerLabel->setText("60");
		const auto qDrawerName = QString(Client::Return_DrawerName().c_str());
		ui.messageArea->append(qDrawerName + " is drawing...");
		m_guessWord = Client::Return_WordToBeGuessed();
		CensoredWord();
		if (m_username == Client::Return_DrawerName())
		{
			m_isDrawer = true;
			ui.wordtoGuess->setText(QString(m_guessWord.c_str()));
		}
		else
		{
			m_isDrawer = false;
			ui.wordtoGuess->setText(QString(m_censoredWord.c_str()));
		}
	}, Qt::QueuedConnection);
}

void GameWindow::ShowPointWindow()
{
	QMetaObject::invokeMethod(this, [this]() {
		auto pointWindow = new ShowPointsWindow();
		pointWindow->show();
		m_capturedImage.fill(Qt::white);
		update();
		// Crearea unui QTimer pentru a închide fereastra după 5 secunde
		auto timer = new QTimer(this);
		connect(timer, &QTimer::timeout, [pointWindow, timer]() {
			// Închideți fereastra și opriți timerul când expiră intervalul
			pointWindow->close();
			pointWindow->deleteLater();
			timer->stop();
			timer->deleteLater();  // Eliberare resurse
			});

		// Setarea intervalului la 5000 de milisecunde (5 secunde)
		timer->start(5000);

		}, Qt::QueuedConnection);
}


void GameWindow::ShowEndWindow()
{
	QMetaObject::invokeMethod(this, [this]() {

	auto* endWindow = new EndGameWindow(std::move(m_username));
	endWindow->show();
	this->destroy();
		

		}, Qt::QueuedConnection);
}

void GameWindow::SaveDrawing()
{
	QMetaObject::invokeMethod(this, [this]()
		{
			QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
			"/path/to/default/filename.png",
			tr("Images (*.png *.jpg)"));
	if (!fileName.isEmpty())
	{
		m_capturedImage.save(fileName);
	}
		}, Qt::QueuedConnection);
}

void GameWindow::SetReceivedDrawing(const QPixmap& pixelMap)
{
	m_receivedDrawing = pixelMap;
	ui.drawingArea->update();
}