#include "iteminsertiondialog.h"
#include "ui_iteminsertiondialog.h"

ItemInsertionDialog::ItemInsertionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemInsertionDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->cancelPushButton,&QPushButton::clicked,this,&QDialog::close);
    connect(ui->inserPushButton,&QPushButton::clicked,this,&ItemInsertionDialog::onInsertNewPassword);
}

ItemInsertionDialog::~ItemInsertionDialog()
{
    delete ui;
}

void ItemInsertionDialog::onInsertNewPassword()
{
    emit newInsertionRequested(ui->usernameLineEdit->text(),ui->passwordLineEdit->text(),ui->websiteLineEdit->text());
}

void ItemInsertionDialog::onInsertionResult(bool state)
{
    if(!state){
        ui->resultLabel->setText("Insertion was unsuccessful. An error occured");
        ui->resultLabel->setStyleSheet("color:red");
        ui->inserPushButton->setText("Try again");
        return;
    }
    ui->inserPushButton->setVisible(false);
    ui->cancelPushButton->setText("close");
    ui->resultLabel->setText("Item has been Added");
    ui->resultLabel->setStyleSheet("color:green");
}
