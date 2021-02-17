#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setupConnection();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupConnection()
{
    connect(ui->loginPushButton,&QPushButton::clicked,this,&LoginDialog::loginPressed);
    connect(ui->closePushButton,&QPushButton::clicked,this,&LoginDialog::closeAppRequested);
}

void LoginDialog::loginPressed()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if((!username.length()) || (!password.length())){
        ui->errorLabel->setText("Empty input");
        return;
    }
    else
        emit loginRequested(username,password);
}

void LoginDialog::setDatabase1State(bool state)
{
    if(state)
        ui->database1CheckBox->setChecked(true);
    else
        ui->database1CheckBox->setChecked(false);
}

void LoginDialog::setDatabase2State(bool state)
{
    if(state)
        ui->database2CheckBox->setChecked(true);
    else
        ui->database2CheckBox->setChecked(false);
}
