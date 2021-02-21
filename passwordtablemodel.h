#ifndef PASSWORDTABLEMODEL_H
#define PASSWORDTABLEMODEL_H
#include <QListView>
#include <QAbstractTableModel>
struct TableItem{
    int     _passId;
    QString _username;
    QString _password;
    QString _site;
    QWidget *_widget = nullptr;
    TableItem(int passId,QString username,QString password,QString site,QWidget* widget = nullptr):
        _passId(passId),_username(username),_password(password),_site(site),_widget(widget)
    {

    }
    TableItem(const TableItem& obj){
        _passId     =  obj._passId;
        _username   =  obj._username;
        _password   =  obj._password;
        _site       =  obj._site;
        _widget     =  obj._widget;
    }
    friend QDataStream& operator <<(QDataStream &out, const TableItem& myObj){
        QString outString = "'",space = " ";
        outString.append(QString::number(myObj._passId));
        outString += space + myObj._username + space + myObj._password + space + myObj._site + " '";
        out << outString;
        return out;
    }
    friend bool operator ==(const TableItem& myObj,const TableItem& myObj2){
        if(myObj._passId == myObj2._passId)
            return true;
        else
            return false;
    }
};

class PasswordTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PasswordTableModel(QObject *parent = nullptr);
    ~PasswordTableModel() override;
    void appendItem(const TableItem& item);
    int tableItemCount() const;
protected:
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;

    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
private:
    const int _columnCount = 4;
    QList<TableItem*> itemsList;
    //Methods
};

#endif // PASSWORDTABLEMODEL_H
