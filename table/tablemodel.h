#ifndef TABLEMODEL_H
#define TABLEMODEL_H
#include <QAbstractTableModel>

class Password;
class TableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum Attributes{IdField ,TitleField, ValidityField, WebsiteField, CreationDateField, ExpirationDate, UsernameField, PasswordField, DescriptionField};
    explicit TableModel(QObject *parent = nullptr);
    ~TableModel() override;

    void addItem(Password *item);
    void syncTable(QList<Password*> items);
    bool removeItem(int row, int id);
    QVariant dataAt(int row, int column) const;
    int itemsCount()const;


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
    const int _columnCount = 9;
    QList<Password*> itemsList;

    //Methods
};

#endif // PASSWORDTABLEMODEL_H
