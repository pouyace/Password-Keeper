#ifndef TABLEITEMOPTIONSWIDGET_H
#define TABLEITEMOPTIONSWIDGET_H

#include <QWidget>

namespace Ui {
class TableItemOptionsWidget;
}

class TableItemOptionsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableItemOptionsWidget(QWidget *parent = nullptr);
    ~TableItemOptionsWidget();

private:
    Ui::TableItemOptionsWidget *ui;
};

#endif // TABLEITEMOPTIONSWIDGET_H
