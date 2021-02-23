#ifndef CUSTOMOPTIONDELEGATE_H
#define CUSTOMOPTIONDELEGATE_H
#include <QAbstractItemDelegate>
#include <QItemDelegate>
class CustomOptionDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    CustomOptionDelegate(QObject *parent = nullptr);
    //virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // CUSTOMOPTIONDELEGATE_H
