#include "customtablemodel.h"
#include <QtDebug>
TableModel::TableModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{

}

void TableModel::appendItem(const TableItem &item)
{
    TableItem *temp = new TableItem(item);
    beginInsertRows(QModelIndex(),tableItemCount(),tableItemCount());
    itemsList.append(temp);
    endInsertRows();

}

QVariant TableModel::data(const QModelIndex &index, int role) const
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
    else if(role == Qt::EditRole){
        return "wwwwww";
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return tableItemCount();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return _columnCount;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
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

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<"In setData()";
    if(!index.isValid())
        return false;
    if(role == Qt::DisplayRole){
        qDebug()<<"wow";
        switch (index.column()) {
        case 0: itemsList[index.row()]->setPassId(value.toString()); return true;
        case 1: itemsList[index.row()]->setUsername(value.toString()); return true;
        case 2: itemsList[index.row()]->setPassword(value.toString()); return true;
        case 3: itemsList[index.row()]->setSite(value.toString());return true;
        }
    }
    if(role == Qt::EditRole){
        qDebug()<<"wow";
        switch (index.column()) {
        case 0: itemsList[index.row()]->setPassId(value.toString()); return true;
        case 1: itemsList[index.row()]->setUsername(value.toString()); return true;
        case 2: itemsList[index.row()]->setPassword(value.toString()); return true;
        case 3: itemsList[index.row()]->setSite(value.toString());return true;
        }
    }
    return false;
}

int TableModel::tableItemCount() const
{
    return itemsList.count();
}
