#include "iteminsertiondialog.h"
#include "ui_iteminsertiondialog.h"

ItemInsertionDialog::ItemInsertionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemInsertionDialog)
{
    ui->setupUi(this);
}

ItemInsertionDialog::~ItemInsertionDialog()
{
    delete ui;
}
