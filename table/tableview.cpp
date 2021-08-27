#include "tableview.h"
#include "../Single/password.h"
#include <QDebug>
#include <QHeaderView>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QMenu>
#include "tabledelegate.h"
#include "proxymodel.h"
#include <QMessageBox>
#include "tablemodel.h"
TableView::TableView(QWidget *parent):
    QTableView(parent)
    , mHoverRow(-1)
    , mHoverColumn(-1)
{
    setupProperties();
}

ProxyModel *TableView::proxyModel() const
{
    return _proxyModel;
}

void TableView::syncSize()
{
    int w = this->width()/7;
    this->setColumnWidth(TableModel::IdField      ,w);
    this->setColumnWidth(TableModel::UsernameField,w*2);
    this->setColumnWidth(TableModel::PasswordField,w*2);
    this->setColumnWidth(TableModel::WebsiteField ,w*2);
}


void TableView::setupProperties()
{
//    this->setContextMenuPolicy(Qt::NoContextMenu);
//    this->setDragEnabled(true);
//    this->setAcceptDrops(true);
//    this->setDragDropMode(QAbstractItemView::DragDrop);
//    this->setDropIndicatorShown(true);

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setCornerButtonEnabled(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(false);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->setMouseTracking(true);

    tableModel = new TableModel(this);
    specialDelegate = new StyledItemDelegate();
    this->setModel(tableModel);
    this->setItemDelegate(specialDelegate);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&TableView::customContextMenuRequested,this,&TableView::onCustomContextMenu);

    mainMenu = new QMenu(this);
    mainMenu->addAction("Edit",this,&TableView::contextMenuEditAction);
    mainMenu->addAction("Remove",this,&TableView::contextMenuRemoveAction);
    mainMenu->addAction("Details",this,&TableView::contextMenuDetailsAction);

    _proxyModel = new ProxyModel(this);
    _proxyModel->setSourceModel(tableModel);
    _proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->setModel(_proxyModel);

//    _proxyModel->setFilterRegExp("\\d\\d\\d\\d\\d\\d\\d");

}

void TableView::mouseMoveEvent(QMouseEvent *event)
{
    QTableView::mouseMoveEvent(event);

        QModelIndex index = indexAt(event->pos());
        int oldHoverRow = mHoverRow;
        int oldHoverColumn = mHoverColumn;
        mHoverRow = index.row();
        mHoverColumn = index.column();

        if (selectionBehavior() == SelectRows && oldHoverRow != mHoverRow) {
            for (int i = 0; i < model()->columnCount(); ++i)
                update(model()->index(mHoverRow, i));
        }
        if (selectionBehavior() == SelectColumns && oldHoverColumn != mHoverColumn) {
            for (int i = 0; i < model()->rowCount(); ++i) {
                update(model()->index(i, mHoverColumn));
                update(model()->index(i, oldHoverColumn));
            }
        }
}

void TableView::showSyncItems(QList<Password*> passList)
{
    tableModel->syncTable(passList);
}

void TableView::addItem(Password *password)
{
    tableModel->addItem(password);
}

void TableView::onItemDeleted(int id, bool status)
{
    bool state = false;
    if(status){
        state = tableModel->removeItem(deletingItemRow, id);
    }
    else if( !status && !state){
        QMessageBox::warning(this, "Deletion Error", "Could not delete item with id: "+ QString::number(id));
    }
}

void TableView::onCustomContextMenu(const QPoint &position)
{
    int row = this->indexAt(position).row();
//    qDebug()<<"row="<<row;
    if(row < 0 || row >= tableModel->itemsCount())
        return;
    point = position;
    mainMenu->popup(mapToGlobal(position));
}

void TableView::contextMenuEditAction()
{

}

void TableView::contextMenuRemoveAction()
{
    deletingItemRow = this->indexAt(point).row();
    int id = tableModel->dataAt(deletingItemRow, 0).toInt();
//    qDebug()<<"id="<<id;
    QMessageBox messageBox;
    messageBox.setWindowFlag(Qt::FramelessWindowHint);
    messageBox.setText("Deleting index '"+QString::number(id)+"' permanently");
    messageBox.setInformativeText("Are you sure about this?");
    messageBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    messageBox.setDefaultButton(QMessageBox::Yes);
    int retVal = messageBox.exec();

    switch (retVal) {
        case QMessageBox::Yes:
            emit deleteItem(id);
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
    }
}

void TableView::contextMenuDetailsAction()
{

}
