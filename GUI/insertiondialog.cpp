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
    this->setTabOrder(ui->websiteLineEdit,ui->expirationDateLineEdit);
    this->setTabOrder(ui->expirationDateLineEdit, ui->titleLineEdit);
    this->setTabOrder(ui->titleLineEdit, ui->descriptionLineEdit);
    this->setTabOrder(ui->descriptionLineEdit, ui->inserPushButton);
    this->setTabOrder(ui->inserPushButton,ui->cancelPushButton);
}

ItemInsertionDialog::~ItemInsertionDialog()
{
    delete ui;
}

void ItemInsertionDialog::closeEvent(QCloseEvent *)
{
    clearWindow();
}

void ItemInsertionDialog::onInsertNewPassword()
{
    QString  username       = ui->usernameLineEdit->text();
    QString  password       = ui->passwordLineEdit->text();
    QString  website        = ui->websiteLineEdit->text();
    QString  title          = ui->titleLineEdit->text();
    QString  description    = ui->descriptionLineEdit->text();
    QString  expirationDate = ui->expirationDateLineEdit->text();


    Password newPass(username, password, website, title, expirationDate, description);
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
    clearWindow();
}

void ItemInsertionDialog::clearWindow(){
    ui->resultLabel->clear();
    ui->websiteLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->usernameLineEdit->clear();
    ui->titleLineEdit->clear();
    ui->descriptionLineEdit->clear();
    ui->expirationDateLineEdit->clear();
}


