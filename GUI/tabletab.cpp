#include "tabletab.h"
#include "ui_tabletab.h"
#include "table/proxymodel.h"
#include "table/tableview.h"
#include "Single/password.h"
#include "GUI/insertiondialog.h"
#include <QDebug>

TableTab::TableTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableTab)
{
    ui->setupUi(this);
    setupProperties();
    setupConnection();
}

TableTab::~TableTab()
{
    delete ui;
}

TableView *TableTab::tableView() const
{
    return _tableView;
}

ItemInsertionDialog *TableTab::insertionDialog() const
{
    return itemInsertionDialog;
}

void TableTab::setupProperties()
{
    ui->newPasswords->setCursor(Qt::PointingHandCursor);
    ui->searchToolButton->setCursor(Qt::IBeamCursor);
    ui->searchLineEdit->setPlaceholderText("Search Passwords");

    _tableView            = new TableView(this);   // Table
    itemInsertionDialog  = new ItemInsertionDialog  (this);   // Insertion Dialog
    ui->verticalLayout_6->addWidget(_tableView);
}

void TableTab::setupConnection()
{
    connect(ui->newPasswords,&QToolButton::clicked,itemInsertionDialog,&ItemInsertionDialog::exec);
    connect(ui->searchLineEdit, &QLineEdit::textChanged, this, &TableTab::filterTableItems);
    connect(this, &TableTab::filterItems, _tableView->proxyModel()
            , static_cast<void (QSortFilterProxyModel::*)(const QRegExp&)>(&QSortFilterProxyModel::setFilterRegExp));
    connect(ui->syncButton, &QToolButton::clicked, this, &TableTab::onSyncClicked);

}

void TableTab::filterTableItems(QString text)
{
    emit filterItems(QRegExp(text));
}

void TableTab::updateTotPass(int count)
{
    ui->totalPasswordsLabel->setNum(count);
}

void TableTab::upadteTotSite(int count)
{
    ui->totalSitesLabel->setNum(count);
}
