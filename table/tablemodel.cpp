#include "tablemodel.h"
#include <QtDebug>
#include "../Single/password.h"

TableModel::TableModel(QObject *parent):
    QAbstractTableModel(parent)
{

}

TableModel::~TableModel()
{

}

void TableModel::addItem(Password *item)
{
    beginInsertRows(QModelIndex(), itemsList.count(), itemsList.count());
    itemsList.append(item);
    endInsertRows();

}

void TableModel::syncTable(QList<Password *> items)
{
//    qDebug()<<"tableSynced";
    // How about deleteLater() ?
    beginRemoveRows(QModelIndex(), 0, itemsList.count()-1);
    itemsList.clear();
    endRemoveRows();
    beginInsertRows(QModelIndex(), itemsList.count(), itemsList.count()+items.count()-1);
    itemsList.append(items);
    endInsertRows();
}

bool TableModel::removeItem(int row, int id)
{
    bool status = false;
    beginRemoveRows(QModelIndex(), row, row);
    foreach(Password* item, itemsList){
        if(item->passId().toInt() == id){
            item->deleteLater();
            itemsList.removeAll(item);
            status = true;
        }
    }
    endRemoveRows();
    return status;
}

QVariant TableModel::dataAt(int row, int column) const
{
    Q_UNUSED(column)
    return index(row,0,QModelIndex()).data();
}

int TableModel::itemsCount() const
{
    return itemsList.count();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{

    if(!index.isValid())
        return QVariant();

    if (index.row() >= itemsList.size() || index.row() < 0)
             return QVariant();

    if(role == Qt::DisplayRole){
        switch (index.column()) {
        case IdField:           return  itemsList[index.row()]->passId();
        case UsernameField:     return  itemsList[index.row()]->username();
        case PasswordField:     return  itemsList[index.row()]->password();
        case WebsiteField:      return  itemsList[index.row()]->website();
        case DescriptionField:  return itemsList[index.row()]->description();
        case ExpirationDate:    return itemsList[index.row()]->expiration();
        case CreationDateField: return itemsList[index.row()]->creation();
        case TitleField:        return itemsList[index.row()]->title();
        case ValidityField:     return itemsList[index.row()]->validity();
        }
    }

    switch (role) {
    case Qt::TextAlignmentRole: return Qt::AlignCenter;
    case Qt::EditRole: return "Right click to edit";
    default:return QVariant();
    }
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return itemsList.count();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
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

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch (section) {
            case IdField:           return  tr("ID") ;
            case UsernameField:     return  tr("USERNAME");
            case PasswordField:     return  tr("PASSWORD");
            case WebsiteField:      return  tr("WEBSITE");
            case DescriptionField:  return tr("DESCIPTION");
            case ExpirationDate:    return tr("EXP DATE");
            case CreationDateField: return tr("CREATION DATE");
            case TitleField:        return tr("TITLE");
            case ValidityField:     return tr("VALIDITY");
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
    Q_UNUSED(value)
    if(!index.isValid())
        return false;

    switch (role) {
    case Qt::DisplayRole: emit dataChanged(index, index, {});  return true;
    }


    return false;
}


bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         itemsList.removeAt(position);
     }

     endRemoveRows();
     return true;
 }
