#include "insertiondialog.h"
#include "ui_insertiondialog.h"

ItemInsertionDialog::ItemInsertionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemInsertionDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    connect(ui->cancelPushButton,&QPushButton::clicked,this,&QDialog::close);
    connect(ui->inserPushButton,&QPushButton::clicked,this,&ItemInsertionDialog::onInsertNewPassword);
    this->setTabOrder(ui->cancelPushButton,ui->usernameLineEdit);
    this->setTabOrder(ui->usernameLineEdit,ui->passwordLineEdit);
    this->setTabOrder(ui->passwordLineEdit,ui->websiteLineEdit);
    this->setTabOrder(ui->websiteLineEdit,ui->inserPushButton);
    this->setTabOrder(ui->inserPushButton,ui->cancelPushButton);
}

ItemInsertionDialog::~ItemInsertionDialog()
{
    delete ui;
}

void ItemInsertionDialog::closeEvent(QCloseEvent *)
{
    ui->resultLabel->clear();
    ui->websiteLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->usernameLineEdit->clear();
}

void ItemInsertionDialog::onInsertNewPassword()
{
    Password *newPass = new Password(ui->usernameLineEdit->text(), ui->passwordLineEdit->text(),ui->websiteLineEdit->text());
    emit newInsertionRequested(newPass);
}

void ItemInsertionDialog::onInsertionResult(bool state)
{
    if(!state){
        ui->resultLabel->setText("Insertion was unsuccessful. An error occured");
        ui->resultLabel->setStyleSheet("color:red");
        ui->inserPushButton->setText("Try again");
        return;
    }
    ui->cancelPushButton->setText("close");
    ui->resultLabel->setText("Item has been Added");
    ui->resultLabel->setStyleSheet("color:green");
    ui->websiteLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->usernameLineEdit->clear();
}
