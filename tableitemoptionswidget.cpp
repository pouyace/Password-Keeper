#include "tableitemoptionswidget.h"
#include "ui_tableitemoptionswidget.h"

TableItemOptionsWidget::TableItemOptionsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TableItemOptionsWidget)
{
    ui->setupUi(this);
}

TableItemOptionsWidget::~TableItemOptionsWidget()
{
    delete ui;
}
