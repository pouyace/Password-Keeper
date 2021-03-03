#include "mainwindow.h"
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
#include "tableview.h"
#include "databasepassewordsetter.h"
#include "passwordhandler.h"
#include "usercontroller.h"
#include "iteminsertiondialog.h"

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
    connect(loginDialog,&LoginDialog::destroyed,this,&MainWindow::close);
//    connect(loginDialog,&LoginDialog::databaseIsNotConnected,databaseVerifier,&PostgreSqlVerifier::connectToDatabase);

    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,loginDialog,&LoginDialog::setDatabaseState,Qt::UniqueConnection);
    connect(databaseVerifier,&PostgreSqlVerifier::errorOccured,loginDialog,&LoginDialog::setError);
    connect(databaseVerifier,&PostgreSqlVerifier::hintDisplayRequested,loginDialog,&LoginDialog::onSetHint);
    connect(databaseVerifier,&PostgreSqlVerifier::userSignedIn,this,&MainWindow::setupMainWindow);

    connect(databaseVerifier,&PostgreSqlVerifier::passwordListRetreived,userController,&UserController::onItemsRetreived);

    connect(databaseVerifier,&PostgreSqlVerifier::databaseConnected,databasePasswordSetterDialog,&DataBasePassewordSetter::onDatabaseConnected);
    connect(this,&MainWindow::connectToDatabaseRequested,databaseVerifier,&PostgreSqlVerifier::connectToDatabase);

    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::databaseNewConfigSet,databaseVerifier,&PostgreSqlVerifier::connectToDatabase);
    connect(databasePasswordSetterDialog,&DataBasePassewordSetter::dialodClosed,loginDialog,&LoginDialog::onDatabaseDialogClosed);

    connect(userController,&UserController::showItems,tableView,&TableView::addNewItem,Qt::UniqueConnection);

    connect(itemInsertionDialog,&ItemInsertionDialog::newInsertionRequested,databaseVerifier,&PostgreSqlVerifier::addNewItemToDatabase);
    connect(databaseVerifier,&PostgreSqlVerifier::newItemInserted,itemInsertionDialog,&ItemInsertionDialog::onInsertionResult);
    connect(ui->newPasswords,&QToolButton::clicked,this,&MainWindow::onInsertNewPassword);
    connect(buttonGroup,QOverload<int>::of(&QButtonGroup::buttonClicked),ui->stackedWidget,&QStackedWidget::setCurrentIndex);
    connect(timer,&QTimer::timeout,this,&MainWindow::updateDateAndTime);
    connect(ui->exitToolButton,&QToolButton::clicked,this,&QMainWindow::close);
    connect(userController,&UserController::passwordsCountChanged,this,[=](int c){ui->passwordsCountLabel->setText(QString::number(c) + " Passwords");});
    connect(userController,&UserController::passwordsCountChanged,this,[=](int c){ui->totalPasswordsLabel->setNum(c);});
    connect(userController,&UserController::uniqueSitesCountChanged,this,[=](int c){ui->totalSitesLabel->setNum(c);});

}

void MainWindow::initializeObjects()
{
    loginDialog                  = new LoginDialog          (this);
    databaseVerifier             = new PostgreSqlVerifier   (this);
    userController               = new UserController       (this);
    tableView                    = new TableView            (this);
    timer                        = new QTimer               (this);
    buttonGroup                  = new QButtonGroup         (this);
    itemInsertionDialog          = new ItemInsertionDialog  (this);
    databasePasswordSetterDialog = new DataBasePassewordSetter(DEFAULTDATABASEUSERNAME,DEFAULTDATABASEPASSWORD
                                                               ,loginDialog);

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
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
    timer->start(1000);
    timer->setTimerType(Qt::VeryCoarseTimer);
    ui->verticalLayout_6->addWidget(tableView);
    ui->searchLineEdit->setPlaceholderText("Search Passwords");
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
    tableView->syncSize();
    ui->usernameLabel->setText(user->prettyName());
}
void MainWindow::updateDateAndTime()
{
    ui->timeLabel->setText(QTime::currentTime().toString("h:mm:ss"));
    ui->dateLabel->setText(QDate::currentDate().toString());
}

void MainWindow::onInsertNewPassword()
{
    itemInsertionDialog->exec();

}
