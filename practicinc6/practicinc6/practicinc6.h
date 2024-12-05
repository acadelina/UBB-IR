#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc6.h"

class practicinc6 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc6(QWidget *parent = nullptr);
    ~practicinc6();

private:
    Ui::practicinc6Class ui;
};
