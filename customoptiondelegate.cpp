#include "customoptiondelegate.h"
#include "singleitemoptionwidget.h"
#include <QLineEdit>
#include <QDebug>
#include <QPainter>
CustomOptionDelegate::CustomOptionDelegate(QObject *parent):
    QItemDelegate(parent)
{

}

QWidget *CustomOptionDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* temp = new QLineEdit(parent);
    temp->setAlignment(Qt::AlignCenter);
    return temp;
}

void CustomOptionDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text(), Qt::DisplayRole);
}

void CustomOptionDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    lineEdit->setText(value);
}



void CustomOptionDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
