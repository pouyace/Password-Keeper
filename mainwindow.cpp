#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordhandler.h"
#include "loadingdialog.h"
#include "logindialog.h"
#include "postgresqlverifier.h"
#include <QHostAddress>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupLoginDialog();
    setupSqlVerifier();
    setupConnections();
    databaseVerifier->setupConfig(QHostAddress::LocalHost,5432,"postgres","newpouya","PasswordKeeper");

//    connect(ui->pushButton,&QPushButton::clicked,this
//            ,[=]{passwordGenerator->GeneratePassword(10,PasswordHandler::AllChars);});
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(loginDialog,&LoginDialog::closeAppRequested,this,&QMainWindow::close);
    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabase1State,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabase2State,Qt::UniqueConnection);
}

void MainWindow::setupLoadingDialog()
{
    loadingDialog = new LoadingDialog(this);
    loadingDialog->show();

}

void MainWindow::setupLoginDialog()
{
    loginDialog = new LoginDialog(this);
    loginDialog->show();
}

void MainWindow::setupSqlVerifier()
{
    databaseVerifier = new PostgreSqlVerifier();
}

void MainWindow::setupPasswordGenerator()
{
    passwordGenerator = new PasswordHandler(this);
}

