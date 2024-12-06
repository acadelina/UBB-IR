#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc5.h"

class practicinc5 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc5(QWidget *parent = nullptr);
    ~practicinc5();

private:
    Ui::practicinc5Class ui;
};
