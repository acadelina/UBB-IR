#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Melodii2sim.h"

class Melodii2sim : public QMainWindow
{
    Q_OBJECT

public:
    Melodii2sim(QWidget *parent = nullptr);
    ~Melodii2sim();

private:
    Ui::Melodii2simClass ui;
};
