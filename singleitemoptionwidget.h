#ifndef SINGLEITEMOPTIONWIDGET_H
#define SINGLEITEMOPTIONWIDGET_H

#include <QWidget>

namespace Ui {
class SingleItemOptionWidget;
}

class SingleItemOptionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SingleItemOptionWidget(QWidget *parent = nullptr);
    ~SingleItemOptionWidget();

private:
    Ui::SingleItemOptionWidget *ui;
};

#endif // SINGLEITEMOPTIONWIDGET_H
