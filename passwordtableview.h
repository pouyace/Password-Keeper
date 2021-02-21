#ifndef PASSWORDTABLEVIEW_H
#define PASSWORDTABLEVIEW_H
#include <QTableView>
class PasswordTableModel;
class User;
struct TableItem;
class SpecialWidgetDelegate;
class PasswordTableView : public QTableView
{
    Q_OBJECT
public:
    PasswordTableView(QWidget *parent = nullptr);
    void loadTable(User* user);
private:
    PasswordTableModel  *tableModel = nullptr;
    SpecialWidgetDelegate *specialDelegate = nullptr;
    void append(TableItem tableItem);
    void setupProperties();
public slots:
    void resizeWidget();
};

#endif // PASSWORDTABLEVIEW_H
