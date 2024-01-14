#pragma once

#include <QMainWindow>
#include "ui_ShowImagesWindow.h"

class ShowImagesWindow : public QMainWindow
{
	Q_OBJECT

public:
	ShowImagesWindow(std::tuple<std::string, std::string, std::string, std::string> images,QWidget *parent = nullptr);
	~ShowImagesWindow();
private:
	void DisplayImages();
	QImage DeserializeImage(std::string imageString);
private slots:
	void MainMenuButton_clicked();

private:
	Ui::ShowImagesWindowClass ui;
	std::tuple<std::string, std::string, std::string, std::string> m_images;
};
