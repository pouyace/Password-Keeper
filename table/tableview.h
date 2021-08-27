#ifndef PASSWORDTABLEVIEW_H
#define PASSWORDTABLEVIEW_H
#include <QTableView>
class QStandardItemModel;
class Password;
struct TableItem;
class TableModel;
class StyledItemDelegate;
class TableView : public QTableView
{
    Q_OBJECT
public:
    TableView(QWidget *parent = nullptr);
    QModelIndex hoverIndex() const { return model()->index(mHoverRow, mHoverColumn); }
private:
    int mHoverRow, mHoverColumn, deletingItemRow;
    TableModel          *tableModel          = nullptr;
    StyledItemDelegate  *specialDelegate     = nullptr;
    QMenu               *mainMenu            = nullptr;
    QPoint point ;
    void setupProperties();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void syncSize();
    void showSyncItems(QList<Password*>);
    void addItem(Password*);
    void onItemDeleted(int id, bool status);
private slots:
    void onCustomContextMenu(const QPoint &position);
    void contextMenuEditAction();
    void contextMenuRemoveAction();
    void contextMenuDetailsAction();
signals:
    void deleteItem(int);
};

#endif // PASSWORDTABLEVIEW_H
