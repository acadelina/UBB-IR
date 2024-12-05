#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc3.h"

class practicinc3 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc3(QWidget *parent = nullptr);
    ~practicinc3();

private:
    Ui::practicinc3Class ui;
};
