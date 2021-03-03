#ifndef PASSWORDTABLEVIEW_H
#define PASSWORDTABLEVIEW_H
#include <QTableView>
class QStandardItemModel;
class Password;
struct TableItem;
class QStandardItem;
class StyledItemDelegate;
class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }
    void syncSize();
private:
    int mHoverRow, mHoverColumn;
    QStandardItemModel  *tableModel = nullptr;
    StyledItemDelegate *specialDelegate = nullptr;
    void setupProperties();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void onDataChanged(QStandardItem *item);
    void addNewItem(QList<Password*>);
//    void deleteItem(int id);
};

#endif // PASSWORDTABLEVIEW_H
