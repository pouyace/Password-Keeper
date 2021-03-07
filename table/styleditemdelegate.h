#ifndef STYLEDITEMDELEGATE_H
#define STYLEDITEMDELEGATE_H

#include <QStyledItemDelegate>

class StyledItemDelegate : public QStyledItemDelegate
{
public:
    StyledItemDelegate();

    // QAbstractItemDelegate interface
public:
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const Q_DECL_OVERRIDE;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // STYLEDITEMDELEGATE_H
