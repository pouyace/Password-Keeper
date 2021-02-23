#include "styleditemdelegate.h"
#include "customtableview.h"
#include <QDebug>
#include <QLineEdit>
StyledItemDelegate::StyledItemDelegate()
    : QStyledItemDelegate ()
{

}


void StyledItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    opt.state &= ~QStyle::State_HasFocus;

    TableView *view = qobject_cast<TableView *>(opt.styleObject);
    QTableView::SelectionBehavior behavior = view->selectionBehavior();
    QModelIndex hoverIndex = view->hoverIndex();

    if (!(option.state & QStyle::State_Selected) && behavior != QTableView::SelectItems) {
        if (behavior == QTableView::SelectRows && hoverIndex.row() == index.row())
            opt.state |= QStyle::State_MouseOver;
        if (behavior == QTableView::SelectColumns && hoverIndex.column() == index.column())
            opt.state |= QStyle::State_MouseOver;
    }
    QStyledItemDelegate::paint(painter, opt, index);
}
QWidget *StyledItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit* temp = new QLineEdit(parent);
    temp->setAlignment(Qt::AlignCenter);
    temp->setContextMenuPolicy(Qt::NoContextMenu);
    temp->setProperty("class","EditMode");
    return temp;
}

void StyledItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    model->setData(index, lineEdit->text(), Qt::DisplayRole);
}

void StyledItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString value = index.model()->data(index, Qt::DisplayRole).toString();
    lineEdit->setText(value);
}



void StyledItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
