#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>
/*
struct TableItem{
    QString     _passId;
    QString _username;
    QString _password;
    QString _site;
    TableItem(QString passId,QString username,QString password,QString site):
        _passId(passId),_username(username),_password(password),_site(site)
    {

    }
    TableItem(const TableItem& obj){
        _passId     =  obj._passId;
        _username   =  obj._username;
        _password   =  obj._password;
        _site       =  obj._site;
    }
    friend QDataStream& operator <<(QDataStream &out, const TableItem& myObj){
        QString outString = "'",space = " ";
        outString.append(myObj._passId);
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
    void setPassId(QString pass){
        _passId = pass;
        qDebug()<<"passId changed";
    }
    void setUsername(QString username){
        _username = username;
        qDebug()<<"Username changed";
    }
    void setPassword(QString password){
        _password = password;
        qDebug()<<"Password changed";
    }
    void setSite(QString site){
        _site = site;
    }
};
*/
class Password;
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Attributes{IdField , UsernameField, PasswordField, WebsiteField};
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    void addItem(Password *item);
    void addItems(QList<Password*> items);
    QVariant dataAt(int row, int column) const;


protected:
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole)const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const override;
    virtual QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    virtual bool removeRows(int position, int rows, const QModelIndex &index) override;
private:
    const int _columnCount = 4;
    QList<Password*> itemsList;

    //Methods
};

#endif // PASSWORDTABLEMODEL_H
