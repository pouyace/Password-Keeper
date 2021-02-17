#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordhandler.h"
#include "loadingdialog.h"
#include "logindialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupLoginDialog();
    passwordGenerator = new PasswordHandler(this);
//    connect(ui->pushButton,&QPushButton::clicked,this
//            ,[=]{passwordGenerator->GeneratePassword(10,PasswordHandler::AllChars);});
}

MainWindow::~MainWindow()
{
    delete ui;
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

