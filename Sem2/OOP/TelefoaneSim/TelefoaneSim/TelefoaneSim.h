#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TelefoaneSim.h"

class TelefoaneSim : public QMainWindow
{
    Q_OBJECT

public:
    TelefoaneSim(QWidget *parent = nullptr);
    ~TelefoaneSim();

private:
    Ui::TelefoaneSimClass ui;
};
