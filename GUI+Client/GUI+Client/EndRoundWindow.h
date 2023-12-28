#pragma once

#include <QMainWindow>
#include "ui_endRoundWindow.h"

class EndRoundWindow : public QMainWindow
{
	Q_OBJECT

public:
	EndRoundWindow(QWidget *parent = nullptr);
	~EndRoundWindow();

private:
	Ui::EndRoundWindowClass ui;
};
