#include "passwordgenerator.h"
#include "ui_passwordgenerator.h"

PasswordGenerator::PasswordGenerator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordGenerator)
{
    ui->setupUi(this);
//    PasswordHandler
}

PasswordGenerator::~PasswordGenerator()
{
    delete ui;
}
