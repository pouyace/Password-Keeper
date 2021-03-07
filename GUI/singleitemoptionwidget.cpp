#include "singleitemoptionwidget.h"
#include "ui_singleitemoptionwidget.h"

SingleItemOptionWidget::SingleItemOptionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SingleItemOptionWidget)
{
    ui->setupUi(this);
}

SingleItemOptionWidget::~SingleItemOptionWidget()
{
    delete ui;
}
