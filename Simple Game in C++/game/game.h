#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_diana.h"

class diana : public QMainWindow
{
    Q_OBJECT

public:
    diana(QWidget *parent = nullptr);
    ~diana();

private:
    Ui::dianaClass ui;
};
