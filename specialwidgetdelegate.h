#ifndef SPECIALWIDGETDELEGATE_H
#define SPECIALWIDGETDELEGATE_H
#include <QAbstractItemDelegate>
#include <QItemDelegate>
class SpecialWidgetDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SpecialWidgetDelegate(QObject *parent = nullptr);
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    //virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    //void setEditorData(QWidget *editor, const QModelIndex &index) const override;
   // QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif // SPECIALWIDGETDELEGATE_H
