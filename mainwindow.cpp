﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTimer>
#include <QDateTime>
#include <QButtonGroup>
#include "GUI/logindialog.h"
#include "Verifier/databaseverifier.h"
#include "Single/user.h"
#include "GUI/insertiondialog.h"
#include "table/tableview.h"
#include "Handlers/usercontroller.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeObjects();
    initializeModules();
    setupConnections();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(loginDialog,&LoginDialog::loginRequested,databaseVerifier,&DatabaseVerifier::onUserLoginRequested);
    connect(loginDialog,&LoginDialog::destroyed,this,&MainWindow::close);

    connect(databaseVerifier,&DatabaseVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabaseState,Qt::UniqueConnection);
    connect(databaseVerifier,&DatabaseVerifier::errorOccured,loginDialog,&LoginDialog::setError);
    connect(databaseVerifier,&DatabaseVerifier::hintDisplayRequested,loginDialog,&LoginDialog::onSetHint);
    connect(databaseVerifier,&DatabaseVerifier::userSignedIn,this,&MainWindow::setupMainWindow);
    connect(databaseVerifier,&DatabaseVerifier::syncItemsRetreived,userController,&UserController::onItemsRetreived);
    connect(databaseVerifier,&DatabaseVerifier::itemRemoved, ui->tableTab->tableView(), &TableView::onItemDeleted);
    connect(databaseVerifier,&DatabaseVerifier::onDialogClosed,loginDialog,&LoginDialog::onDatabaseDialogClosed);
    connect(databaseVerifier,&DatabaseVerifier::newItemInserted,ui->tableTab->insertionDialog(),&ItemInsertionDialog::onInsertionResult);

    connect(ui->tableTab->insertionDialog(),&ItemInsertionDialog::newInsertionRequested,databaseVerifier,&DatabaseVerifier::onAddNewItem);

    connect(buttonGroup,QOverload<int>::of(&QButtonGroup::buttonClicked),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateDateAndTime);
    connect(ui->exitToolButton  ,&QToolButton::clicked,this,&QMainWindow::close);

    connect(userController,&UserController::syncedItemsGot,ui->tableTab->tableView(), &TableView::showSyncItems);
    connect(userController,&UserController::passwordsCountUpdated,this,[=](int c){ui->passwordsCountLabel->setText(QString::number(c) + " Passwords");});
    connect(userController,&UserController::passwordsCountUpdated,ui->tableTab,&TableTab::updateTotPass);
    connect(userController,&UserController::uniqueSitesCountUpdated,ui->tableTab,&TableTab::upadteTotSite);

    connect(ui->tableTab->tableView(),  &TableView::deleteItem,     databaseVerifier, &DatabaseVerifier::onRemoveItem);
    connect(ui->tableTab,               &TableTab::onSyncClicked,   databaseVerifier, &DatabaseVerifier::sync);

    connect(this, &MainWindow::mainwindowResized, ui->tableTab->tableView(), &TableView::syncSize);

}

void MainWindow::initializeObjects()
{
    timer                        = new QTimer               (this);   // Timer
    buttonGroup                  = new QButtonGroup         (this);   // ButtonGroup
}

void MainWindow::initializeModules()
{
    loginDialog                  = new LoginDialog          (this);   // Login
    databaseVerifier             = new DatabaseVerifier     (this);   // Database
    userController               = new UserController       (this);   // User Controller
}

void MainWindow::setupProperties()
{
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(ui->myPasswordsToolButton,0);
    buttonGroup->addButton(ui->passwordGeneratorToolButton,1);
    buttonGroup->addButton(ui->ExportToolButton,2);
    buttonGroup->addButton(ui->profileToolButton,3);
    ui->stackedWidget->setCurrentIndex(0);
    ui->myPasswordsToolButton->setChecked(true);
    timer->start(1000);
    timer->setTimerType(Qt::VeryCoarseTimer);

}

void MainWindow::raiseLoginPage()
{
    this->hide();
    loginDialog->show();
    databaseVerifier->doConnect();
}

void MainWindow::resizeEvent(QResizeEvent *)
{
    emit mainwindowResized(ui->stackedWidget->size());
}
void MainWindow::setupMainWindow(User *user)
{
    userController->setUser(user);
    setupProperties();
    loginDialog->hide();
//    this->showFullScreen();
    this->show();
    ui->usernameLabel->setText(user->prettyName());
    ui->tableTab->tableView()->syncSize(ui->stackedWidget->size());
}
void MainWindow::updateDateAndTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
    ui->dateLabel->setText(QDate::currentDate().toString());
}
