#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc8.h"

class practicinc8 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc8(QWidget *parent = nullptr);
    ~practicinc8();

private:
    Ui::practicinc8Class ui;
};
