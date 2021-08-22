#include "tableview.h"
#include "../Single/password.h"
#include <QDebug>
#include <QHeaderView>
#include <QMouseEvent>
#include <QStandardItemModel>
#include <QMenu>
#include "styleditemdelegate.h"
#include <QMessageBox>
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
    this->setColumnWidth(Pass_Id_col,w);
    this->setColumnWidth(Username_col,w*2);
    this->setColumnWidth(Password_col,w*2);
    this->setColumnWidth(Site_col,w*2);
}


void TableView::setupProperties()
{
//    this->setContextMenuPolicy(Qt::NoContextMenu);
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

    tableModel->setHeaderData(Pass_Id_col,Qt::Horizontal,tr("Pass Id"));
    tableModel->setHeaderData(Username_col,Qt::Horizontal,tr("Username"));
    tableModel->setHeaderData(Password_col,Qt::Horizontal,tr("Password"));
    tableModel->setHeaderData(Site_col,Qt::Horizontal,tr("Site"));

    connect(tableModel,&QStandardItemModel::itemChanged,this,&TableView::onDataChanged);

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&TableView::customContextMenuRequested,this,&TableView::onCustomContextMenu);

    mainMenu = new QMenu(this);
    mainMenu->addAction("Edit",this,&TableView::contextMenuEditAction);
    mainMenu->addAction("Remove",this,&TableView::contextMenuRemoveAction);
    mainMenu->addAction("Details",this,&TableView::contextMenuDetailsAction);



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
//    qDebug()<<"Item on row "<<item->index().row()<<" and column "
//           <<item->index().column()<<" changed to "<<item->index().data().toString();
}

void TableView::addNewItem(QList<Password*> passList)
{
    tableModel->removeRows(0,tableModel->rowCount(),QModelIndex());
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

void TableView::onCustomContextMenu(const QPoint &position)
{
    point = position;
    mainMenu->popup(mapToGlobal(position));
}

void TableView::contextMenuEditAction()
{

}

void TableView::contextMenuRemoveAction()
{
    int row = this->indexAt(point).row();
    qDebug()<<"ajal:"<<row;
    int id = tableModel->index(row,0,QModelIndex()).data().toInt();
    qDebug()<<"id="<<id;
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
