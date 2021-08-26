#include "tabletab.h"
#include "ui_passwordtablewidget.h"

#include "table/tableview.h"
#include "Single/password.h"
#include "GUI/iteminsertiondialog.h"


TableTab::TableTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PasswordTableWidget)
{
    ui->setupUi(this);
    setupProperties();
    setupConnection();
}

TableTab::~TableTab()
{
    delete ui;
}

void TableTab::syncTableSize()
{
    tableView->syncSize();
}

void TableTab::setupProperties()
{
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
    ui->searchLineEdit->setPlaceholderText("Search Passwords");

    tableView            = new TableView(this);   // Table
    itemInsertionDialog  = new ItemInsertionDialog  (this);   // Insertion Dialog
    ui->verticalLayout_6->addWidget(tableView);
}

void TableTab::setupConnection()
{
    connect(tableView,&TableView::deleteItem,this,&TableTab::removeItemRequested);
    connect(ui->newPasswords,&QToolButton::clicked,itemInsertionDialog,&ItemInsertionDialog::exec);
    connect(this,&TableTab::addItemRequested,tableView,&TableView::addNewItem);
    connect(itemInsertionDialog,&ItemInsertionDialog::newInsertionRequested,this,&TableTab::itemInsertionRequested);
    connect(this,&TableTab::insertionResult,itemInsertionDialog,&ItemInsertionDialog::onInsertionResult);
//    connect(tableView,&TableView::deleteItem,this,&PasswordTableWidget::removeItemRequested);
}

void TableTab::updateTotPass(int count)
{
    ui->totalPasswordsLabel->setNum(count);
}

void TableTab::upadteTotSite(int count)
{
    ui->totalSitesLabel->setNum(count);
}
