#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_practicinc9.h"

class practicinc9 : public QMainWindow
{
    Q_OBJECT

public:
    practicinc9(QWidget *parent = nullptr);
    ~practicinc9();

private:
    Ui::practicinc9Class ui;
};
