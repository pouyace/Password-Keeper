#include "tableview.h"
#include "../Single/password.h"
#include <QDebug>
#include <QHeaderView>
#include <QMouseEvent>
#include <QStandardItemModel>
#include "styleditemdelegate.h"
TableView::TableView(QWidget *parent):
    QTableView(parent)
    , mHoverRow(-1)
    , mHoverColumn(-1)
{
    setupProperties();
}

void TableView::syncSize()
{
    int w = this->width()/7;
    this->setColumnWidth(0,w);
    this->setColumnWidth(1,w*2);
    this->setColumnWidth(2,w*2);
    this->setColumnWidth(3,w*2);
}


void TableView::setupProperties()
{
    this->setContextMenuPolicy(Qt::NoContextMenu);
//    this->setDragEnabled(true);
//    this->setAcceptDrops(true);
//    this->setDragDropMode(QAbstractItemView::DragDrop);
//    this->setDropIndicatorShown(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setCornerButtonEnabled(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(false);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->setMouseTracking(true);

    tableModel = new QStandardItemModel(0,4,this);
    specialDelegate = new StyledItemDelegate();
    this->setModel(tableModel);
    this->setItemDelegate(specialDelegate);
    /*
    this->setItemDelegateForColumn(1,specialDelegate);
    this->setItemDelegateForColumn(2,specialDelegate);
    this->setItemDelegateForColumn(3,specialDelegate);*/

    tableModel->setHeaderData(0,Qt::Horizontal,tr("Pass Id"));
    tableModel->setHeaderData(1,Qt::Horizontal,tr("Username"));
    tableModel->setHeaderData(2,Qt::Horizontal,tr("Password"));
    tableModel->setHeaderData(3,Qt::Horizontal,tr("Site"));

    connect(tableModel,&QStandardItemModel::itemChanged,this,&TableView::onDataChanged);

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

void TableView::onDataChanged(QStandardItem* item)
{
    qDebug()<<"Item on row "<<item->index().row()<<" and column "
           <<item->index().column()<<" changed to "<<item->index().data().toString();
}

void TableView::addNewItem(QList<Password*> passList)
{
    QListIterator<Password*>passIt(passList);
    QList<QStandardItem*> items;
    while(passIt.hasNext()){
        Password* temp = passIt.next();
          items.append(new QStandardItem(temp->getPassId()));
          items.append(new QStandardItem(temp->getUsername()));
          items.append(new QStandardItem(temp->getPassword()));
          items.append(new QStandardItem(temp->getSite()));
          tableModel->appendRow(items);
          items.clear();
          for(int i=0;i<4;i++){
              QModelIndex index = tableModel->index(tableModel->rowCount() - 1,i,QModelIndex());
                tableModel->setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);
            }
    }
}

void TableView::removeViewData()
{
    tableModel->removeRows(0,tableModel->rowCount(),QModelIndex());
}
