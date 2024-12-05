#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TractoareSim.h"

class TractoareSim : public QMainWindow
{
    Q_OBJECT

public:
    TractoareSim(QWidget *parent = nullptr);
    ~TractoareSim();

private:
    Ui::TractoareSimClass ui;
};
