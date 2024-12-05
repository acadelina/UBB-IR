#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc1.h"

class practicinc1 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc1(QWidget *parent = nullptr);
    ~practicinc1();

private:
    Ui::practicinc1Class ui;
};
