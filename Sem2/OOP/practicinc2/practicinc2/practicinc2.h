#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc2.h"

class practicinc2 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc2(QWidget *parent = nullptr);
    ~practicinc2();

private:
    Ui::practicinc2Class ui;
};
