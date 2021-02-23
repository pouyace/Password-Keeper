#include "customtableview.h"
#include "customtablemodel.h"
#include "user.h"
#include "password.h"
#include "customoptiondelegate.h"
#include <QDebug>
#include <QHeaderView>
#include <QStandardItemModel>

TableView::TableView(QWidget *parent):
    QTableView(parent)
{
    setupProperties();
}

void TableView::loadTable(User *user)
{
    QListIterator<Password*> mItr(user->passwords());
    QList<QStandardItem*> items;
    while(mItr.hasNext()){
        Password *temp = mItr.next();
        items.clear();
        items.append(new QStandardItem(temp->getPassId()));
        items.append(new QStandardItem(temp->getUsername()));
        items.append(new QStandardItem(temp->getPassword()));
        items.append(new QStandardItem(temp->getSite()));
        int row = tableModel->rowCount();
        tableModel->appendRow(items);
        for(int i=0;i<4;i++){
            QModelIndex index = tableModel->index(row,i,QModelIndex());
            tableModel->setData(index,Qt::AlignCenter,Qt::TextAlignmentRole);
        }
    }
}

void TableView::syncSize()
{
    int w = this->width()/7;
    this->setColumnWidth(0,w);
    this->setColumnWidth(1,w*2);
    this->setColumnWidth(2,w*2);
    this->setColumnWidth(3,w*2);
}

void TableView::append(TableItem tableItem)
{

}

void TableView::setupProperties()
{
    this->setContextMenuPolicy(Qt::NoContextMenu);
//    this->setDragEnabled(true);
//    this->setAcceptDrops(true);
//    this->setDragDropMode(QAbstractItemView::DragDrop);
//    this->setDropIndicatorShown(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
//    this->setCornerButtonEnabled(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(false);
    this->verticalHeader()->setVisible(false);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    this->setEditTriggers(QAbstractItemView::AllEditTriggers);
//    this->setMouseTracking(true);

    tableModel = new QStandardItemModel(0,4,this);
    specialDelegate = new CustomOptionDelegate(this);
    this->setModel(tableModel);
    this->setItemDelegate(specialDelegate);

    tableModel->setHeaderData(0,Qt::Horizontal,tr("Pass Id"));
    tableModel->setHeaderData(1,Qt::Horizontal,tr("Username"));
    tableModel->setHeaderData(2,Qt::Horizontal,tr("Password"));
    tableModel->setHeaderData(3,Qt::Horizontal,tr("Site"));

    connect(tableModel,&QStandardItemModel::itemChanged,this,&TableView::onDataChanged);

}

void TableView::onDataChanged(QStandardItem* item)
{
    qDebug()<<"Item on row "<<item->index().row()<<" and column "
           <<item->index().column()<<" changed to "<<item->index().data().toString();
}
