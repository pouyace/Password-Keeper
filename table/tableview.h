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
    void syncSize();
private:
    int mHoverRow, mHoverColumn;
    TableModel          *tableModel          = nullptr;
    StyledItemDelegate  *specialDelegate     = nullptr;
    QMenu               *mainMenu            = nullptr;
    QPoint point ;
    void setupProperties();
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
public slots:
    void addNewItem(QList<Password*>);
private slots:
    void onCustomContextMenu(const QPoint &position);
    void contextMenuEditAction();
    void contextMenuRemoveAction();
    void contextMenuDetailsAction();
signals:
    void deleteItem(int);
};

#endif // PASSWORDTABLEVIEW_H
