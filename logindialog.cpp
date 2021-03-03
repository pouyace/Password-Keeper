#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    setupConnection();
    ui->errorLabel->setVisible(false);
    ui->hintLabel->setVisible(false);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::setupConnection()
{
    connect(ui->loginPushButton,&QPushButton::clicked,this,&LoginDialog::onLoginButtonClicked);
    connect(ui->closePushButton,&QPushButton::clicked,this,&QDialog::close);
}

void LoginDialog::onLoginButtonClicked()
{
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();
    if((!username.length()) || (!password.length())){
        ui->errorLabel->setText("Empty input");
        return;
    }
    else{
        if(databaseState)
            emit loginRequested(username,password);
        else
            emit databaseIsNotConnected("","");
    }
}

void LoginDialog::setDatabaseState(const bool& state)
{
    databaseState = state;
    ui->database1CheckBox->setChecked(state);
    ui->loginPushButton->setEnabled(state);
    ui->usernameLineEdit->setEnabled(state);
    ui->passwordLineEdit->setEnabled(state);
}

void LoginDialog::setError(const QString &error)
{
    ui->errorLabel->setText(error);
    ui->errorLabel->setVisible(true);
}

void LoginDialog::onDatabaseDialogClosed()
{
    ui->loginPushButton->setEnabled(true);
    ui->usernameLineEdit->setEnabled(true);
    ui->passwordLineEdit->setEnabled(true);
}

void LoginDialog::onSetHint(QString hint)
{
    if(hint.length()){
        ui->hintLabel->setVisible(true);
        ui->hintLabel->setText("Password Hint:' "+hint+" '");
    }
    else
        ui->hintLabel->setVisible(false);
}

