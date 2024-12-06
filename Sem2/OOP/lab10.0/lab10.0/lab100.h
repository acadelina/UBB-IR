#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_lab100.h"

class lab100 : public QMainWindow
{
    Q_OBJECT

public:
    lab100(QWidget *parent = nullptr);
    ~lab100();

private:
    Ui::lab100Class ui;
};
