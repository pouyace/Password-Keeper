#include "specialwidgetdelegate.h"
#include "tableitemoptionswidget.h"
#include <QComboBox>
#include <QDebug>
#include <QPainter>
SpecialWidgetDelegate::SpecialWidgetDelegate(QObject *parent):
    QItemDelegate(parent)
{

}

void SpecialWidgetDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem myOption = option;
    int dataIndex = index.data().toInt();
    QString text;
    if((dataIndex > -1) && (dataIndex < 0)){
        text = "_Items.at(dataIndex)";
    }
    myOption.text = text;

    myOption.displayAlignment = Qt::AlignCenter;
    QRectF target(10.0, 20.0, 80.0, 60.0);
      QRectF source(0.0, 0.0, 70.0, 40.0);
    painter->drawPixmap(target,QPixmap(":/icons/add-file.png"),source);
    this->drawDisplay(painter,myOption,myOption.rect,myOption.text);
}

//void SpecialWidgetDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
//{
////    TableItemOptionsWidget *widget = static_cast<TableItemOptionsWidget*>(editor);
////    model->setData(index, widget->isVisible(), Qt::EditRole);
//    TableItemOptionsWidget *comboBox = static_cast<TableItemOptionsWidget*>(editor);
//    //model->setData(index, comboBox->currentIndex(), Qt::EditRole);
//}

//void SpecialWidgetDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    //int value = index.model()->data(index, Qt::EditRole).toInt();
//    //TableItemOptionsWidget *widget = static_cast<TableItemOptionsWidget*>(editor);
//    TableItemOptionsWidget *comboBox = static_cast<TableItemOptionsWidget*>(editor);
//    int value = index.model()->data(index, Qt::DisplayRole).toInt();
////    comboBox->setCurrentIndex(1);
//    qDebug()<<Q_FUNC_INFO;
//}

//QWidget *SpecialWidgetDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    TableItemOptionsWidget* temp = new TableItemOptionsWidget(parent);
//    temp->setPalette(option.palette);
//    temp->setStyle(dynamic_cast<QStyle*>(option.styleObject));
//    return temp;

//    TableItemOptionsWidget *editor = new TableItemOptionsWidget(parent);
//    for(int i = 0; i < 9; ++i){
//        editor->addItem(QString::number(i));
//        editor->setItemData(i,Qt::AlignCenter, Qt::TextAlignmentRole);
//    }
//    editor->setPalette(option.palette);
//    editor->setStyle(dynamic_cast<QStyle*>(option.styleObject));
//    return editor;
//}

void SpecialWidgetDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
