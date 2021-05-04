#include "passwordtablewidget.h"
#include "ui_passwordtablewidget.h"

#include "table/tableview.h"
#include "password.h"
#include "GUI/iteminsertiondialog.h"


PasswordTableWidget::PasswordTableWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordTableWidget)
{
    ui->setupUi(this);
    setupProperties();
    setupConnection();
}

PasswordTableWidget::~PasswordTableWidget()
{
    delete ui;
}

void PasswordTableWidget::syncTableSize()
{
    tableView->syncSize();
}

void PasswordTableWidget::setupProperties()
{
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
    ui->searchLineEdit->setPlaceholderText("Search Passwords");

    tableView            = new TableView(this);   // Table
    itemInsertionDialog  = new ItemInsertionDialog  (this);   // Insertion Dialog
    ui->verticalLayout_6->addWidget(tableView);
}

void PasswordTableWidget::setupConnection()
{
    connect(ui->newPasswords,&QToolButton::clicked,itemInsertionDialog,&ItemInsertionDialog::exec);
    connect(this,&PasswordTableWidget::addItemRequested,tableView,&TableView::addNewItem);
    connect(this,&PasswordTableWidget::removeItemRequested,tableView,&TableView::removeViewData);
    connect(itemInsertionDialog,&ItemInsertionDialog::newInsertionRequested,this,&PasswordTableWidget::itemInsertionRequested);
    connect(this,&PasswordTableWidget::insertionResult,itemInsertionDialog,&ItemInsertionDialog::onInsertionResult);
}

void PasswordTableWidget::updateTotPass(int count)
{
    ui->totalPasswordsLabel->setNum(count);
}

void PasswordTableWidget::upadteTotSite(int count)
{
    ui->totalSitesLabel->setNum(count);
}
