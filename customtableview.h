#ifndef PASSWORDTABLEVIEW_H
#define PASSWORDTABLEVIEW_H
#include <QTableView>
class QStandardItemModel;
class User;
struct TableItem;
class QStandardItem;
class StyledItemDelegate;
class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }
    void loadTable(User* user);
    void syncSize();
private:
    int mHoverRow, mHoverColumn;
    QStandardItemModel  *tableModel = nullptr;
    StyledItemDelegate *specialDelegate = nullptr;
    void append(TableItem tableItem);
    void setupProperties();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void onDataChanged(QStandardItem *item);
};

#endif // PASSWORDTABLEVIEW_H
