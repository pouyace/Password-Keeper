#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHostAddress>
#include <QTimer>
#include <QDateTime>
#include <QButtonGroup>
#include "GUI/logindialog.h"
#include "Verifier/postgresqlverifier.h"
#include "Single/user.h"
#include "GUI/singleitemoptionwidget.h"
#include "table/tableview.h"
#include "Handlers/passwordhandler.h"
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
    connect(loginDialog,&LoginDialog::loginRequested,databaseVerifier,&PostgreSqlVerifier::onUserLoginRequested);
    connect(loginDialog,&LoginDialog::destroyed,this,&MainWindow::close);
    connect(loginDialog,&LoginDialog::databaseIsNotConnected,databaseVerifier,&PostgreSqlVerifier::onConnectToDatabase);

    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabaseState,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::errorOccured,loginDialog,&LoginDialog::setError);
    connect(databaseVerifier,&PostgreSqlVerifier::hintDisplayRequested,loginDialog,&LoginDialog::onSetHint);
    connect(databaseVerifier,&PostgreSqlVerifier::userSignedIn,this,&MainWindow::setupMainWindow);
    connect(databaseVerifier,&PostgreSqlVerifier::syncItemsRetreived,userController,&UserController::onItemsRetreived);
    connect(databaseVerifier,&PostgreSqlVerifier::newItemInserted,ui->firstWidget,&PasswordTableWidget::removeItemRequested);
    connect(databaseVerifier,&PostgreSqlVerifier::newItemInserted,userController,&UserController::emptyPasswordList);


    connect(this,&MainWindow::connectToDatabaseRequested,databaseVerifier,&PostgreSqlVerifier::onConnectToDatabase);

    connect(databaseVerifier,&PostgreSqlVerifier::onDialogClosed,loginDialog,&LoginDialog::onDatabaseDialogClosed);
    connect(ui->firstWidget,&PasswordTableWidget::itemInsertionRequested,databaseVerifier,&PostgreSqlVerifier::onAddNewItem);
    connect(databaseVerifier,&PostgreSqlVerifier::newItemInserted,ui->firstWidget,&PasswordTableWidget::insertionResult);
    connect(buttonGroup,QOverload<int>::of(&QButtonGroup::buttonClicked),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateDateAndTime);
    connect(ui->exitToolButton  ,&QToolButton::clicked,this,&QMainWindow::close);

    connect(userController,&UserController::showItems,ui->firstWidget,&PasswordTableWidget::addItemRequested,Qt::UniqueConnection);
    connect(userController,&UserController::passwordsCountChanged,this,[=](int c){ui->passwordsCountLabel->setText(QString::number(c) + " Passwords");});
    connect(userController,&UserController::passwordsCountChanged,ui->firstWidget,&PasswordTableWidget::updateTotPass);
    connect(userController,&UserController::uniqueSitesCountChanged,ui->firstWidget,&PasswordTableWidget::upadteTotSite);

}

void MainWindow::initializeObjects()
{
    timer                        = new QTimer               (this);   // Timer
    buttonGroup                  = new QButtonGroup         (this);   // ButtonGroup
}

void MainWindow::initializeModules()
{
    loginDialog                  = new LoginDialog          (this);   // Login
    databaseVerifier             = new PostgreSqlVerifier   (this);   // Database
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
    emit connectToDatabaseRequested(DEFAULTDATABASEUSERNAME,DEFAULTDATABASEPASSWORD);
}
void MainWindow::setupMainWindow(User *user)
{
    userController->setUser(user);
    setupProperties();
    loginDialog->hide();
    this->showFullScreen();
    ui->usernameLabel->setText(user->prettyName());
    ui->firstWidget->syncTableSize();
}
void MainWindow::updateDateAndTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
    ui->dateLabel->setText(QDate::currentDate().toString());
}
