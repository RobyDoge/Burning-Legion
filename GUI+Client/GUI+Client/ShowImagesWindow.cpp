#include "ShowImagesWindow.h"

ShowImagesWindow::ShowImagesWindow(std::tuple<std::string, std::string, std::string, std::string> images,QWidget *parent)
	: QMainWindow(parent),m_images(images)
{
	ui.setupUi(this);
	connect(ui.MainMenu, &QPushButton::clicked, this, &ShowImagesWindow::MainMenuButton_clicked);
	DisplayImages();
}

ShowImagesWindow::~ShowImagesWindow()
{}

void ShowImagesWindow::MainMenuButton_clicked()
{
	this->destroy();
}

QImage ShowImagesWindow::DeserializeImage(std::string imageString)
{
	QByteArray byteArray = QByteArray::fromBase64(imageString.c_str());
	QImage image;
	image.loadFromData(byteArray, "PNG");
	return image;
}
void ShowImagesWindow::DisplayImages()
{
	ui.label->setPixmap(QPixmap::fromImage(DeserializeImage(std::get<0>(m_images))));
	ui.label_2->setPixmap(QPixmap::fromImage(DeserializeImage(std::get<1>(m_images))));
	ui.label_3->setPixmap(QPixmap::fromImage(DeserializeImage(std::get<2>(m_images))));
	ui.label_4->setPixmap(QPixmap::fromImage(DeserializeImage(std::get<3>(m_images))));
}