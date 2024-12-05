#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc7.h"

class practicinc7 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc7(QWidget *parent = nullptr);
    ~practicinc7();

private:
    Ui::practicinc7Class ui;
};
