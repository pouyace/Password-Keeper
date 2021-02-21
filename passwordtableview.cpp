#include "passwordtableview.h"
#include "passwordtablemodel.h"
#include "user.h"
#include "password.h"
#include "specialwidgetdelegate.h"
#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QHeaderView>

PasswordTableView::PasswordTableView(QWidget *parent):
    QTableView(parent)
{
    tableModel = new PasswordTableModel(this);
    this->setModel(tableModel);
    setupProperties();
}

void PasswordTableView::loadTable(User *user)
{
    QListIterator<Password*> mItr(user->passwords());
    while(mItr.hasNext()){
        Password *temp = mItr.next();
        this->append(TableItem(temp->getPassId(),temp->getUsername(),temp->getPassWord(),temp->getSite()));
    }
}

void PasswordTableView::append(TableItem tableItem)
{
    tableModel->appendItem(tableItem);
}

void PasswordTableView::setupProperties()
{
    this->setDragEnabled(true);
    this->setAcceptDrops(true);
    this->setDragDropMode(QAbstractItemView::DragDrop);
    this->setDropIndicatorShown(true);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setCornerButtonEnabled(false);
    this->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->horizontalHeader()->setStretchLastSection(false);
//    this->horizontalHeader()->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    this->verticalHeader()->setVisible(false);
    this->setMouseTracking(true);
    this->resizeWidget();
    this->setRowHeight(0,90);
    this->setRowHeight(1,90);
    this->setRowHeight(2,90);
    this->setRowHeight(3,90);
}

void PasswordTableView::resizeWidget()
{
    qDebug()<<"w:"<<this->width();
    int w = this->width()/7;
    this->setColumnWidth(0,w );
    this->setColumnWidth(1,w*2);
    this->setColumnWidth(2,w*2);
    this->setColumnWidth(3,w*2);
}
