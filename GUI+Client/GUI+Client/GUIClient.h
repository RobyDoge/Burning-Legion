#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUIClient.h"

class GUIClient : public QMainWindow
{
    Q_OBJECT

public:
    GUIClient(QWidget *parent = nullptr);
    ~GUIClient();

private:
    Ui::GUIClientClass ui;
};
