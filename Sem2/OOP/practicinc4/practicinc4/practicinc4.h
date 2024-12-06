#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc4.h"

class practicinc4 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc4(QWidget *parent = nullptr);
    ~practicinc4();

private:
    Ui::practicinc4Class ui;
};
