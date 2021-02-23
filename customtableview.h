#ifndef PASSWORDTABLEVIEW_H
#define PASSWORDTABLEVIEW_H
#include <QTableView>
class QStandardItemModel;
class User;
struct TableItem;
class CustomOptionDelegate;
class QStandardItem;
class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    void loadTable(User* user);
    void syncSize();
private:
    QStandardItemModel  *tableModel = nullptr;
    CustomOptionDelegate *specialDelegate = nullptr;
    void append(TableItem tableItem);
    void setupProperties();
public slots:
    void onDataChanged(QStandardItem *item);
};

#endif // PASSWORDTABLEVIEW_H
