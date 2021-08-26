#include "tablemodel.h"
#include <QtDebug>
#include "../Single/password.h"

TableModel::TableModel(QObject *parent):
    QAbstractTableModel(parent)
{
    setupRoles();
}

TableModel::~TableModel()
{

}

void TableModel::addItem(Password *item)
{
//    beginInsertRows(QModelIndex(),itemsCount(),itemsCount());
    itemsList.append(item);
//    endInsertRows();

}

void TableModel::addItems(QList<Password *> items)
{
    itemsList = items;
}

QVariant TableModel::dataAt(int row, int column) const
{
    return index(row,0,QModelIndex()).data();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        switch (role) {
        case IdField:       return  itemsList[index.row()]->passId();
        case UsernameField: return  itemsList[index.row()]->username();
        case PasswordField: return  itemsList[index.row()]->password();
        case WebsiteField:  return  itemsList[index.row()]->website();
        default:return QVariant();
        }
    }
    else if(role == Qt::TextAlignmentRole)
        return Qt::AlignCenter;

    else if(role == Qt::EditRole){
        return "Right click to edit";
    }
    return QVariant();
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    return itemsList.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    return _columnCount;
}

QModelIndex TableModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();

    Password *childItem;

    childItem = itemsList.at(row);

    if(childItem){
        QModelIndex mIndex = createIndex(row,column,childItem);
        childItem->setModelIndex(mIndex);
        return mIndex;
    }
    return QModelIndex();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return _roleNames;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case IdField:       return  tr("Pass Id") ;
            case UsernameField: return  tr("Username");
            case PasswordField: return  tr("Password");
            case WebsiteField:  return  tr("Site");
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
    if(!index.isValid())
        return false;
    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case IdField:       itemsList[index.row()]->setPassId(value.toString()); return true;
        case UsernameField: itemsList[index.row()]->setUsername(value.toString()); return true;
        case PasswordField: itemsList[index.row()]->setPassword(value.toString()); return true;
        case WebsiteField:  itemsList[index.row()]->setWebsite(value.toString());return true;
        }
    }

    return false;
}

void TableModel::setupRoles()
{
    _roleNames = QAbstractTableModel::roleNames();
    _roleNames.insert(IdField,"itemId");
    _roleNames.insert(UsernameField,"itemUName");
    _roleNames.insert(PasswordField,"itemPass");
    _roleNames.insert(WebsiteField,"itemWebSite");
}
