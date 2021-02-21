#include "passwordtablemodel.h"
#include <QtDebug>
PasswordTableModel::PasswordTableModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

PasswordTableModel::~PasswordTableModel()
{

}

void PasswordTableModel::appendItem(const TableItem &item)
{
    TableItem *temp = new TableItem(item);
    beginInsertRows(QModelIndex(),tableItemCount(),tableItemCount());
    itemsList.append(temp);
    endInsertRows();

}

QVariant PasswordTableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case 0:return itemsList[index.row()] ->_passId;
        case 1:return  itemsList[index.row()]->_username;
        case 2:return  itemsList[index.row()]->_password;
        case 3:return  itemsList[index.row()]->_site;
        default:return QVariant();
        }
    }
     else if(role == Qt::TextAlignmentRole){
        return Qt::AlignCenter;
        }
    return QVariant();
}

int PasswordTableModel::rowCount(const QModelIndex &parent) const
{
    return tableItemCount();
}

int PasswordTableModel::columnCount(const QModelIndex &parent) const
{
    return _columnCount;
}

QVariant PasswordTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case 0:return  tr("Pass Id") ;
            case 1:return  tr("Username");
            case 2:return  tr("Password");
            case 3:return  tr("Site");
            case 4:return  tr("Widget");
            }
        }
        else if(orientation == Qt::Vertical){
            return "";
        }
    }
    return QVariant();
}

bool PasswordTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<"In setData()";
    if(!index.isValid())
        return false;
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case 0: itemsList[index.row()] ->_passId = value.toInt(); return true;
        case 1: itemsList[index.row()]->_username = value.toString();return true;
        case 2: itemsList[index.row()]->_password =value.toString();return true;
        case 3: itemsList[index.row()]->_site =value.toString();return true;
        case 4: qDebug()<<"heelo";return true;
        }
    }
    if(role == Qt::EditRole){
        switch (index.column()) {
        case 0: itemsList[index.row()] ->_passId = value.toInt(); return true;
        case 1: itemsList[index.row()]->_username = value.toString();return true;
        case 2: itemsList[index.row()]->_password =value.toString();return true;
        case 3: itemsList[index.row()]->_site =value.toString();return true;
        case 4: qDebug()<<"heelo";return true;
        }
    }
}

int PasswordTableModel::tableItemCount() const
{
    return itemsList.count();
}
