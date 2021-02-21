#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "passwordhandler.h"
#include "loadingdialog.h"
#include "logindialog.h"
#include "postgresqlverifier.h"
#include <QHostAddress>
#include <QTimer>
#include <QDateTime>
#include "user.h"
#include <QButtonGroup>
#include "passwordtableview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeObjects();
    setupTime();
    setupButtonGroup();
    setupConnections();
    databaseVerifier->setupConfig(QHostAddress::LocalHost,5432,"postgres","newpouya","PasswordKeeper");
    setupLoginDialog();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(loginDialog,&LoginDialog::loginRequested,databaseVerifier,&PostgreSqlVerifier::verifyUser);
    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabase1State,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabase2State,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::errorOccured,loginDialog,&LoginDialog::setError);
    connect(databaseVerifier,&PostgreSqlVerifier::userSignedIn,this,&MainWindow::setupMainWondow);
    connect(loginDialog,&LoginDialog::closeAppRequested,this,&QMainWindow::close);
    connect(buttonGroup,QOverload<int>::of(&QButtonGroup::buttonClicked),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateDateAndTime);
    connect(ui->exitToolButton,&QToolButton::clicked,this,&QMainWindow::close);
    connect(this,&MainWindow::windowSizeChanged,passwordTable,&PasswordTableView::resizeWidget);
}

void MainWindow::loadPasswordsToTable()
{
    passwordTable->loadTable(user);
}

void MainWindow::setupLoginDialog()
{
    loginDialog->show();
    this->hide();
}

void MainWindow::initializeObjects()
{
    loginDialog = new LoginDialog(this);
    databaseVerifier = new PostgreSqlVerifier(this);
    timer = new QTimer(this);
    passwordTable = new PasswordTableView(this);
    ui->verticalLayout_6->addWidget(passwordTable);

}

void MainWindow::setupMainWondow(User *user)
{
    this->user = user;
    loginDialog->hide();
    this->showFullScreen();
    ui->passwordsCountLabel->setText(QString::number(user->userPasswordsCount()) + " Passwords");
    ui->usernameLabel->setText(user->username());
    ui->totalPasswordsLabel->setNum(user->userPasswordsCount());
    ui->totalSitesLabel->setNum(user->userSitesCount());
    loadPasswordsToTable();
}

void MainWindow::setupButtonGroup()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(true);
    buttonGroup->addButton(ui->myPasswordsToolButton,0);
    buttonGroup->addButton(ui->passwordGeneratorToolButton,1);
    buttonGroup->addButton(ui->ExportToolButton,2);
    buttonGroup->addButton(ui->profileToolButton,3);
    ui->stackedWidget->setCurrentIndex(0);
    ui->myPasswordsToolButton->setChecked(true);
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
}

void MainWindow::setupTime()
{
    timer->start(1000);
    timer->setTimerType(Qt::VeryCoarseTimer);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    emit windowSizeChanged();
}


void MainWindow::updateDateAndTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
    ui->dateLabel->setText(QDate::currentDate().toString());
}

