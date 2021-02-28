#include "databasepassewordsetter.h"
#include "ui_databasepassewordsetter.h"

DataBasePassewordSetter::DataBasePassewordSetter(QString defaultUsername, QString defaultPassword, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DataBasePassewordSetter)
{
    ui->setupUi(this);
    ui->usernameLineEdit->setText(defaultUsername);
    ui->passwordLineEdit->setText(defaultPassword);
    connect(ui->bikhialPushButton,&QPushButton::clicked,this,&DataBasePassewordSetter::bikhialState);
    connect(ui->showPasswordCheckBox,&QCheckBox::stateChanged,this,[=](bool state){
        if(state)
            ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
        else
            ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    });

}

DataBasePassewordSetter::~DataBasePassewordSetter()
{
    delete ui;
}

void DataBasePassewordSetter::onApplyButton()
{
    emit databaseNewConfigSet(ui->usernameLineEdit->text(),ui->passwordLineEdit->text());
}

void DataBasePassewordSetter::databaseConfirmed(bool state)
{

}
