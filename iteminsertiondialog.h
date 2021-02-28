#ifndef ITEMINSERTIONDIALOG_H
#define ITEMINSERTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ItemInsertionDialog;
}

class ItemInsertionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ItemInsertionDialog(QWidget *parent = nullptr);
    ~ItemInsertionDialog();

private:
    Ui::ItemInsertionDialog *ui;
};

#endif // ITEMINSERTIONDIALOG_H
