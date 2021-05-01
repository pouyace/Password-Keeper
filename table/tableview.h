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
    enum TableHeader{Pass_Id_col, Username_col, Password_col, Site_col};
    TableView(QWidget *parent = nullptr);
    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }
    void syncSize();
private:
    int mHoverRow, mHoverColumn;
    QStandardItemModel  *tableModel = nullptr;
    StyledItemDelegate *specialDelegate = nullptr;
    QMenu *mainMenu = nullptr;
    QPoint point ;
    void setupProperties();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void onDataChanged(QStandardItem *item);
    void addNewItem(QList<Password*>);
    void removeViewData();
    void onCustomContextMenu(const QPoint &position);
private slots:
    void contextMenuEditAction();
    void contextMenuRemoveAction();
    void contextMenuDetailsAction();
signals:
    void deleteItemUsingId(int);
//    void deleteItem(int id);
};

#endif // PASSWORDTABLEVIEW_H
