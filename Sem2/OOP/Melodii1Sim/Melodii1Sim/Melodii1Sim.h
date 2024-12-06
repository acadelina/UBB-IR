#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Melodii1Sim.h"

class Melodii1Sim : public QMainWindow
{
    Q_OBJECT

public:
    Melodii1Sim(QWidget *parent = nullptr);
    ~Melodii1Sim();

private:
    Ui::Melodii1SimClass ui;
};
