#include "databasepassewordsetter.h"
#include "ui_databasepassewordsetter.h"

DataBasePassewordSetter::DataBasePassewordSetter(QString defaultUsername, QString defaultPassword, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DataBasePassewordSetter)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setText(defaultUsername);
    ui->passwordLineEdit->setText(defaultPassword);
    connect(ui->applyPushButton,&QPushButton::clicked,this,&DataBasePassewordSetter::onApplyButton);
    connect(ui->bikhialPushButton,&QPushButton::clicked,this,&QDialog::close);
    connect(ui->showPasswordCheckBox,&QCheckBox::stateChanged,this,[=](bool state){
        if(state)
            ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        else
            ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    });
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    this->setWindowFlag(Qt::FramelessWindowHint);

}

DataBasePassewordSetter::~DataBasePassewordSetter()
{
    delete ui;
}

void DataBasePassewordSetter::closeEvent(QCloseEvent *)
{
    emit dialodClosed();
}

void DataBasePassewordSetter::onApplyButton()
{
    emit databaseNewConfigSet(ui->usernameLineEdit->text(),ui->passwordLineEdit->text());
}

void DataBasePassewordSetter::onDatabaseConnected(bool state)
{
    if(state)
        this->close();
    else{
        this->show();
        this->raise();
        ui->errorLabel->setText("couldn't connect to database");
    }
}
