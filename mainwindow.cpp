﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTimer>
#include <QTableWidget>
#include <QDateTime>
#include <QButtonGroup>
#include "logindialog.h"
#include "postgresqlverifier.h"
#include "user.h"
#include "singleitemoptionwidget.h"
#include "customtableview.h"
#include "databasepassewordsetter.h"
#include "passwordhandler.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeObjects();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(loginDialog,&LoginDialog::loginRequested,databaseVerifier,&PostgreSqlVerifier::verifyUser);
    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabaseState,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::errorOccured,loginDialog,&LoginDialog::setError);
    connect(databaseVerifier,&PostgreSqlVerifier::userSignedIn,this,&MainWindow::onSetSignedUser);
    connect(buttonGroup,QOverload<int>::of(&QButtonGroup::buttonClicked),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateDateAndTime);
    connect(ui->exitToolButton,&QToolButton::clicked,this,&QMainWindow::close);
    connect(loginDialog,&LoginDialog::destroyed,this,&MainWindow::close);
    connect(this,&MainWindow::databaseConnected,databasePasswordSetterDialog,&DataBasePassewordSetter::onDatabaseConnected);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::databaseNewConfigSet,this,&MainWindow::updateDatabaseUserAndPass);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::dialodClosed,loginDialog,&LoginDialog::onDatabaseDialogClosed);
    connect(loginDialog,&LoginDialog::databaseIsNotConnected,this,&MainWindow::connectToDatabase);
}

void MainWindow::initializeObjects()
{
    loginDialog = new LoginDialog(this);
    databaseVerifier = new PostgreSqlVerifier(this);
    timer = new QTimer(this);
    tableView = new TableView(this);
    buttonGroup = new QButtonGroup(this);
    databasePasswordSetterDialog = new DataBasePassewordSetter(DEFAULTDATABASEUSERNAME,DEFAULTDATABASEPASSWORD,loginDialog);

    buttonGroup->setExclusive(true);
    buttonGroup->addButton(ui->myPasswordsToolButton,0);
    buttonGroup->addButton(ui->passwordGeneratorToolButton,1);
    buttonGroup->addButton(ui->ExportToolButton,2);
    buttonGroup->addButton(ui->profileToolButton,3);
    ui->stackedWidget->setCurrentIndex(0);
    ui->myPasswordsToolButton->setChecked(true);
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
    timer->start(1000);
    timer->setTimerType(Qt::VeryCoarseTimer);
    ui->verticalLayout_6->addWidget(tableView);
    ui->searchLineEdit->setPlaceholderText("Search Passwords");

}

void MainWindow::connectToDatabase()
{
    isDatabaseConnected = databaseVerifier->setupConfig(QHostAddress::LocalHost,5432,DEFAULTDATABASEUSERNAME,DEFAULTDATABASEPASSWORD,"PasswordKeeper");
    emit databaseConnected(isDatabaseConnected);
}

void MainWindow::raiseLoginPage()
{
    this->hide();
    loginDialog->show();
    connectToDatabase();
}

bool MainWindow::isDataBaseConnected() const
{
    return isDatabaseConnected;
}
void MainWindow::setupMainWindow()
{
    loginDialog->hide();
    this->showFullScreen();
    tableView->loadTable(user->passwords());
    tableView->syncSize();
    ui->passwordsCountLabel->setText(QString::number(user->userPasswordsCount()) + " Passwords");
    ui->usernameLabel->setText(user->prettyName());
    ui->totalPasswordsLabel->setNum(user->userPasswordsCount());
    ui->totalSitesLabel->setNum(user->userSitesCount());
}
void MainWindow::updateDateAndTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
    ui->dateLabel->setText(QDate::currentDate().toString());
}

void MainWindow::onSetSignedUser(User *user)
{
    this->user = user;
    this->setupMainWindow();
}

void MainWindow::updateDatabaseUserAndPass(QString user, QString pass)
{
    isDatabaseConnected = databaseVerifier->setupConfig(QHostAddress::LocalHost,5432,user,pass,"PasswordKeeper");
    emit databaseConnected(isDatabaseConnected);
}
